#include "cmn_hashex.h"
#include <ctype.h>

uint32_t AA_MakeHash(const char* s)
{
    char nameCharIndex;
    bool charIsUpper;
    int nameChar;
    char* lowerNameInc;
    char lowerNameIndex;
    char lowerName[256] = {};
    int result;

    nameCharIndex = *s;
    for (char* i = lowerName; nameCharIndex != 13; *i++ = nameChar)
    {
        if (nameCharIndex == 10 || !nameCharIndex)
        {
            break;
        }
        charIsUpper = isupper(nameCharIndex);
        nameChar = *s;
        if (charIsUpper)
        {
            nameChar = tolower(nameChar);
        }
        nameCharIndex = *++s;
    }

    lowerNameInc = lowerName;
    lowerNameIndex = lowerName[0];
    for (result = 0; *lowerNameInc; lowerNameIndex = *lowerNameInc)
    {
        ++lowerNameInc;
        result = (unsigned int)(lowerNameIndex + 137 * result);
    }

    return result;
}