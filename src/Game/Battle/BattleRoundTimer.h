#pragma once
#include <cstdint>

class RoundTimer
{
private:
	static const int32_t FPS = 60;
	int32_t m_FrameTimeMax {}; // 0x0
	int32_t m_CurrentFrameTime {}; // 0x4
	uint32_t m_TimeStep {}; // 0x8
	bool m_Started {}; // 0xC
	bool m_Pause {}; // 0xD
	bool m_Infinity {}; // 0xE
	bool m_forcePause {}; // 0xF
	void InitParam();
public:
	RoundTimer() {}
	void ResetTime();
	void Start();
	void Setup(int32_t time) { m_CurrentFrameTime = time; }
	void SetupF(float);
	void SetTimeMax(int32_t timeMax) { m_FrameTimeMax = timeMax; }
	void SetTimeMaxF(float);
	void OverwriteTime(int32_t);
	void AddOverwriteTime(int32_t);
	void SetTimeInfinite() { m_Infinity = true; }
	void ResetTimeInfinite() { m_Infinity = false; }
	void SetPause(bool pause) { m_Pause = false; }
	bool IsPause();
	bool IsTimeup();
	bool IsInfinite();
	int32_t GetTimeForDisp();
	int32_t GetMaxTimeForDisp();
	void SetForcePause(bool);
	bool IsForcePause();
	void Update();
	void SetTimeStep(float);
	bool IsZoromeTime();
	bool IsTimerStarted();
};