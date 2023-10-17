
#include "StaticProfileInfoStorage.hpp"
#include "StaticProfilingSite.hpp"
/* AR07 - This file stores the sites where the VM needs to profile further */

// Declarations
SPM_StaticProfile * StaticProfileStorage::profilingData = NULL;
void readStaticProfileInfo4CallSite(SPM_StaticProfile * staticProfile);
void readStaticProfileInfo4ReturnSite(SPM_StaticProfile * staticProfile);
void readStaticProfileInfo4SASite(SPM_StaticProfile * staticProfile);
char * createCopy(char * targetString);

// Utils and Getters
bool StaticProfileStorage::isStaticProfilingMode(J9JavaVM *javaVM)
{
    return J9_ARE_ALL_BITS_SET(javaVM->extendedRuntimeFlags2, J9_EXTENDED_RUNTIME_PROFILE_STATIC_SITES);
}

SPM_StaticProfile * StaticProfileStorage::getProfilingData()
{
    if(NULL == StaticProfileStorage::profilingData)
    {
        SPM_StaticProfile * staticProfileMem = (SPM_StaticProfile *) malloc (sizeof(SPM_StaticProfile));
        SPM_StaticProfile* staticProfile = new (staticProfileMem) SPM_StaticProfile();
        readStaticProfileInfo4CallSite(staticProfile);
        readStaticProfileInfo4ReturnSite(staticProfile);
        readStaticProfileInfo4SASite(staticProfile);
        StaticProfileStorage::profilingData = staticProfile;
    }
    return StaticProfileStorage::profilingData;
}

char * createCopy(char * targetString) 
{
    char * classSignature = NULL;
    if( targetString != NULL)
    {
        classSignature = (char *) malloc (strlen(targetString)+1);
        strcpy(classSignature, targetString);
        
    }
    return classSignature;
}

void readStaticProfileInfo4CallSite(SPM_StaticProfile * staticProfile)
{
    FILE *file = fopen("static_results/CallSites.out", "r");
    if (file==NULL)
    {
        printf("Static results for Call-Site(s) does not exist.\n");
        return;
    }
    char * line = NULL;
    size_t len = 1000;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) 
    {
        char _delim[] = "\t\n";
        char * signature = strtok(line, _delim);
        char * methodSignature = createCopy(signature);
        SPM_StaticProfileInfo* mem = (SPM_StaticProfileInfo *) malloc (sizeof(SPM_StaticProfileInfo));
        char * bci = strtok(NULL, _delim);
        char * methodBCI = createCopy(bci);
        char * ID = strtok(NULL, _delim);
        char * siteID = createCopy(ID);
        if (methodBCI != NULL && siteID != NULL) 
        {
            int _bci = atoi(methodBCI);
            int _id = atoi(siteID);
            SPM_StaticProfileInfo* siteData = new (mem) SPM_StaticProfileInfo(methodSignature,_id,_bci);
            std::vector<SPM_StaticProfileInfo *> callSiteVector = staticProfile->callSiteProfilingData;
            callSiteVector.push_back(siteData);  
            staticProfile->callSiteProfilingData = callSiteVector;
        }
        // free(methodSignature);
        free(methodBCI);
        free(siteID);
    }
    if (file)
    {
        fclose(file);
    }
}

void readStaticProfileInfo4ReturnSite(SPM_StaticProfile * staticProfile)
{
    FILE *file = fopen("static_results/ReturnSites.out", "r");
    if (file==NULL)
    {
        printf("Static results for Return-Site(s) does not exist.\n");
        return;
    }
    char * line = NULL;
    size_t len = 1000;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) 
    {
        char _delim[] = "\t\n";
        char * signature = strtok(line, _delim);
        char * methodSignature = createCopy(signature);
        SPM_StaticProfileInfo* mem = (SPM_StaticProfileInfo *) malloc (sizeof(SPM_StaticProfileInfo));
        char * bci = strtok(NULL, _delim);
        char * methodBCI = createCopy(bci);
        char * ID = strtok(NULL, _delim);
        char * siteID = createCopy(ID);
        if (methodBCI != NULL && siteID != NULL) 
        {
            int _bci = atoi(methodBCI);
            int _id = atoi(siteID);
            SPM_StaticProfileInfo* siteData = new (mem) SPM_StaticProfileInfo(methodSignature,_id,_bci);
            std::vector<SPM_StaticProfileInfo *> returnSiteVector = staticProfile->returnSiteProfilingData;
            returnSiteVector.push_back(siteData);  
            staticProfile->returnSiteProfilingData = returnSiteVector;
        }
        // free(methodSignature);
        free(methodBCI);
        free(siteID);
    }
    if (file)
    {
        fclose(file);
    }
}

void readStaticProfileInfo4SASite(SPM_StaticProfile * staticProfile)
{
    FILE *file = fopen("static_results/StaticAssignSites.out", "r");
    if (file==NULL)
    {
        printf("Static results for Static-Assign Site(s) does not exist.\n");
        return;
    }
    char * line = NULL;
    size_t len = 1000;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) 
    {
        char _delim[] = "\t\n";
        char * signature = strtok(line, _delim);
        char * methodSignature = createCopy(signature);
        SPM_StaticProfileInfo* mem = (SPM_StaticProfileInfo *) malloc (sizeof(SPM_StaticProfileInfo));
        char * bci = strtok(NULL, _delim);
        char * methodBCI = createCopy(bci);
        char * ID = strtok(NULL, _delim);
        char * siteID = createCopy(ID);
        if (methodBCI != NULL && siteID != NULL) 
        {
            int _bci = atoi(methodBCI);
            int _id = atoi(siteID);
            SPM_StaticProfileInfo* siteData = new (mem) SPM_StaticProfileInfo(methodSignature,_id,_bci);
            std::vector<SPM_StaticProfileInfo *> staticAssignSiteVector = staticProfile->staticAssignSiteProfilingData;
            staticAssignSiteVector.push_back(siteData);  
            staticProfile->staticAssignSiteProfilingData = staticAssignSiteVector;
        }
        // free(methodSignature);
        free(methodBCI);
        free(siteID);
    }
    if (file)
    {
        fclose(file);
    }
}

// void readStaticProfileInfo4CallSite(SPM_StaticProfile * staticProfile)
// {
//     FILE *file = fopen("static_results/callSites.out", "r");
//     if (file==NULL)
//     {
//         printf("Static results for callsites does not exist.\n");
//         return;
//     }
//     char * line = NULL;
//     size_t len = 1000;
//     ssize_t read;

//     while ((read = getline(&line, &len, file)) != -1) 
//     {
//         char _delim[] = "\t\n";
//         char * signature = strtok(line, _delim);
//         char * methodSignature = createCopy(signature);
//         SPM_StaticProfileInfo* mem = (SPM_StaticProfileInfo *) malloc (sizeof(SPM_StaticProfileInfo));
//         char * bci = strtok(NULL, _delim);
//         char * methodBCI = createCopy(bci);
//         char * ID = strtok(NULL, _delim);
//         char * siteID = createCopy(ID);
//         if (methodBCI != NULL && siteID != NULL) 
//         {
//             int _bci = atoi(methodBCI);
//             int _id = atoi(siteID);
//             SPM_StaticProfileInfo* siteData = new (mem) SPM_StaticProfileInfo(methodSignature,_id,_bci);
//             std::vector<SPM_StaticProfileInfo *> callSiteVector = staticProfile->callSiteProfilingData;
//             callSiteVector.push_back(siteData);  
//             staticProfile->callSiteProfilingData = callSiteVector;
//         }
//     }
// }

// Call-Site Utils
bool StaticProfileStorage::getProfilingPreference4CallSite(TR_ResolvedMethod * _method, uint32_t bci)
{
    SPM_StaticProfile * staticProfile = StaticProfileStorage::getProfilingData();
    if(NULL != staticProfile)
    {
        return staticProfile->getPreference4CallSite(_method, bci);
    }
    return false;
}

const char * StaticProfileStorage::getDebugCounterName4CallSite(TR_ResolvedMethod * _method, uint32_t bci)
{
    SPM_StaticProfile * staticProfile = StaticProfileStorage::getProfilingData();
    if(NULL != staticProfile)
    {
        return staticProfile->getDebugCounterName4CallSite(_method,bci);
    }
    return NULL;
}

// Return-Site Utils
bool StaticProfileStorage::getProfilingPreference4ReturnSite(TR_ResolvedMethod * _method, uint32_t bci)
{
    SPM_StaticProfile * staticProfile = StaticProfileStorage::getProfilingData();
    if(NULL != staticProfile)
    {
        return staticProfile->getPreference4ReturnSite(_method, bci);
    }
    return false;
}

const char * StaticProfileStorage::getDebugCounterName4ReturnSite(TR_ResolvedMethod * _method, uint32_t bci)
{
    SPM_StaticProfile * staticProfile = StaticProfileStorage::getProfilingData();
    if(NULL != staticProfile)
    {
        return staticProfile->getDebugCounterName4ReturnSite(_method,bci);
    }
    return NULL;
}

// Static-Assign Site Utils
bool StaticProfileStorage::getProfilingPreference4SASite(TR_ResolvedMethod * _method, uint32_t bci)
{
    SPM_StaticProfile * staticProfile = StaticProfileStorage::getProfilingData();
    if(NULL != staticProfile)
    {
        return staticProfile->getPreference4SASite(_method, bci);
    }
    return false;
}

const char * StaticProfileStorage::getDebugCounterName4SASite(TR_ResolvedMethod * _method, uint32_t bci)
{
    SPM_StaticProfile * staticProfile = StaticProfileStorage::getProfilingData();
    if(NULL != staticProfile)
    {
        return staticProfile->getDebugCounterName4SASite(_method,bci);
    }
    return NULL;
}