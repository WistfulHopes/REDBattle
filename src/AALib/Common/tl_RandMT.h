#pragma once
#include <cstdint>

class AA_CRandMT
{
private:
	static const int32_t MT_N; // 0xFFFFFFFFFFFFFFFF
	static const int32_t MT_M; // 0xFFFFFFFFFFFFFFFF
	static const uint32_t MT_MATRIX_A; // 0xFFFFFFFFFFFFFFFF
	static const uint32_t MT_UMASK; // 0xFFFFFFFFFFFFFFFF
	static const uint32_t MT_LMASK; // 0xFFFFFFFFFFFFFFFF
protected:
	uint32_t m_State[624]; // 0x0
	int32_t m_Left; // 0x9C0
	int32_t m_Initf; // 0x9C4
	uint32_t * m_pNext; // 0x9C8
	uint32_t MixBits(uint32_t, uint32_t);
	uint32_t Twist(uint32_t, uint32_t);
	void NextState();
	void InitParam();
public:
	AA_CRandMT(const uint32_t *, int32_t);
	AA_CRandMT(uint32_t);
	AA_CRandMT();
	~AA_CRandMT() {}
	bool Init(const uint32_t *, int32_t);
	bool Init(uint32_t start);
	uint32_t GenU32();
	int32_t GenS32() { return GenU32() >> 1; }
	double GenR1();
	double GenR2();
	double GenR3();
	double GenRS53();
	float GenF32();
	void Update();
    struct FRollbackData
    {
        uint32_t m_State[624]; // 0x0
        int32_t m_Left; // 0x9C0
        int32_t m_Initf; // 0x9C4
        uint32_t * m_pNext; // 0x9C8
    };
	void MakeRollbackData(FRollbackData &);
	void ApplyRollbackData(const FRollbackData &);
};

extern AA_CRandMT s_Rand;