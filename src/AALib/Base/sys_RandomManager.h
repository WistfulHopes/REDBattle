#pragma once
#include <cstdint>
#include "Common/tl_RandMT.h"
#include "sys_ManagerBase.h"

class AA_CRandomManager : public AA_ManagerBase<AA_CRandMT,16>
{
public:
	bool Init(uint32_t val, int32_t idx);
	uint32_t RandU32(int32_t);
	int32_t RandS31(int32_t);
	float RandF32(int32_t);
	float RandF32S(int32_t);
	virtual void Update() override {}
	void MakeRollbackData(int32_t, AA_CRandMT::FRollbackData &);
	void ApplyRollbackData(int32_t, const AA_CRandMT::FRollbackData &);
	AA_CRandomManager() {}
	AA_CRandomManager & operator=(AA_CRandomManager &);
	AA_CRandomManager & operator=(const AA_CRandomManager &);
};