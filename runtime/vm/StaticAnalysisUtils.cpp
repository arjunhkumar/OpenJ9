#include <fstream>
#include "InlineableFieldMetadata.hpp"
#include "StaticAnalysisUtils.hpp"

static std::vector<IFM_ClassMetadata *> staticResults;

bool fieldInliningPreference(J9Class *fieldClass, J9ROMFieldShape* field){
    J9UTF8* className = J9ROMCLASS_CLASSNAME(fieldClass->romClass);
    const char * classNameStr = (char *) J9UTF8_DATA(className);
    printf("Trying to check status of field of Container Class: %s\n",classNameStr);
    IFM_ClassMetadata * classData = getClassMetadata(classNameStr);
    if(classData != NULL)
    {
        J9ROMNameAndSignature *nameAndSig = &field->nameAndSignature;
		J9UTF8 *nameUTF = J9ROMNAMEANDSIGNATURE_NAME(nameAndSig);
        const char * fieldSig = (char *) J9UTF8_DATA(nameUTF);
        return classData->isFieldInlined(fieldSig,"");
    }
    return true;
}

bool fieldInliningPreferenceWithRom(J9ROMClass *fieldClass, J9ROMFieldShape* field){
    J9UTF8* className = J9ROMCLASS_CLASSNAME(fieldClass);
    const char * classNameStr = (char *) J9UTF8_DATA(className);
    printf("Trying to check status of field of Container Class: %s\n",classNameStr);
    IFM_ClassMetadata * classData = getClassMetadata(classNameStr);
    if(classData != NULL)
    {
        J9ROMNameAndSignature *nameAndSig = &field->nameAndSignature;
		J9UTF8 *nameUTF = J9ROMNAMEANDSIGNATURE_NAME(nameAndSig);
        const char * fieldSig = (char *) J9UTF8_DATA(nameUTF);
        return classData->isFieldInlined(fieldSig,"");
    }
    return true;
}

IFM_ClassMetadata * getClassMetadata(const char * className)
{
   for (std::vector<IFM_ClassMetadata *>::iterator i = staticResults.begin(); i != staticResults.end(); ++i)
   {
        IFM_ClassMetadata * element = (IFM_ClassMetadata *)*i;
        const char * element_className =  element->getClassName();
        if (!strcmp(element_className, className))
        {
            return element;
        }
   }
   return NULL;
}
