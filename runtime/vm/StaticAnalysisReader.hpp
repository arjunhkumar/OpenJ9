#if !defined(STATIC_ANALYSIS_READER_HPP)
#define STATIC_ANALYSIS_READER_HPP

#include <stdlib.h>
#include <string.h>
#include "j9.h"

/* AR07 - This file takes care of all the functions required to read static analysis 
    for flattening as well as retrieving the field level preference during JIT. */

#ifdef __cplusplus
extern "C" {
    void readStaticResults(char *filename);
    const char * createCopy(char * targetString);
    int fieldInliningPreference(J9Class *fieldClass, J9ROMFieldShape* field);
    int fieldInliningPreferenceWithRom(J9ROMClass* fieldClass, J9ROMFieldShape* field);
    // auto getClassMetadata(char * className);
}
#endif

#endif /* STATIC_ANALYSIS_READER_HPP */


