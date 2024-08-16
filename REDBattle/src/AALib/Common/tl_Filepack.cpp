#include "tl_Filepack.h"
#include "AALib/Common/PackHeader/PAC_FPac.h"
#include <ctype.h>

uint32_t AA_Filepack_FPAC::SearchFileIDFromHash(uint32_t namehash)
{
    uint32_t result;

    auto unk = 0;
    auto header = (FILEPACK_HEADER*)m_pData;
    char* offset = (char*)m_pData + 32;
    auto stylePack = header->stylePack;

    auto count = header->numFile - 1;

    if ((stylePack & FPACST_ID_ONLY) != 0)
    {
        if ((int)count < 0)
        {
            return -1;
        }
        while (true)
        {
            result = count + unk >> 1;
            auto hash = *(int32_t*)&offset[16 * (int)result + 12];
            if (hash == namehash) return result;
            auto unk2 = result + 1;
            if (hash >= namehash)
            {
                count = result - 1;
                unk2 = unk;
            }
            unk = unk2;
            if (unk2 > count) return -1;
        }
    }

    else if ((stylePack & FPACST_LONGNAME) != 0)
    {
        if ((int)count < 0)
        {
            return -1;
        }
        while (true)
        {
            result = count + unk >> 1;
            auto hash = *(int32_t*)&offset[80 * (int)result + 76];
            if (hash == namehash) return result;
            auto unk2 = result + 1;
            if (hash >= namehash)
            {
                count = result - 1;
                unk2 = unk;
            }
            unk = unk2;
            if (unk2 > count) return -1;
        }
    }

    else
    {
        if ((int)count < 0)
        {
            return -1;
        }
        while (true)
        {
            result = count + unk >> 1;
            auto hash = *(int32_t*)&offset[48 * (int)result + 44];
            if (hash == namehash) return result;
            auto unk2 = result + 1;
            if (hash >= namehash)
            {
                count = result - 1;
                unk2 = unk;
            }
            unk = unk2;
            if (unk2 > count) return -1;
        }
    }

    return -1;
}

AA_Filepack_FPAC::AA_Filepack_FPAC()
{
    m_pData = nullptr;
}

void* AA_Filepack_FPAC::GetPackOffsetAddr(uint32_t num)
{
    auto header = (FILEPACK_HEADER*)m_pData;
    if (header->numFile < num) return nullptr;
    auto stylePack = header->stylePack;
    if ((int)stylePack >= 0)
        return (char*)m_pData + (uint32_t)((char*)m_pData + num * ((header->maxlenName + 12 & 0xFFFFFFF0) + 16) + header
            ->maxlenName + 36) + header->sizeHeader;
    if ((stylePack & FPACST_ID_ONLY) != 0)
        return (char*)m_pData + ((uint32_t*)m_pData)[4 * num + 9] + header->sizeHeader;

    uint64_t offset;

    if ((stylePack & FPACST_LONGNAME) != 0)
        offset = ((uint32_t*)m_pData)[20 * num + 25];
    else
        offset = ((uint32_t*)m_pData)[12 * num + 17];

    return (char*)m_pData + offset + header->sizeHeader;
}

uint32_t AA_Filepack_FPAC::GetPackOffsetFileSize(uint32_t num)
{
    auto header = (FILEPACK_HEADER*)m_pData;
    if (header->numFile < num) return 0;
    auto stylePack = header->stylePack;
    if ((int)stylePack >= 0)
        return (uint32_t)m_pData + (uint32_t)((char*)m_pData + num * ((header->maxlenName + 12 & 0xFFFFFFF0) + 16) +
            header->maxlenName + 37) + header->sizeHeader;
    if ((stylePack & FPACST_ID_ONLY) != 0)
        return (uint32_t)m_pData + ((uint32_t*)m_pData)[4 * num + 10] + header->sizeHeader;

    uint32_t offset;

    if ((stylePack & FPACST_LONGNAME) != 0)
        offset = ((uint32_t*)m_pData)[20 * num + 26];
    else
        offset = ((uint32_t*)m_pData)[12 * num + 18];

    return (uint32_t)m_pData + offset + header->sizeHeader;
}

const char* AA_Filepack_FPAC::GetPackFileNum2FileName(uint32_t num)
{
    auto header = (FILEPACK_HEADER*)m_pData;
    if (header->numFile < num) return nullptr;

    auto stylePack = header->stylePack;
    if ((stylePack & FPACST_ID_ONLY) != 0) return nullptr;

    if ((int32_t)stylePack >= 0)
        return (char*)m_pData + num * ((header->maxlenName + 12 & 0xFFFFFFF0) + 16) + 32;

    char* offset = (char*)m_pData + 32;
    int index;
    if ((stylePack & FPACST_LONGNAME) != 0) index = 80 * num;
    else index = 48 * num;

    return &offset[index];
}

uint32_t AA_Filepack_FPAC::SearchFileID(const char* pFileName)
{
    auto header = (FILEPACK_HEADER*)m_pData;
    auto stylePack = header->stylePack;
    if ((int)stylePack < 0)
    {
        return SearchFileIDFromHash(MakeHash(pFileName));
    }

    if (header->numFile)
    {
        auto index = 0;
        const char* unk = nullptr;
        while (true)
        {
            if ((stylePack & FPACST_ID_ONLY) != 0) unk = 0;
            else
            {
                auto offset = 0;
                if ((int)stylePack < 0)
                {
                    auto tempOffset = 5 * index;
                    if ((stylePack & FPACST_LONGNAME) == 0) tempOffset = 3 * index;
                    offset = 16 * tempOffset;
                }
                else offset = index * (header->maxlenName + 12 & 0xFFFFFFF0) + 16;

                unk = (char*)m_pData + offset + 32;
            }
            auto start = pFileName - unk;
            auto offset = 0;
            auto final = 0;
            do
            {
                offset = start[unk];
                final = *(uint8_t*)(unk - offset);
                if (final) break;
                ++unk;
            }
            while (offset);
            if (!final) break;
            index++;
            if (header->numFile <= index) return -1;
        }
        return index;
    }

    return -1;
}

uint32_t AA_Filepack_FPAC::MakeHash(const char* s)
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
