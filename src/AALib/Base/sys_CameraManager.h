#pragma once
#include "sys_ManagerBase.h"
#include "sys_Camera.h"

class AA_CCameraManager : public AA_ManagerBase<AA_CCamera,16>
{
public:
	AA_CCameraManager() {}
	virtual ~AA_CCameraManager() {}
	AA_CCameraManager & operator=(AA_CCameraManager &);
	AA_CCameraManager & operator=(const AA_CCameraManager &);
};