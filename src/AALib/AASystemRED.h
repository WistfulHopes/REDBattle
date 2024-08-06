#pragma once
#include "Base/sys_RandomManager.h"

enum ERondomType
{
	RND_NOSYNC = 0,
	RND_SYNC = 1,
	RND_MAX = 2,
};
class AASystemRED
{
private:
	bool m_bInitialized; // 0x8
	AASystemRED();
	~AASystemRED();
protected:
	//AA_CCameraManager m_CameraManager; // 0x10
	//AA_CInputManager m_InputManager; // 0xA0
	AA_CRandomManager m_RandomManager; // 0x130
	//AA_CTaskManager m_TaskManager; // 0x1C0
	//GAME_SystemKeyController * m_SystemKey; // 0x1F0
	//GAME_BattleKeyController * m_BattleKey[4]; // 0x1F8
	//GAME_KeyboardKeyController * m_KeyboardKey; // 0x218
	//GAME_BattleKeyController * m_BattleKey_Any; // 0x220
	void Initialize();
	void InitializeInput();
public:
	AASystemRED(const AASystemRED &) = delete;
	void Update();
	//AA_CCameraManager & GetCameraManager();
	//AA_CInputManager & GetInputManager();
	AA_CRandomManager & GetRandomManager();
	AA_CRandMT * GetRandom(ERondomType);
	//GAME_SystemKeyController * GetSystemKey();
	//GAME_BattleKeyController * GetBattleKey(SIDE_ID);
	//GAME_BattleKeyController * GetBattleKeyFromPadID(PAD_ID);
	//GAME_KeyboardKeyController * GetKeyboardKey();
private:
	static AASystemRED * s_Instance; // 0xFFFFFFFFFFFFFFFF
public:
	static AASystemRED * GetInstance() { return s_Instance; }
	static void StaticInitialize();
	static void StaticFinalize();
	AASystemRED & operator=(const AASystemRED &) = delete;
};