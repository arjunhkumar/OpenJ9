#if !defined(INLINEABLE_FIELD_METADATA_HPP)
#define INLINEABLE_FIELD_METADATA_HPP

#include <vector>

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

	const char * getFieldName();

    const char * getFieldSign();

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

    const char * getClassName();

    void addField(char const *fieldName,char const *fieldSign);

    bool isFieldInlined(char const *fieldName,char const *fieldSign);

    const char * createCopy(const char * targetString);

    void clearResults();

};

#endif /* INLINEABLE_FIELD_METADATA_HPP */
