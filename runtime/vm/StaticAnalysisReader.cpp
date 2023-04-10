#include <fstream>
#include <stdio.h>
#include "StaticAnalysisReader.hpp"
#include "StaticAnalysisUtils.hpp"
#include "InlineableFieldMetadata.hpp"

/* AR07 - This file takes care of all the functions required to read static analysis 
    for flattening as well as retrieving the field level preference during JIT. */

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
        char classname_delim[] = " \t\r\n";
        char * signature = strtok(line, classname_delim);
        const char * classSignature = createCopy(signature);
        // printf("Classname: %s.\n",classSignature);
        IFM_ClassMetadata* mem = (IFM_ClassMetadata *) malloc (sizeof(IFM_ClassMetadata));
        IFM_ClassMetadata* classMetadata = new (mem) IFM_ClassMetadata(classSignature);
        signature = strtok(NULL, classname_delim);
        while (signature != NULL) 
        {
            classMetadata->addField(signature,NULL);
            // printf("Field: %s.\n",signature);
            signature = strtok(NULL, classname_delim);
        }
        StaticAnalysisUtils::staticResults.push_back(classMetadata);
        // printf("End of class.\n");
    }

}

IFM_ClassMetadata * getClassMetadata(const char * className)
{
    std::vector<IFM_ClassMetadata *> staticRes = StaticAnalysisUtils::getStaticRes();
    for(size_t i = 0; i < staticRes.size(); ++i) 
    {
        const char * element_className =  staticRes[i]->getClassName();
        // printf("1. Class Name inside res file: %s\n",element_className);
        // printf("1. Class Name for comparison: %s\n",className);
        // printf("1. Comparison result: %d\n",strncmp(element_className, className,strlen(element_className)));
        // printf("Element: %s\n",element_className);
        if (strncmp(element_className, className,strlen(element_className)) == 0)
        {
            return staticRes[i];
        }
    }
   return NULL;
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

int fieldInliningPreference(J9Class *fieldClass, J9ROMFieldShape* field)
{
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
    return 1;
}

int fieldInliningPreferenceWithRom(J9ROMClass* fieldClass, J9ROMFieldShape* field)
{
    J9UTF8* className = J9ROMCLASS_CLASSNAME(fieldClass);
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
    return 1;
}
