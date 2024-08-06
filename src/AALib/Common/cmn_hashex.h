#pragma once
#include <cstdint>

uint32_t AA_MakeHash(const char* s);

class U32KEY
{
private:
    uint32_t m_Key; // 0x0
public:
    bool operator==(const U32KEY&);
    bool operator<(const U32KEY&);
    operator bool();
    uint32_t GetKey() { return m_Key; }
};

class CHashKey
{
public:
    U32KEY m_Key; // 0x0
    uint32_t GetHash() { return m_Key.GetKey(); }
};

class CHashNode
{
public:
    virtual CHashKey* GetKey() = 0;
    CHashNode() {}
};

class CHashKeyC32BYTE : public CHashKey {};

class CHashNodeC32BYTE : public CHashNode
{
private:
    CHashKeyC32BYTE m_HashKey; // 0x8
public:
    virtual CHashKey* GetKey() override
    {
        return &m_HashKey;
    }
    CHashNodeC32BYTE() {}
};

template <typename T>
class CHashTable
{
protected:
    T* m_Node;
    uint32_t m_NodeCnt;
    uint32_t m_NodeMax;

    uint32_t GetHash(CHashKey* hashKey)
    {
        return hashKey->GetHash();
    }

public:
    CHashTable(uint32_t HashTableNum)
    {
        m_Node = new T[HashTableNum];
        m_NodeMax = HashTableNum;
        m_NodeCnt = 0;
    }
    void ClearAllNode()
    {
        m_NodeCnt = 0;
    }

    static int32_t CompNode(const void* p1, const void* p2) {
        uint32_t key1 = ***(uint32_t***)p1;
        uint32_t key2 = ***(uint32_t***)p2;
        if (key1 >= key2) return key1 > key2;
        else return -1;
    }

    friend class CBBSFileAnalyzeData;
};

class CHashNodeC32BYTEtoU32 : public CHashNodeC32BYTE
{
private:
    uint32_t m_Data; // 0x10
public:
    CHashNodeC32BYTEtoU32()
    {
        m_Data = 0;
    }
    void SetData(uint32_t data)
    {
        m_Data = data;
    }
    uint32_t GetData()
    {
        return m_Data;
    }

    friend class CBBSFileAnalyzeData;
};

template<typename T, int V1, int V2>
class AA_EasyHash
{
public:
	AA_EasyHash();
private:
	unsigned short m_MaxLinkErrorCount; // 0x0
	unsigned short m_ElmCount; // 0x2
	unsigned short m_HashTable[V2]; // 0x4
	unsigned short m_LinkTable[V1]; // 0x1E4
	T m_ElmTable[V1]; // 0x25C
public:
	int32_t GetCount();
	void Release();
	void Sort();
	void AA_EasyHashInit();
	void Insert(const T&, uint32_t);
	bool Find(const T&, uint32_t, unsigned short *);
};
