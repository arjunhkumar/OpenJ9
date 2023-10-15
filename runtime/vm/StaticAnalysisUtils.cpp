#include <stdio.h>
#include "InlineableFieldMetadata.hpp"
#include "StaticAnalysisUtils.hpp"
#include "StaticProfilingMetadata.hpp"

std::vector<IFM_ClassMetadata *> StaticAnalysisUtils::staticResults;
SPM_StaticProfilingMetadata * StaticAnalysisUtils::profilingData;

bool StaticAnalysisUtils::fieldInliningPreference(J9Class *fieldClass, J9ROMFieldShape* field){
    J9UTF8* className = J9ROMCLASS_CLASSNAME(fieldClass->romClass);
    const char * classNameStr = (char *) J9UTF8_DATA(className);
    // printf("Trying to check status of field of Container Class: %s\n",classNameStr);
    IFM_ClassMetadata * classData = getClassMetadata(classNameStr);
    if(classData != NULL)
    {
        J9ROMNameAndSignature *nameAndSig = &field->nameAndSignature;
		J9UTF8 *nameUTF = J9ROMNAMEANDSIGNATURE_NAME(nameAndSig);
        const char * fieldSig = (char *) J9UTF8_DATA(nameUTF);
        return classData->isFieldInlined(fieldSig,"");
    }
    return true;
}

bool StaticAnalysisUtils::fieldInliningPreferenceWithRom(J9ROMClass *fieldClass, J9ROMFieldShape* field){
    J9UTF8* className = J9ROMCLASS_CLASSNAME(fieldClass);
    const char * classNameStr = (char *) J9UTF8_DATA(className);
    // printf("Trying to check status of field of Container Class: %s\n",classNameStr);
    IFM_ClassMetadata * classData = getClassMetadata(classNameStr);
    if(classData != NULL)
    {
        J9ROMNameAndSignature *nameAndSig = &field->nameAndSignature;
		J9UTF8 *signUTF = J9ROMNAMEANDSIGNATURE_NAME(nameAndSig);
        const char * fieldSig = (char *) J9UTF8_DATA(signUTF);
        return classData->isFieldInlined(fieldSig,"");
    }
    return true;
}

IFM_ClassMetadata * StaticAnalysisUtils::getClassMetadata(const char * className)
{
//    for (auto it = StaticAnalysisUtils::getStaticRes().begin(); it != StaticAnalysisUtils::getStaticRes().end(); ++it)
//    {
//         const char * element_className =  (*it)->getClassName();
//         if (!strcmp(element_className, className))
//         {
//             return (IFM_ClassMetadata *)(*it);
//         }
//    }

    std::vector<IFM_ClassMetadata *> staticRes = StaticAnalysisUtils::getStaticRes();
    for(size_t i = 0; i < staticRes.size(); ++i) 
    {
        const char * element_className =  staticRes[i]->getClassName();
        // printf("2. Class Name inside res file: %s\n",element_className);
        // printf("2. Class Name for comparison: %s\n",className);
        // printf("2. Comparison result: %d\n",strncmp(element_className, className,strlen(element_className)));
        // printf("Element: %s\n",element_className);
        if (strncmp(element_className, className,strlen(element_className)) == 0)
        {
            return staticRes[i];
        }
    }
   return NULL;
}

std::vector<IFM_ClassMetadata *> StaticAnalysisUtils::getStaticRes()
{
    return StaticAnalysisUtils::staticResults;
}

// SPM_StaticProfilingMetadata * StaticAnalysisUtils::getProfileData()
// {
//     return StaticAnalysisUtils::profilingData;
// }

void StaticAnalysisUtils::clearResults()
{
    std::vector<IFM_ClassMetadata *> staticRes = StaticAnalysisUtils::getStaticRes();
    for(size_t i = 0; i < staticRes.size(); ++i) 
    {
        IFM_ClassMetadata * element = staticRes[i];
        char * element_className =  (char *)element->getClassName();
        element->clearResults();
        free(element_className);
        delete(element);
    }

    // if(NULL != StaticAnalysisUtils::profilingData)
    // {
    //     StaticAnalysisUtils::getProfileData()->clearResults();
    // }


}

void StaticAnalysisUtils::addCallSiteProfileData(SPM_StaticProfileInfo * staticProfileInfo)
{
    // if(NULL == StaticAnalysisUtils::profilingData)
    // {
    //     SPM_StaticProfilingMetadata * profileMetadata = (SPM_StaticProfilingMetadata *) malloc (sizeof(SPM_StaticProfilingMetadata));
    //     // StaticAnalysisUtils::profilingData = (SPM_StaticProfilingMetadata *) malloc (sizeof(SPM_StaticProfilingMetadata));
    //      std::vector<SPM_StaticProfileInfo *> callSiteProfilingDataCopy;
    //      callSiteProfilingDataCopy.push_back(staticProfileInfo);
    //      profileMetadata->callSiteProfilingData = callSiteProfilingDataCopy;
    //      StaticAnalysisUtils::profilingData = profileMetadata;
    // }
    // else
    // {
        SPM_StaticProfilingMetadata * profileMetadata = StaticAnalysisUtils::getProfileData();
        // std::vector<SPM_StaticProfileInfo *> callSiteProfilingDataCopy = profileMetadata->callSiteProfilingData;
        profileMetadata->callSiteProfilingData.push_back(staticProfileInfo);
    // }
    // std::vector<SPM_StaticProfileInfo *> callSiteProfilingData = StaticAnalysisUtils::profilingData->callSiteProfilingData;
    // // if(callSiteProfilingData.empty)
    // // {
   
    //     callSiteProfilingData.push_back(staticProfileInfo);
        
    // }
}

bool StaticAnalysisUtils::getProfilingPreference4CallSite(char * methodSig, uint32_t bci)
{
    if(NULL != StaticAnalysisUtils::profilingData)
    {
        SPM_StaticProfilingMetadata * profilingMetadata = StaticAnalysisUtils::profilingData;
        return profilingMetadata->getCallSitePreference(methodSig, bci);
    }
    return false;
}

const char * StaticAnalysisUtils::getDebugCounterName(char * methodSig, uint32_t bci)
 {
    if(NULL != StaticAnalysisUtils::profilingData)
    {
        return StaticAnalysisUtils::profilingData->getDebugCounterName(methodSig,bci);
    }
    return NULL;
 }