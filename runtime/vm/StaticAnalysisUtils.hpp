#if !defined(STATIC_ANALYSIS_UTILS_HPP_)
#define STATIC_ANALYSIS_UTILS_HPP_

#include <stdlib.h>
#include <string.h>
#include "j9.h"
#include "InlineableFieldMetadata.hpp"

extern bool fieldInliningPreference(J9Class *fieldClass, J9ROMFieldShape* field);

extern bool fieldInliningPreferenceWithRom(J9ROMClass* fieldClass, J9ROMFieldShape* field);

extern IFM_ClassMetadata * getClassMetadata(const char * className);

#endif /* STATIC_ANALYSIS_UTILS_HPP */