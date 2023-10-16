#if !defined(STATIC_PROFILE_STORAGE_HPP_)
#define STATIC_PROFILE_STORAGE_HPP_

#include "StaticProfilingSite.hpp"
#include "compile/ResolvedMethod.hpp"
// #include "vm/StaticAnalysisUtils.hpp"
// #include "vm/StaticProfilingMetadata.hpp"
/* AR07 - This file stores the sites where the VM needs to profile further */


class StaticProfileStorage 
{
    //Members:
    private:

    public:
    static SPM_StaticProfile * profilingData;
    static SPM_StaticProfile * getProfilingData();
    static bool getProfilingPreference4CallSite(TR_ResolvedMethod * _method, uint32_t bci);
    static const char * getDebugCounterName(TR_ResolvedMethod * _method, uint32_t bci);
    // static void readStaticProfileInfo();
};

#endif /* STATIC_PROFILE_STORAGE_HPP_ */