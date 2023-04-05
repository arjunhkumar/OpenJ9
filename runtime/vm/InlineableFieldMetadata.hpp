#if !defined(INLINEABLE_FIELD_METADATA_HPP)
#define INLINEABLE_FIELD_METADATA_HPP

#include <vector>
#include <string.h>

class IFM_ClassFieldMetadata 
{
   private:
    const char * _fieldName;
    const char * _fieldSign;

    public:
    IFM_ClassFieldMetadata(char const *fieldName,char const *fieldSign) :
		_fieldName(fieldName),
        _fieldSign(fieldSign)
	{}

	const char * getFieldName()
    {
        return _fieldName;
    }

    const char * getFieldSign()
    {
        return _fieldSign;
    }

};


class IFM_ClassMetadata 
{
   private:
   const char * _className;
   std::vector<IFM_ClassFieldMetadata *> inlineableFieldList;

   public:
    IFM_ClassMetadata(char const *classname) :
		_className(classname)
	{}

	const char * getClassName()
    {
        return _className;
    }

    void addField(char const *fieldName,char const *fieldSign)
    {
        IFM_ClassFieldMetadata fieldMetadataObj = IFM_ClassFieldMetadata(fieldName,fieldSign);
        IFM_ClassFieldMetadata* fieldMetadata = &fieldMetadataObj;
        inlineableFieldList.push_back(fieldMetadata);
    }

    bool isFieldInlined(char const *fieldName,char const *fieldSign)
    {
        for (std::vector<IFM_ClassFieldMetadata *>::iterator i = inlineableFieldList.begin(); i != inlineableFieldList.end(); ++i)
        {
                IFM_ClassFieldMetadata * element = (IFM_ClassFieldMetadata *)*i;
                const char * elementFieldName =  element->getFieldName();
                if (!strcmp(elementFieldName, fieldName))
                {
                    return false;
                }
        }
        return true;
    }

};

#endif /* INLINEABLE_FIELD_METADATA_HPP */
