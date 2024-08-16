#pragma once
#include <cstdint>
#include <cstring>

template <int Length>
class CXXBYTE
{
private:
    char m_Buf[Length] {};

public:
	CXXBYTE()
	{
		strncpy(m_Buf, "", Length);
		m_Buf[Length - 1] = 0;
	}
    CXXBYTE(const char* str);
    CXXBYTE& operator=(const char* str);
    CXXBYTE& operator+=(const char* str);
    const char* GetStr() const { return m_Buf; }
    char* GetStrV() const { return m_Buf; }
};

template <int Length>
CXXBYTE<Length>::CXXBYTE(const char* str)
{
    strncpy(m_Buf, str, Length);
    m_Buf[Length - 1] = 0;
}

template <int Length>
CXXBYTE<Length>& CXXBYTE<Length>::operator=(const char* str)
{
    if (!str) return *this;

    int bufEnd = 0;
    int bufIdx = 0;

    while (*str)
    {
        m_Buf[bufIdx] = *str;
        char nextChar = str[1];
        if (!nextChar)
        {
            ++bufEnd;
            break;
        }
        m_Buf[bufIdx + 1] = nextChar;
        nextChar = str[2];
        if (!nextChar)
        {
            bufEnd += 2;
            break;
        }
        m_Buf[bufIdx + 2] = nextChar;
        nextChar = str[3];
        if (!nextChar)
        {
            bufEnd += 2;
            break;
        }
        m_Buf[bufIdx + 3] = nextChar;
        str += 4;
        bufIdx += 4;
        bufEnd += 4;
        if (bufIdx >= Length) break;
    }
    if (bufEnd < Length) memset(&m_Buf[bufEnd], 0, Length - bufEnd);
    m_Buf[Length - 1] = 0;

    return *this;
}

template <int Length>
CXXBYTE<Length>& CXXBYTE<Length>::operator+=(const char* str)
{
    int bufLen = 0;
    if (m_Buf[0])
    {
        bufLen = strlen(m_Buf);
    }
    if (bufLen < Length)
    {
        char* bufEnd = m_Buf[bufLen];

        do
        {
            if (!*str) break;
            *bufEnd = *str;

            ++bufLen;
            ++bufEnd;
            ++str;
        } while (bufEnd - static_cast<char*>(this) < Length);
    }

    if (bufLen < Length)
    {
        memset(&m_Buf[bufLen], 0, Length - bufLen);
    }
    m_Buf[Length - 1] = 0;

    return this;
}

template <typename T1, typename T2, int V1, int V2>
class AA_EasyMap
{
public:
    AA_EasyMap() {}
private:
    T1 m_pKeyList[V1] {};
    T2 m_pItemList[V1] {};
    int32_t m_PSortList[V1] {};
    int32_t m_Cursor[V2] {};
    bool m_IsOverWriteInsert {};
};

class CCmnRect
{
public:
	float m_X {}; // 0x0
	float m_Y {}; // 0x4
	float m_W {}; // 0x8
	float m_H {}; // 0xC
	CCmnRect(float, float, float, float);
	CCmnRect();
	void SetRect(float, float, float, float);
	void Reset();
	void Normalize();
	bool IsPointIn(float, float);
	void RoundInteger();
	void Add(CCmnRect &);
	void PosAdd_SizeSet(CCmnRect &);
	void PackIntoRect(CCmnRect &);
	bool IsTooLittle();
};

template <int Num, typename T>
class BitArrayRED_NoInit
{
    enum {
        NUM_OF_U32_DATA_ARRAY = Num / 4,
    };
    uint32_t m_U32DataArray[NUM_OF_U32_DATA_ARRAY] {}; // 0x0
	uint32_t GetBufferPos(T);
	uint32_t GetOffset(T);
	static uint32_t NumOfBits(uint32_t);
	static int32_t GetLSB(uint32_t);
	static void Fill(unsigned long long &);
	static void Fill(uint32_t &);
public:
	int32_t GetBitNumMax();
	void Set(T, bool);
	void Set(T);
	void Clr(T);
	bool Check(T);
	uint32_t CheckF(T);
	void Add(T);
	void Del(T);
	bool Is(T);
	bool Has(T);
	uint32_t IsF(T);
	int32_t GetBufferSize();
	int32_t GetBufferNum();
	void ClrAll();
	void SetAll();
	int32_t CountTrueBit();
	void Reverse(T);
	void EndianSwap();
	void operator|=(T);
	void operator+=(T);
	void operator-=(T);
	bool operator[](T);
	int32_t GetFirstBitZero();
	int32_t GetLsb();
};

template <int Num, typename T>
class BitArrayRED 
{
public:
    BitArrayRED();
};

enum MAAI_TYPE
{
	MAAI_TYPE_NORMAL_GAME = 0,
	MAAI_TYPE_RIGHT_LITTLE = 1,
	MAAI_TYPE_RIGHT_MAX = 2,
	MAAI_TYPE_LEFT_LITTLE = 3,
	MAAI_TYPE_LEFT_MAX = 4,
	MAAI_TYPE_NEAR_CENTER = 5,
	MAAI_TYPE_FAR = 6,
	MAAI_TYPE_NEAR_EX = 7,
};
