#include <fstream>
#include "StaticAnalysisReader.hpp"
#include "StaticAnalysisUtils.hpp"
#include "InlineableFieldMetadata.hpp"


void readStaticResults(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file==NULL)
    {
        printf("Static analysis results does not exist.\n");
        return;
    }
    // StaticAnalysisUtils::staticResults = (IFM_ClassMetadata *) malloc (sizeof(IFM_ClassMetadata));
    char * line = NULL;
    size_t len = 1000;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) 
    {
        char classname_delim[] = "&&";
        char * signature = strtok(line, classname_delim);
        const char * classSignature = createCopy(signature);
        printf("Classname: %s.\n",classSignature);
        IFM_ClassMetadata* mem = (IFM_ClassMetadata *) malloc (sizeof(IFM_ClassMetadata));
        IFM_ClassMetadata* classMetadata = new (mem) IFM_ClassMetadata(classSignature);
        signature = strtok(NULL, classname_delim);
        while (signature != NULL) 
        {
            classMetadata->addField(signature,NULL);
            printf("Field: %s.\n",signature);
            signature = strtok(NULL, classname_delim);
        }
        StaticAnalysisUtils::staticResults.push_back(classMetadata);
        printf("End of class.\n");
    }

}

const char * createCopy(char * targetString) 
{
    char * classSignature;
    if( targetString != NULL)
    {
        classSignature = (char *) malloc (strlen(targetString));
        strcpy(classSignature, targetString);
        
    }
    return classSignature;
}