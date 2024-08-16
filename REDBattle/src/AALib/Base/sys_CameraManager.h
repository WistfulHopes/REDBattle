#pragma once
#include "sys_ManagerBase.h"
#include "sys_Camera.h"

class AA_CCameraManager : public AA_ManagerBase<AA_CCamera,16>
{
public:
	AA_CCameraManager() {}
	virtual ~AA_CCameraManager() {}
	virtual void Update() override 
	{
		for (uint32_t i = 0; i < m_InstanceNum; i++)
		{
			m_Instances[i]->Update();
		}
	}
	AA_CCameraManager & operator=(AA_CCameraManager &);
	AA_CCameraManager & operator=(const AA_CCameraManager &);
};