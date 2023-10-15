// #if !defined(STATIC_ANALYSIS_UTILS_HPP_)
// #define STATIC_ANALYSIS_UTILS_HPP_
#ifndef STATIC_ANALYSIS_UTILS_HPP_
#define STATIC_ANALYSIS_UTILS_HPP_

#include <stdlib.h>
#include <string.h>
#include "j9.h"
#include "InlineableFieldMetadata.hpp"
#include "StaticProfilingMetadata.hpp"

/* AR07 - This file takes care of all the functions required to read static analysis 
    for flattening as well as retrieving the field level preference during JIT. */


class StaticAnalysisUtils 
{
    private:
    static SPM_StaticProfilingMetadata * profilingData;

    public:

    static int value_debug;

    static std::vector<IFM_ClassMetadata *> staticResults;

    static bool fieldInliningPreference(J9Class *fieldClass, J9ROMFieldShape* field);

    static bool fieldInliningPreferenceWithRom(J9ROMClass* fieldClass, J9ROMFieldShape* field);

    static IFM_ClassMetadata * getClassMetadata(const char * className);

    static std::vector<IFM_ClassMetadata *> getStaticRes();

    static SPM_StaticProfilingMetadata * getProfileData()
    {
        // SPM_StaticProfilingMetadata * StaticAnalysisUtils::profilingData;
        // if(StaticAnalysisUtils::profilingData == NULL)
        // {
        //     StaticAnalysisUtils::profilingData = (SPM_StaticProfilingMetadata *) malloc (sizeof(SPM_StaticProfilingMetadata));
        // }
        return profilingData;
    }
    
    static void addCallSiteProfileData(SPM_StaticProfileInfo * staticProfileInfo);

    static bool getProfilingPreference4CallSite(char * methodSig, uint32_t bci);

    static const char * getDebugCounterName(char * methodSig, uint32_t bci);

    static void clearResults();


};    
#endif /* STATIC_ANALYSIS_UTILS_HPP_ */ 