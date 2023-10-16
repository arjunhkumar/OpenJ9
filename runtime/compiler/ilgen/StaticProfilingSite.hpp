#if !defined(STATIC_PROFILE_INFO_HPP_)
#define STATIC_PROFILE_INFO_HPP_

/* AR07 - This file stores the ds to store where the VM needs to profile further */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "j9.h"
#include "compile/ResolvedMethod.hpp"


class SPM_StaticProfileInfo 
{
    private:
    const char * _methodSignature;
    U_32 _id;
    U_32 _bco;

    public:
    SPM_StaticProfileInfo(char const *methodSignature,U_32 identifier,U_32 bci) :
        _methodSignature(methodSignature),
        _id(identifier),
        _bco(bci)
    {}

    const char * getMethodSignature();

    U_32 getID();

    U_32 getBCI();

    // const char * createCopy(const char * targetString);

};

class SPM_StaticProfile
{
    private:

    
    public:
    std::vector<SPM_StaticProfileInfo *> callSiteProfilingData;
    std::vector<SPM_StaticProfileInfo *> returnSiteProfilingData;
    std::vector<SPM_StaticProfileInfo *> staticAssignSiteProfilingData;
    std::vector<SPM_StaticProfileInfo *> getCallSiteProfile();
    
    std::vector<SPM_StaticProfileInfo *> getReturnSiteProfile();
    
    std::vector<SPM_StaticProfileInfo *> getStaticAssignSiteProfile();

    bool getCallSitePreference(char * methodSignature, uint32_t bci);
    const char * getDebugCounterName(char * methodSignature, uint32_t bci);
    
    // CALL-SITE PROFILING
    bool getPreference4CallSite(TR_ResolvedMethod * _method, uint32_t bci);
    const char * getDebugCounterName4CallSite(TR_ResolvedMethod * _method, uint32_t bci);
    // RETURN-SITE PROFILING
    bool getPreference4ReturnSite(TR_ResolvedMethod * _method, uint32_t bci);
    const char * getDebugCounterName4ReturnSite(TR_ResolvedMethod * _method, uint32_t bci);
    // STATIC-ASSIGN SITE PROFILING
    bool getPreference4SASite(TR_ResolvedMethod * _method, uint32_t bci);
    const char * getDebugCounterName4SASite(TR_ResolvedMethod * _method, uint32_t bci);

    void clearResults();
};

#endif /* STATIC_PROFILE_INFO_HPP_ */
