#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "j9.h"
#include "StaticProfilingSite.hpp"

std::vector<SPM_StaticProfileInfo *> callSiteProfilingData;
std::vector<SPM_StaticProfileInfo *> returnSiteProfilingData;
std::vector<SPM_StaticProfileInfo *> staticAssignSiteProfilingData;

const char * callSiteCounterPrefix = "CALL-SITE-COUNTER/";
const char * returnSiteCounterPrefix = "RETURN-SITE-COUNTER/";
const char * staticAssignSiteCounterPrefix = "STATIC-ASSIGN-SITE-COUNTER/";

const char * _methodSignature;
U_32 _id;
U_32 _bco;

std::vector<SPM_StaticProfileInfo *> SPM_StaticProfile::getCallSiteProfile()
{
    return callSiteProfilingData;
}

std::vector<SPM_StaticProfileInfo *> SPM_StaticProfile::getReturnSiteProfile()
{
    return returnSiteProfilingData;
}

std::vector<SPM_StaticProfileInfo *> SPM_StaticProfile::getStaticAssignSiteProfile()
{
    return staticAssignSiteProfilingData;
}

const char * SPM_StaticProfileInfo::getMethodSignature()
{
    return _methodSignature;
}

U_32 SPM_StaticProfileInfo::getID()
{
    return _id;
}

U_32 SPM_StaticProfileInfo::getBCI()
{
    return _bco;
}

char * createMethodSignature(TR_ResolvedMethod * _method);

const char * createCopy(const char * targetString)
{
    char * copyString = NULL;
    if( targetString != NULL)
    {
        copyString = (char *) malloc (strlen(targetString));
        strcpy(copyString, targetString);
        
    }
    return copyString;
}

const char * getDebugCounterName4CallSite(const char * ID)
{
	char *debugCounterName =  (char*)malloc(strlen(callSiteCounterPrefix)+strlen(ID)+1);
    strcpy(debugCounterName,callSiteCounterPrefix);
    strcat(debugCounterName,ID);
    return debugCounterName;
}

bool SPM_StaticProfile::getCallSitePreference(char * methodSignature, uint32_t bci)
{
    std::vector<SPM_StaticProfileInfo *> callSiteProfile = getCallSiteProfile();
    for (size_t i = 0; i < callSiteProfile.size(); ++i)
    {
        const char *method_sig = callSiteProfile[i]->getMethodSignature();
        if ( (strncmp(method_sig, methodSignature, strlen(method_sig)) == 0) 
            && bci == callSiteProfile[i]->getBCI())
        {
           return true;
        }
    }
    return false;
}

bool SPM_StaticProfile::getCallSitePreference(TR_ResolvedMethod * _method, uint32_t bci)
{
    if(NULL != _method)
    {
        char * methodSig = createMethodSignature(_method);
        std::vector<SPM_StaticProfileInfo *> callSiteProfile = getCallSiteProfile();
        for (size_t i = 0; i < callSiteProfile.size(); ++i)
        {
            const char *method_sig = callSiteProfile[i]->getMethodSignature();
            if ( (strncmp(method_sig, methodSig, strlen(method_sig)) == 0) 
                && bci == callSiteProfile[i]->getBCI())
            {
                free(methodSig);
                return true;
            }
        }
        free(methodSig);
    }
    return false;
}

const char * SPM_StaticProfile::getDebugCounterName(char * methodSignature, uint32_t bci)
{
    std::vector<SPM_StaticProfileInfo *> callSiteProfile = getCallSiteProfile();
    for (size_t i = 0; i < callSiteProfile.size(); ++i)
    {
        const char *method_sig = callSiteProfile[i]->getMethodSignature();
        if ( (strncmp(method_sig, methodSignature, strlen(method_sig)) == 0) 
            && bci == callSiteProfile[i]->getBCI())
        {
            U_32 intID  = callSiteProfile[i]->getID();
            std::string ID_string = std::to_string(intID);
            const char * ID_char = ID_string.c_str();
            return getDebugCounterName4CallSite(ID_char);
        }
    }
    return NULL;
}

const char * SPM_StaticProfile::getDebugCounterName(TR_ResolvedMethod * _method, uint32_t bci)
{
    if(NULL != _method)
    {
        char * _methodSig = createMethodSignature(_method);
        std::vector<SPM_StaticProfileInfo *> callSiteProfile = getCallSiteProfile();
        for (size_t i = 0; i < callSiteProfile.size(); ++i)
        {
            const char *method_sig = callSiteProfile[i]->getMethodSignature();
            if ( (strncmp(method_sig, _methodSig, strlen(method_sig)) == 0) 
                && bci == callSiteProfile[i]->getBCI())
            {
                U_32 intID  = callSiteProfile[i]->getID();
                std::string ID_string = std::to_string(intID);
                const char * ID_char = ID_string.c_str();
                free(_methodSig);
                return getDebugCounterName4CallSite(ID_char);
            }
        }
        free(_methodSig);
    }
    
    return NULL;
}

void SPM_StaticProfile::clearResults()
{
    for(size_t i = 0; i < callSiteProfilingData.size(); ++i) 
    {
        SPM_StaticProfileInfo * element = callSiteProfilingData[i];
        char * methodSig =  (char *)element->getMethodSignature();
        free(methodSig);
        delete(element);
    }

    for(size_t i = 0; i < returnSiteProfilingData.size(); ++i) 
    {
        SPM_StaticProfileInfo * element = returnSiteProfilingData[i];
        char * methodSig =  (char *)element->getMethodSignature();
        free(methodSig);
        delete(element);
    }

    for(size_t i = 0; i < staticAssignSiteProfilingData.size(); ++i) 
    {
        SPM_StaticProfileInfo * element = staticAssignSiteProfilingData[i];
        char * methodSig =  (char *)element->getMethodSignature();
        free(methodSig);
        delete(element);
    }
}

char * createMethodSignature(TR_ResolvedMethod * _method)
{
    if(NULL != _method)
    {
        /** Get all the required information. */
        char * methodClassName = (char*)malloc(_method->classNameLength());
        char * methodName = (char*)malloc(_method->nameLength());
        char * methodSig = (char*)malloc(_method->signatureLength());
        strncpy(methodClassName,_method->classNameChars(),_method->classNameLength());
        strncpy(methodName,_method->nameChars(),_method->nameLength());
        strncpy(methodSig,_method->signatureChars(),_method->signatureLength());

        /** Create new string for signature. */
        char *_methodSig =  (char*)calloc(_method->classNameLength()+_method->nameLength()
            +_method->signatureLength()+4,1);
        strncpy(_methodSig,methodClassName,_method->classNameLength());
        strcat(_methodSig,"#");
        strncat(_methodSig,methodName,_method->nameLength());
        strcat(_methodSig,"#");
        strncat(_methodSig,methodSig,_method->signatureLength());
        free(methodClassName);
        free(methodName);
        free(methodSig);
        return _methodSig;
    }
    return NULL;
}
