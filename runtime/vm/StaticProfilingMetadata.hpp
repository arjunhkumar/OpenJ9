#if !defined(STATIC_PROFILE_METADATA_HPP)
#define STATIC_PROFILE_METADATA_HPP

#include <vector>
#include "j9.h"
#include <string.h>


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

    static  U_32 getByteCodeIndex(SPM_StaticProfileInfo * profileInfo);

    const char * createCopy(const char * targetString);

};


class SPM_StaticProfilingMetadata 
{
   private:

    public:
    // bool methodProfilingPreference4CallSite(TR_ResolvedMethod *method);

    // bool bciProfilingPreference4CallSite(TR_ResolvedMethod *method, TR::Node* node);
    
    // void putProfilingDebugCounter(TR_ResolvedMethod *method, TR::Node* node, TR::TreeTop *tt);
    std::vector<SPM_StaticProfileInfo *> callSiteProfilingData;
    std::vector<SPM_StaticProfileInfo *> returnSiteProfilingData;
    std::vector<SPM_StaticProfileInfo *> staticAssignSiteProfilingData;

    std::vector<SPM_StaticProfileInfo *> getCallSiteProfile();
    
    std::vector<SPM_StaticProfileInfo *> getReturnSiteProfile();
    
    std::vector<SPM_StaticProfileInfo *> getStaticAssignSiteProfile();

    bool getCallSitePreference(char * methodSignature, uint32_t bci);

    const char * getDebugCounterName(char * methodSignature, uint32_t bci);

    // SPM_StaticProfileInfo * getProfilingInfo4CallSite(TR_ResolvedMethod *method,uint32_t bci);

    void clearResults();

};

#endif /* STATIC_PROFILE_METADATA_HPP */
