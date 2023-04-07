#include <fstream>
#include "InlineableFieldMetadata.hpp"
#include "StaticAnalysisUtils.hpp"

std::vector<IFM_ClassMetadata *> StaticAnalysisUtils::staticResults;

bool StaticAnalysisUtils::fieldInliningPreference(J9Class *fieldClass, J9ROMFieldShape* field){
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

bool StaticAnalysisUtils::fieldInliningPreferenceWithRom(J9ROMClass *fieldClass, J9ROMFieldShape* field){
    J9UTF8* className = J9ROMCLASS_CLASSNAME(fieldClass);
    const char * classNameStr = (char *) J9UTF8_DATA(className);
    printf("Trying to check status of field of Container Class: %s\n",classNameStr);
    IFM_ClassMetadata * classData = getClassMetadata(classNameStr);
    if(classData != NULL)
    {
        J9ROMNameAndSignature *nameAndSig = &field->nameAndSignature;
		J9UTF8 *signUTF = J9ROMNAMEANDSIGNATURE_SIGNATURE(nameAndSig);
        const char * fieldSig = (char *) J9UTF8_DATA(signUTF);
        return classData->isFieldInlined(fieldSig,"");
    }
    return true;
}

IFM_ClassMetadata * StaticAnalysisUtils::getClassMetadata(const char * className)
{
//    for (auto it = StaticAnalysisUtils::getStaticRes().begin(); it != StaticAnalysisUtils::getStaticRes().end(); ++it)
//    {
//         const char * element_className =  (*it)->getClassName();
//         if (!strcmp(element_className, className))
//         {
//             return (IFM_ClassMetadata *)(*it);
//         }
//    }

    std::vector<IFM_ClassMetadata *> staticRes = StaticAnalysisUtils::getStaticRes();
    for(size_t i = 0; i < staticRes.size(); ++i) 
    {
        const char * element_className =  staticRes[i]->getClassName();
        printf("Element: %s\n",element_className);
        if (strcmp(element_className, className))
        {
            return staticRes[i];
        }
    }
   return NULL;
}

std::vector<IFM_ClassMetadata *> StaticAnalysisUtils::getStaticRes()
{
    return StaticAnalysisUtils::staticResults;
}

void StaticAnalysisUtils::clearResults()
{
    // for (std::vector<IFM_ClassMetadata *>::iterator i = StaticAnalysisUtils::getStaticRes().begin(); i != StaticAnalysisUtils::getStaticRes().end(); ++i)
    // {
    //     IFM_ClassMetadata * element = (IFM_ClassMetadata *)*i;
    //     char * element_className =  (char *)element->getClassName();
    //     element->clearResults();
    //     free(element_className);
    //     delete(element);
    // }

    std::vector<IFM_ClassMetadata *> staticRes = StaticAnalysisUtils::getStaticRes();
    for(size_t i = 0; i < staticRes.size(); ++i) 
    {
        IFM_ClassMetadata * element = staticRes[i];
        char * element_className =  (char *)element->getClassName();
        element->clearResults();
        free(element_className);
        delete(element);
    }


}
