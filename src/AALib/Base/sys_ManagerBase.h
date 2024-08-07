#pragma once
#include "Common/cmn_class.h"
#include <cstring>

template <typename T, int Count>
class AA_ManagerBase
{
private:
	T* m_Instances[Count]; // 0x8
	uint32_t m_InstanceNum; // 0x88
protected:
	void Cleanup();
public:
	AA_ManagerBase();
	~AA_ManagerBase();
	void CleanupInstance();
	AA_Handle RegistInstanceHandle(T*);
	T* RegistInstance(T*);
	T* Get(const AA_Handle &);
	T* Get(uint32_t idx) { return m_Instances[idx]; }
	void Update();
	AA_ManagerBase & operator=(const AA_ManagerBase &);
};

template<typename T, int Count>
inline AA_ManagerBase<T, Count>::AA_ManagerBase()
{
	m_InstanceNum = 0;
	std::memset(m_Instances, 0, sizeof(m_Instances));
}
