#pragma once
#include <cstdint>
#include <string>
#include "REDGameConstant.h"
#include <memory>

class SCENE_CBase;

enum EFadeType : uint8_t
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
	void ChangeFadeColor(uint32_t);
	uint32_t GetFadeColor();
	bool IsChangeFadeColor();
	~CSceneChange() {}
	CSceneChange & operator=(const CSceneChange & __that);
};

namespace red
{
    namespace cmn 
    {
        static inline bool g_SceneChangeFinish;
		static inline CSceneChange g_SceneChangeReq;
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

	static REDGameCommon* GetInstance() 
	{
		static REDGameCommon* sInstance;
		return sInstance;
	}

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

	void ChangeScene();
};