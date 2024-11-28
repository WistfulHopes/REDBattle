#include "tl_Jon.h"
#include <cstdlib>
#include <cwchar>

AA_CCollision_JON::AA_CCollision_JON()
{
    m_ImageFileNum = 0;
    for (int i = 0; i < 8; i++)
    {
        m_ImageFileName[i] = nullptr;
    }
    m_ViewAddr = nullptr;
    for (int i = 0; i < 18; i++)
    {
        m_CollisionAddr[i] = nullptr;
    }
}

bool AA_CCollision_JON::AnalyzeCollisionFile(const void* col)
{
    if (col)
    {
        SetCollisionFileAddr(col);
        m_ImageFileNum = *((uint16_t*)col + 2);
        auto offset = (char*)col + 6;
        
        for (int i = 0; i < m_ImageFileNum; i++)
        {
            m_ImageFileName[i] = offset;
            offset += 32;
        }
        
        uint8_t typeCount = *(uint8_t*)offset - 3;
        auto viewRelated = *(uint16_t*)(offset + 1);
        m_ViewNum = *(uint16_t*)(offset + 3);
        auto unk = *(uint16_t*)(offset + 5);
        uint16_t* offset2 = (uint16_t*)(offset + 7);
        int colCount = 0;

        if (typeCount)
        {
            for (int i = 0; i < typeCount; i++)
            {
                m_CollisionNum[i] = *offset2++;
                colCount += m_CollisionNum[i];
            }
        }

        if (typeCount < 18)
        {
            for (int i = typeCount; i < 18; i++)
            {
                m_CollisionNum[i] = 0;
            }
        }

        m_ViewAddr = (sJonElmView*)&offset2[26 * viewRelated];
        auto collision = (sJonElmCollision*)((uint64_t)m_ViewAddr + 308 * unk + 80 * m_ViewNum);
        if (colCount)
        {
            for (int i = 0; i < colCount; i++)
            {
                m_CollisionAddr[i] = collision;
                collision++;
            }
        }

        return true;
    }
    return false;
}

const wchar_t* AA_CCollision_JON::GetAnimeName()
{
    if (m_ImageFileNum <= 0) return nullptr;
    auto fileName = m_ImageFileName[0];
    if (!fileName) return nullptr;

    wchar_t* name = new wchar_t[0x20];
    std::mbstowcs(name, fileName, 0x20);

    wchar_t* end = nullptr;

    for (wchar_t* i = std::wcsstr(name, L"_"); i; i = i = std::wcsstr(i + 1, L"_"))
    {
        end = i;
    }
    *end = 0;
    return name;
}

int32_t AA_CCollision_JON::GetAnimeFrame()
{
    if (m_ImageFileNum <= 0) return 0;
    auto fileName = m_ImageFileName[0];
    if (!fileName) return 0;

    wchar_t* name = new wchar_t[0x20];
    std::mbstowcs(name, fileName, 0x20);

    wchar_t* numOffset = nullptr;

    for (wchar_t* i = std::wcsstr(name, L"_"); i; i = i = std::wcsstr(i + 1, L"_"))
    {
        numOffset = i;
    }
    wchar_t* final = numOffset + 1;

    if (std::wcsstr(final, L"."))
    {
        wchar_t* end = nullptr;
        do 
        {
            wchar_t* end = final;
            final = std::wcsstr(final + 1, L".");
        }
        while (final);
        *end = 0;
    }

    return std::wcstol(final, nullptr, 10);
}
