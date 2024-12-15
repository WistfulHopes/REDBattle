#pragma once
#include <cstdint>

class AA_Handle
{
	enum 
    {
		INVALID_HANDLE = 255,
	};
private:
	uint32_t value {}; // 0x0
public:
	AA_Handle(uint32_t);
	AA_Handle() 
	{
		value = 0;
	}
	void Set(uint32_t);
	uint32_t Get();
	bool IsValid();
	void SetInvalid();
	AA_Handle & operator=(const uint32_t &);
	AA_Handle & operator=(const AA_Handle &);
};

template<typename T>
class AA_Flag
{
private:
	T m_Flag {}; // 0x0
public:
	static const uint32_t BIT_NUM {}; // 0xFFFFFFFFFFFFFFFF
	AA_Flag(T flag) { m_Flag = flag; }
	AA_Flag() {}
	bool Check(T);
	bool CheckN(T);
	bool CheckAll(T);
	bool CheckAny();
	void Set(T flag) { m_Flag &= flag; }
	void SetN(T);
	T Get()
	{
		return m_Flag;
	}
	void Add(T flag) { m_Flag |= flag; }
	void AddN(T);
	void Del(T flag) { m_Flag &= ~flag; }
	void DelN(T);
	void Reset()
	{
		m_Flag = 0;
	}
	operator T();
	T & operator|=(const T &);
	const T operator&(const T &);
	const T operator|(const T &);
	bool operator==(const AA_Flag &);
};