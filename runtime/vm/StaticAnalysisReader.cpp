#include <fstream>
#include "StaticAnalysisReader.hpp"
#include "InlineableFieldMetadata.hpp"

static std::vector<IFM_ClassMetadata *> staticResults;

void readStaticResults(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file==NULL)
    {
        printf("Static analysis results does not exist.\n");
        return;
    }
    char * line = NULL;
    size_t len = 1000;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) 
    {
        char classname_delim[] = "&&";
        char * signature = strtok(line, classname_delim);
        printf("Classname: %s.\n",signature);
        IFM_ClassMetadata classMetadataObj = IFM_ClassMetadata(signature);
        IFM_ClassMetadata* classMetadata = &classMetadataObj;
        signature = strtok(NULL, classname_delim);
        while (signature != NULL) 
        {
            classMetadata->addField(signature,NULL);
            printf("Field: %s.\n",signature);
            signature = strtok(NULL, classname_delim);
        }
        staticResults.push_back(classMetadata);
        printf("End of class.\n");
    }

}