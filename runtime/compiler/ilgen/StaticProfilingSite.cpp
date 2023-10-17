#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "j9.h"
#include "StaticProfilingSite.hpp"

std::vector<SPM_StaticProfileInfo *> callSiteProfilingData;
std::vector<SPM_StaticProfileInfo *> returnSiteProfilingData;
std::vector<SPM_StaticProfileInfo *> staticAssignSiteProfilingData;

const char * callSiteCounterPrefix = "SSRA/CALL-SITE-COUNTER/";
const char * returnSiteCounterPrefix = "SSRA/RETURN-SITE-COUNTER/";
const char * staticAssignSiteCounterPrefix = "SSRA/STATIC-ASSIGN-SITE-COUNTER/";

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

const char * createMethodSignature(TR_ResolvedMethod * _method);

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
/** General util functions. */
const char * getDCName4CallSite(const char * ID)
{
	char *debugCounterName =  (char*)malloc(strlen(callSiteCounterPrefix)+strlen(ID)+1);
    strcpy(debugCounterName,callSiteCounterPrefix);
    strcat(debugCounterName,ID);
    // printf("Allocating CS site memory: %s",debugCounterName);
    return debugCounterName;
}

const char * getDCName4RetSite(const char * ID)
{
	char *debugCounterName =  (char*)malloc(strlen(returnSiteCounterPrefix)+strlen(ID)+1);
    strcpy(debugCounterName,returnSiteCounterPrefix);
    strcat(debugCounterName,ID);
    // printf("Allocating RT site memory: %s",debugCounterName);
    return debugCounterName;
}

const char * getDCName4SASite(const char * ID)
{
	char *debugCounterName =  (char*)malloc(strlen(staticAssignSiteCounterPrefix)+strlen(ID)+1);
    strcpy(debugCounterName,staticAssignSiteCounterPrefix);
    strcat(debugCounterName,ID);
    // printf("Allocating SA site memory: %s",debugCounterName);
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
            return getDCName4CallSite(ID_char);
        }
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

const char * createMethodSignature(TR_ResolvedMethod * _method)
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
            +_method->signatureLength()+3,1);
        strncpy(_methodSig,methodClassName,_method->classNameLength());
        strcat(_methodSig,"##");
        strncat(_methodSig,methodName,_method->nameLength());
        // strcat(_methodSig,"#");
        strncat(_methodSig,methodSig,_method->signatureLength());
        free(methodClassName);
        free(methodName);
        free(methodSig);
        return _methodSig;
    }
    return NULL;
}

/** Call-Site util functions. */

bool SPM_StaticProfile::getPreference4CallSite(TR_ResolvedMethod * _method, uint32_t bci)
{
    if(NULL != _method)
    {
        const char * methodSig = createMethodSignature(_method);
        // printf("Allocating callsite site memory: %s",methodSig);
        // if((strncmp(_method->nameChars(), "trace", 5) == 0) )
        // {
        //     printf("Inside trace. BCO: %u\n",bci);
        // }
        std::vector<SPM_StaticProfileInfo *> callSiteProfile = getCallSiteProfile();
        for (size_t i = 0; i < callSiteProfile.size(); ++i)
        {
            const char *method_sig = callSiteProfile[i]->getMethodSignature();
            // if((strncmp(_method->nameChars(), "trace", 5) == 0) && (bci == 65 || bci == 96) )
            // {
            //     int cmpOut = strncmp(method_sig, methodSig, strlen(method_sig));
            //     printf("method_sig:%s methodSig:%s strlen %lu. BCO: %u\n",method_sig,methodSig,strlen(method_sig),bci);
            //     printf("Compare Out: %d\n",cmpOut);
            // }
            if ( (strncmp(method_sig, methodSig, strlen(method_sig)) == 0) 
                && bci == callSiteProfile[i]->getBCI())
            {
                free((char *)methodSig);
                return true;
            }
        }
        free((char *)methodSig);
    }
    return false;
}

const char * SPM_StaticProfile::getDebugCounterName4CallSite(TR_ResolvedMethod * _method, uint32_t bci)
{
    if(NULL != _method)
    {
        const char * _methodSig = createMethodSignature(_method);
        // printf("Allocating dc callsite site memory: %s",_methodSig);
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
                free((char *)_methodSig);
                return getDCName4CallSite(ID_char);
            }
        }
        free((char *)_methodSig);
    }
    
    return NULL;
}



/** Return-Site util functions. */

bool SPM_StaticProfile::getPreference4ReturnSite(TR_ResolvedMethod * _method, uint32_t bci)
{
    if(NULL != _method)
    {
        const char * methodSig = createMethodSignature(_method);
        std::vector<SPM_StaticProfileInfo *> retSiteProfile = getReturnSiteProfile();
        for (size_t i = 0; i < retSiteProfile.size(); ++i)
        {
            const char *method_sig = retSiteProfile[i]->getMethodSignature();
            // if((strncmp(_method->nameChars(), "getView", 7) == 0))
            // // && (bci == 4) )
            // {
            //     int cmpOut = strncmp(method_sig, methodSig, strlen(method_sig));
            //     printf("method_sig:%s methodSig:%s strlen %lu. BCO: %u\n",method_sig,methodSig,strlen(method_sig),bci);
            //     printf("Compare Out: %d\n",cmpOut);
            // }
            if ( (strncmp(method_sig, methodSig, strlen(method_sig)) == 0) 
                && bci == retSiteProfile[i]->getBCI())
            {
                free((char *)methodSig);
                return true;
            }
        }
        free((char *)methodSig);
    }
    return false;
}

const char * SPM_StaticProfile::getDebugCounterName4ReturnSite(TR_ResolvedMethod * _method, uint32_t bci)
{
    if(NULL != _method)
    {
        const char * _methodSig = createMethodSignature(_method);
        // printf("Allocating dc return site memory: %s",_methodSig);
        std::vector<SPM_StaticProfileInfo *> retSiteProfile = getReturnSiteProfile();
        for (size_t i = 0; i < retSiteProfile.size(); ++i)
        {
            const char *method_sig = retSiteProfile[i]->getMethodSignature();
            if ( (strncmp(method_sig, _methodSig, strlen(method_sig)) == 0) 
                && bci == retSiteProfile[i]->getBCI())
            {
                U_32 intID  = retSiteProfile[i]->getID();
                std::string ID_string = std::to_string(intID);
                const char * ID_char = ID_string.c_str();
                free((char *)_methodSig);
                return getDCName4RetSite(ID_char);
            }
        }
        free((char *)_methodSig);
    }
    return NULL;
}


/** Static-Assign Site util functions. */

bool SPM_StaticProfile::getPreference4SASite(TR_ResolvedMethod * _method, uint32_t bci)
{
    if(NULL != _method)
    {
        const char * methodSig = createMethodSignature(_method);
        // printf("Allocating sa site memory: %s",methodSig);
        std::vector<SPM_StaticProfileInfo *> saSiteProfile = getStaticAssignSiteProfile();
        for (size_t i = 0; i < saSiteProfile.size(); ++i)
        {
            const char *method_sig = saSiteProfile[i]->getMethodSignature();
            // if((strncmp(_method->nameChars(), "getCenter", 9) == 0))
            // // && (bci == 4) )
            // {
            //     int cmpOut = strncmp(method_sig, methodSig, strlen(method_sig));
            //     printf("method_sig:%s methodSig:%s strlen %lu. BCO: %u\n",method_sig,methodSig,strlen(method_sig),bci);
            //     printf("Compare Out: %d\n",cmpOut);
            // }
            if ( (strncmp(method_sig, methodSig, strlen(method_sig)) == 0) 
                && bci == saSiteProfile[i]->getBCI())
            {
                free((char *)methodSig);
                return true;
            }
        }
        free((char *)methodSig);
    }
    return false;
}

const char * SPM_StaticProfile::getDebugCounterName4SASite(TR_ResolvedMethod * _method, uint32_t bci)
{
    if(NULL != _method)
    {
        const char * _methodSig = createMethodSignature(_method);
        // printf("Allocating sa dc site memory: %s",_methodSig);
        std::vector<SPM_StaticProfileInfo *> saSiteProfile = getStaticAssignSiteProfile();
        for (size_t i = 0; i < saSiteProfile.size(); ++i)
        {
            const char *method_sig = saSiteProfile[i]->getMethodSignature();
            if ( (strncmp(method_sig, _methodSig, strlen(method_sig)) == 0) 
                && bci == saSiteProfile[i]->getBCI())
            {
                U_32 intID  = saSiteProfile[i]->getID();
                std::string ID_string = std::to_string(intID);
                const char * ID_char = ID_string.c_str();
                free((char *)_methodSig);
                return getDCName4SASite(ID_char);
            }
        }
        free((char *)_methodSig);
    }
    return NULL;
}