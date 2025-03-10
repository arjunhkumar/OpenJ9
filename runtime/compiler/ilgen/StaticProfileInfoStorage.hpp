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
    static SPM_StaticProfile * profilingData;

    // Functions
    public:
    // Getters
    static SPM_StaticProfile * getProfilingData();
    static bool isStaticProfilingMode(J9JavaVM *javaVM);
    // Call-Site Utils
    static bool getProfilingPreference4CallSite(TR_ResolvedMethod * _method, uint32_t bci);
    static const char * getDebugCounterName4CallSite(TR_ResolvedMethod * _method, uint32_t bci);
    // Return-Site Utils
    static bool getProfilingPreference4ReturnSite(TR_ResolvedMethod * _method, uint32_t bci);
    static const char * getDebugCounterName4ReturnSite(TR_ResolvedMethod * _method, uint32_t bci);
    // Static-Assign Site Utils
    static bool getProfilingPreference4SASite(TR_ResolvedMethod * _method, uint32_t bci);
    static const char * getDebugCounterName4SASite(TR_ResolvedMethod * _method, uint32_t bci);
    // TypeCast-Site Utils
    static bool getProfilingPreference4CastSite(TR_ResolvedMethod * _method, uint32_t bci);
    static const char * getDebugCounterName4CastSite(TR_ResolvedMethod * _method, uint32_t bci);
    // Equals-Site Utils
    static bool getProfilingPreference4EqualsSite(TR_ResolvedMethod * _method, uint32_t bci);
    static const char * getDebugCounterName4EqualsSite(TR_ResolvedMethod * _method, uint32_t bci);
    // Load-store utils
    static const char * getDebugCounterName4FieldLoad(char * className, U_16 classNameLength, char * fieldName, U_16 fieldNameLength);
    static const char * getDebugCounterName4FieldStore(char * className, U_16 classNameLength, char * fieldName, U_16 fieldNameLength);
};

#endif /* STATIC_PROFILE_STORAGE_HPP_ */