#include "InlineableFieldMetadata.hpp"
#include <stdlib.h>
#include <string.h>

const char * IFM_ClassFieldMetadata::getFieldName()
{
    return _fieldName;
}

const char * IFM_ClassFieldMetadata::getFieldSign()
{
    return _fieldSign;
}

void IFM_ClassMetadata::addField(char const *fieldName,char const *fieldSign)
{
    /* IFM_ClassFieldMetadata *fieldMetadata = new IFM_ClassFieldMetadata(fieldName,fieldSign);
        IFM_ClassFieldMetadata* fieldMetadata = &fieldMetadataObj; */
    const char * _fieldName = createCopy(fieldName);
    const char * _fieldSign = createCopy(fieldSign);
    IFM_ClassFieldMetadata* mem = (IFM_ClassFieldMetadata *) malloc (sizeof(IFM_ClassFieldMetadata));
    IFM_ClassFieldMetadata* fieldMetadata = new (mem) IFM_ClassFieldMetadata(_fieldName,_fieldSign);
    inlineableFieldList.push_back(fieldMetadata);
}

bool IFM_ClassMetadata::isFieldInlined(char const *fieldName,char const *fieldSign)
{
    // for (std::vector<IFM_ClassFieldMetadata *>::iterator i = inlineableFieldList.begin(); i != inlineableFieldList.end(); ++i)
    // {
    //         IFM_ClassFieldMetadata * element = (IFM_ClassFieldMetadata *)*i;
    //         const char * elementFieldName =  element->getFieldName();
    //         if (!strcmp(elementFieldName, fieldName))
    //         {
    //             return false;
    //         }
    // }
    for(size_t i = 0; i < inlineableFieldList.size(); ++i) 
    {
        IFM_ClassFieldMetadata * element = inlineableFieldList[i];
        const char * elementFieldName =  element->getFieldName();
        if (strcmp(elementFieldName, fieldName))
        {
            return false;
        }
    }
    return true;
}

const char * IFM_ClassMetadata::createCopy(const char * targetString) 
{
    char * classSignature;
    if( targetString != NULL)
    {
        classSignature = (char *) malloc (strlen(targetString));
        strcpy(classSignature, targetString);
        
    }
    return classSignature;
}

void IFM_ClassMetadata::clearResults()
{
    // for (std::vector<IFM_ClassFieldMetadata *>::iterator i = inlineableFieldList.begin(); i != inlineableFieldList.end(); ++i)
    // {
    //     IFM_ClassFieldMetadata * element = (IFM_ClassFieldMetadata *)*i;
    //     char * elementFieldName =  (char *)element->getFieldName();
    //     free(elementFieldName);
    //     delete(element);
    // }
    for(size_t i = 0; i < inlineableFieldList.size(); ++i) 
    {
        IFM_ClassFieldMetadata * element = inlineableFieldList[i];
        char * elementFieldName =  (char *)element->getFieldName();
        free(elementFieldName);
        delete(element);
    }

}

const char * IFM_ClassMetadata::getClassName()
{
    return _className;
}