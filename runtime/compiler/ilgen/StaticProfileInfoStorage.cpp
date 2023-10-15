
#include "StaticProfileInfoStorage.hpp"
#include "StaticProfilingSite.hpp"
/* AR07 - This file stores the sites where the VM needs to profile further */

SPM_StaticProfile * StaticProfileStorage::profilingData = NULL;

void readStaticProfileInfo(SPM_StaticProfile * staticProfile);

const char * createCopy(char * targetString) 
{
    char * classSignature = NULL;
    if( targetString != NULL)
    {
        classSignature = (char *) malloc (strlen(targetString));
        strcpy(classSignature, targetString);
        
    }
    return classSignature;
}

SPM_StaticProfile * StaticProfileStorage::getProfilingData()
{
    if(NULL == StaticProfileStorage::profilingData)
    {
        SPM_StaticProfile * staticProfileMem = (SPM_StaticProfile *) malloc (sizeof(SPM_StaticProfile));
        SPM_StaticProfile* staticProfile = new (staticProfileMem) SPM_StaticProfile();
        readStaticProfileInfo(staticProfile);
        StaticProfileStorage::profilingData = staticProfile;
    }
    return StaticProfileStorage::profilingData;
}


void readStaticProfileInfo(SPM_StaticProfile * staticProfile)
{
    FILE *file = fopen("static_results/callSites.out", "r");
    if (file==NULL)
    {
        printf("Static results for callsites does not exist.\n");
        return;
    }
    // StaticAnalysisUtils::staticResults = (IFM_ClassMetadata *) malloc (sizeof(IFM_ClassMetadata));
    char * line = NULL;
    size_t len = 1000;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) 
    {
        char _delim[] = "\t\n";
        char * signature = strtok(line, _delim);
        const char * methodSignature = createCopy(signature);
        // printf("Classname: %s.\n",classSignature);
        SPM_StaticProfileInfo* mem = (SPM_StaticProfileInfo *) malloc (sizeof(SPM_StaticProfileInfo));
        char * bci = strtok(NULL, _delim);
        const char * methodBCI = createCopy(bci);
        char * ID = strtok(NULL, _delim);
        const char * siteID = createCopy(ID);
        if (methodBCI != NULL && siteID != NULL) 
        {
            int _bci = atoi(methodBCI);
            int _id = atoi(siteID);
            SPM_StaticProfileInfo* siteData = new (mem) SPM_StaticProfileInfo(methodSignature,_id,_bci);
            std::vector<SPM_StaticProfileInfo *> callSiteVector = staticProfile->callSiteProfilingData;
            callSiteVector.push_back(siteData);  
            staticProfile->callSiteProfilingData = callSiteVector;
        }
    }
}

bool StaticProfileStorage::getProfilingPreference4CallSite(char * methodSig, uint32_t bci)
{
    SPM_StaticProfile * staticProfile = StaticProfileStorage::getProfilingData();
    if(NULL != staticProfile)
    {
        return staticProfile->getCallSitePreference(methodSig, bci);
    }
    return false;
}

const char * StaticProfileStorage::getDebugCounterName(char * methodSig, uint32_t bci)
 {
    SPM_StaticProfile * staticProfile = StaticProfileStorage::getProfilingData();
    if(NULL != staticProfile)
    {
        return staticProfile->getDebugCounterName(methodSig,bci);
    }
    return NULL;
 }