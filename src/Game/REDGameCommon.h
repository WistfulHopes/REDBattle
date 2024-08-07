#pragma once
#include <cstdint>
#include <string>
#include "REDGameConstant.h"
#include <memory>

class SCENE_CBase;

enum BATTLE_DRAMA_ID : int32_t
{
	BATTLE_DRAMA_ID_INVALID = 0,
	BATTLE_DRAMA_ID_OPENING = 1,
	BATTLE_DRAMA_ID_ENDING = 2,
	BATTLE_DRAMA_ID_INTERLUDE = 3,
	BATTLE_DRAMA_ID_MAX = 4,
};

struct FMemberCharaInfo
{
	bool bEnable; // 0x0
	ECharaID CharaID; // 0x1
	EColorID ColorID; // 0x2
	EBattleScript ScriptType; // 0x3
	ECostumeID CostumeID; // 0x4
	bool bCPU; // 0x5
	int32_t CPULv; // 0x8
	FMemberCharaInfo() {}
	void Initialize();
	void Setup(bool, ECharaID, EColorID, EBattleScript, ECostumeID);
};

class REDBattlePlayerInfo 
{
public:
    REDBattlePlayerInfo() {}

    FMemberCharaInfo m_MemberCharaInfoList[3]; // 0x28
	bool DecideChara; // 0x4C
	uint32_t Handicap; // 0x50
	unsigned char PlayerState; // 0x54
	bool bUseCard; // 0x55
	bool bPadAssign; // 0x56
	bool bPlayTimeLimit; // 0x57
	PAD_ID PadID; // 0x58
	GAME_MODE PlayGameMode; // 0x5C
	int32_t SystemContinueTimer; // 0x60
	int32_t StageNo; // 0x64
	int32_t ContinueCount; // 0x68
	bool bStraightAll; // 0x6C
	bool bRandomChara; // 0x6D
	int32_t WinCount; // 0x70
	int32_t TmpWinCount; // 0x74
	int32_t TmpLoseCount; // 0x78
	wchar_t EntryName[4]; // 0x7C
	enum BATTLE_DRAMA_ID BattleDramaID; // 0x84
	bool bStylishMode; // 0x88
	bool bSelectMySet; // 0x89
	float PauseMenuLeftTime; // 0x8C
	void InitializeParam();
};

enum class EFadeType : uint8_t
{
    Normal = 0x0000,
    Animation = 0x0001,
};

class CSceneChangeCharaInfo
{
public:
	CSceneChangeCharaInfo() { CSceneChangeCharaInfoInit(); }
	void CSceneChangeCharaInfoInit();
	bool IsValid();
	bool IsCharaIDValid();
	void SetBattleCharaData(ECharaID charaID, EColorID colorID, EBattleScript scriptType, ECostumeID costumeID, HANDICAP_TYPE handicap);
	ECharaID GetCharaID() { return m_CharaID; }
	int32_t GetColorID()  { return m_ColorID; }
	EBattleScript GetScriptType()  { return m_ScriptType; }
	int32_t GetCostumeID()  { return m_CostumeID; }
	int32_t GetHandicap()  { return m_Handicap; }
	void SetCharaID(ECharaID);
	void SetColorID(int32_t);
private:
	ECharaID m_CharaID; // 0x0
	int32_t m_ColorID; // 0x4
	EBattleScript m_ScriptType; // 0x8
	int32_t m_CostumeID; // 0xC
	int32_t m_Handicap; // 0x10
};

class CSceneChange
{
public:
	static int32_t NewChallengerWaitCount; // 0xFFFFFFFFFFFFFFFF
	static int32_t MovieWaitCount; // 0xFFFFFFFFFFFFFFFF
	CSceneChange();
	void CSceneChangeInit();
	int32_t m_scFadeOutTime; // 0x0
	EFadeType m_scFadeType; // 0x4
	SCENE_ID m_scSceneID; // 0x8
	CSceneChangeCharaInfo m_scCharInfo[3][2]; // 0xC
	EBGMID m_scBGMID; // 0x84
	EBattleStage m_scBattleStage; // 0x88
	char m_scBattleInitPos; // 0x8C
	std::string m_scAdvStage; // 0x90
	GAME_MODE m_scGameMode; // 0xA0
	bool m_DispNewChallenger; // 0xA4
	bool m_scStoryEnd; // 0xA5
	bool m_SoftReset; // 0xA6
	bool m_RankMatchBattle; // 0xA7
	bool m_NetworkBattle; // 0xA8
	std::string m_LobbySubMenuID; // 0xB0
	void SetupFromCurrentInfo();
private:
	bool m_scSetFadeOutColor; // 0xB8
	uint32_t m_scFadeOutColor; // 0xBC
public:
	void ChangeFadeColor(uint32_t color)
	{
		m_scSetFadeOutColor = true;
		m_scFadeOutColor = color;
	}
	uint32_t GetFadeColor()
	{
		return m_scFadeOutColor;
	}
	bool IsChangeFadeColor()
	{
		return m_scSetFadeOutColor;
	}
	~CSceneChange() {}
	CSceneChange & operator=(const CSceneChange & __that);
};

namespace red
{
    namespace cmn 
    {
        extern bool g_SceneChangeFinish;
		extern CSceneChange g_SceneChangeReq;
		bool SceneChange(const CSceneChange& sc);
    };
};

class REDGameCommon 
{
private:
	REDGameCommon();

public:
	REDGameCommon(REDGameCommon const&) = delete;
	void operator=(REDGameCommon const&) = delete;

	int32_t playerID;
	SIDE_ID m_PlayerSide;

	static REDGameCommon* GetInstance();

private:
	GAME_MODE m_GameMode;
	GAME_MODE m_PrevGameMode;

	PAD_ID m_MainQuadrant;
	SIDE_ID m_MainPlayerSide;

	uint64_t m_FrameCounter;
	uint64_t m_FrameCounterEx;

	EBGMID m_BgmID;

	std::unique_ptr<SCENE_CBase> m_CurrentScene;
	SCENE_ID m_CurrentSceneID;
	SCENE_ID m_PrevSceneID;

private:
	REDBattlePlayerInfo BattlePlayerInfo[2];

public:
	void SetGameMode(GAME_MODE gameMode) 
	{
		m_PrevGameMode = m_GameMode;
		m_GameMode = gameMode;
	}

	void SetSceneID(SCENE_ID sceneID)
	{
		m_PrevSceneID = m_CurrentSceneID;
		m_CurrentSceneID = sceneID;
	}

	SCENE_CBase* GetScene() { return m_CurrentScene.get(); }
	GAME_MODE GetGameMode() { return m_GameMode; }

	void ChangeScene();
	void Tick(float DeltaSeconds);

	ECharaID GetBattleCharaID(SIDE_ID PlayerSide, EMemberID MemberID) 
	{
		return BattlePlayerInfo[PlayerSide].m_MemberCharaInfoList[MemberID].CharaID;
	}
};