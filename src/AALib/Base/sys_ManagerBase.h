#pragma once
#include "AALib/Common/cmn_class.h"
#include <cstring>

template <typename T, int Count>
class AA_ManagerBase
{
protected:
	T* m_Instances[Count] {}; // 0x8
	uint32_t m_InstanceNum {}; // 0x88
protected:
	void Cleanup();
public:
	AA_ManagerBase();
	virtual ~AA_ManagerBase()
	{
		for (uint32_t i = 0; i < m_InstanceNum; i++)		
		{
			delete m_Instances[i];
		}
	}
	void CleanupInstance();
	AA_Handle RegistInstanceHandle(T* inst);
	T* RegistInstance(T* inst);
	T* Get(const AA_Handle &);
	T* Get(uint32_t idx) { return m_Instances[idx]; }
	virtual void Update() = 0;
	AA_ManagerBase & operator=(const AA_ManagerBase &);
};

template<typename T, int Count>
inline AA_ManagerBase<T, Count>::AA_ManagerBase()
{
	m_InstanceNum = 0;
	std::memset(m_Instances, 0, sizeof(m_Instances));
}

template<typename T, int Count>
inline void AA_ManagerBase<T, Count>::CleanupInstance()
{
	for (int i = 0; i < m_InstanceNum; i++)
	{
		delete m_Instances[i];
	}
}

template<typename T, int Count>
inline T* AA_ManagerBase<T, Count>::RegistInstance(T* inst)
{
	if (m_InstanceNum < Count)
	{
		return m_Instances[m_InstanceNum++] = inst;
	}
	return nullptr;
}
