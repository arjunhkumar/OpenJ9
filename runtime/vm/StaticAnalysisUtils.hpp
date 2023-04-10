#if !defined(STATIC_ANALYSIS_UTILS_HPP_)
#define STATIC_ANALYSIS_UTILS_HPP_

#include <stdlib.h>
#include <string.h>
#include "j9.h"
#include "InlineableFieldMetadata.hpp"

/* AR07 - This file takes care of all the functions required to read static analysis 
    for flattening as well as retrieving the field level preference during JIT. */


class StaticAnalysisUtils 
{
    public:

    static int value_debug;

    static std::vector<IFM_ClassMetadata *> staticResults;

    static bool fieldInliningPreference(J9Class *fieldClass, J9ROMFieldShape* field);

    static bool fieldInliningPreferenceWithRom(J9ROMClass* fieldClass, J9ROMFieldShape* field);

    static IFM_ClassMetadata * getClassMetadata(const char * className);

    static std::vector<IFM_ClassMetadata *> getStaticRes();

    static void clearResults();

};    
#endif /* STATIC_ANALYSIS_UTILS_HPP */