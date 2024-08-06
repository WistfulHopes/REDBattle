#pragma once
#include <cstdint>
#include "Base/sys_Math.h"

enum EACCType
{
	ACC_LINEAR = 0,
	ACC_DEC = 1,
	ACC_ACC = 2,
	ACC_ACC_TO_DEC = 3,
	ACC_EXP_DEC = 4,
	ACC_EXP_ACC = 5,
	ACC_EXP_ACC_TO_DEC = 6,
};

class LoopedFloatParam
{
public:
	float Value; // 0x0
	float Speed; // 0x4
private:
	float BeginValue; // 0x8
	float EndValue; // 0xC
	int32_t LoopCount; // 0x10
	int32_t FrameCounter; // 0x14
	int32_t FrameCountMax; // 0x18
	float MINVALUE; // 0x1C
	float MAXVALUE; // 0x20
public:
	LoopedFloatParam(float, float);
	LoopedFloatParam();
	void Stop();
	void Reset();
	void Update();
	void SetParamWithLoop(float, int32_t, int32_t);
};

class CColorWithSpeed
{
public:
	CColorWithSpeed();
	void InitCColorWithSpeed();
	void SetColorWithLoop(AA_LinearColor, int32_t, int32_t);
	void UpdateCColorWithSpeed();
	uint32_t GetU32Color();
	void SetU32Color(uint32_t);
	AA_LinearColor GetColor();
	void SetColor(AA_LinearColor);
	void Stop();
	LoopedFloatParam R; // 0x0
	LoopedFloatParam G; // 0x24
	LoopedFloatParam B; // 0x48
	LoopedFloatParam A; // 0x6C
	bool IgnoreStop; // 0x90
};

class CFloatWithTimer
{
public:
	CFloatWithTimer();
	void Init();
	void Update();
	float GetVal();
	void SetVal(float, float, uint32_t);
	void SetPause(bool);
	bool IsSet();
	float m_Val; // 0x0
	float m_BeginVal; // 0x4
	float m_DestVal; // 0x8
	int32_t m_DestTimer; // 0xC
	int32_t m_DestTimerMax; // 0x10
	bool m_bSet; // 0x14
	bool m_bPause; // 0x15
};

class CVectorWithTimer
{
public:
	CVectorWithTimer();
	void Init();
	void Update();
	float GetVal(uint32_t);
	void SetVal(uint32_t, float, uint32_t);
	bool IsSet();
	float m_Val[4]; // 0x0
	float m_BeginVal[4]; // 0x10
	float m_DestVal[4]; // 0x20
	int32_t m_DestTimer[4]; // 0x30
	int32_t m_DestTimerMax[4]; // 0x40
	bool m_bSet; // 0x50
};