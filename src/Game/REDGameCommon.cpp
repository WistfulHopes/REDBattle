#include "REDGameCommon.h"

#include <Scene/scene_Battle.h>
#include <Scene/scene_Boot.h>

#include "Scene/scene_Base.h"

bool red::cmn::g_SceneChangeFinish = true;
CSceneChange red::cmn::g_SceneChangeReq {};

CSceneChange::CSceneChange()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            m_scCharInfo[i][j].SetBattleCharaData(CHARA_ID_SOL, COLOR_ID_01, BATTLE_SCRIPT_DEFAULT, COSTUME_ID_01, HANDICAP_TYPE_LOWEST);
        }
    }
    m_scAdvStage = "";
    m_LobbySubMenuID = "";
    m_scFadeOutTime = 20;
    m_scFadeType = EFadeType::Animation;
    m_scSceneID = SCENE_ID_INVALID;
    m_scBGMID = BGMID_INVALID;
    m_scBattleStage = BATTLE_STAGE_MAX;
    m_scBattleInitPos = -1;
    m_scGameMode = GAME_MODE_INVALID;
    m_NetworkBattle = false;
}

CSceneChange& CSceneChange::operator=(const CSceneChange& __that)
{
    m_scFadeOutTime = __that.m_scFadeOutTime;
    m_scFadeType = __that.m_scFadeType;
    m_scSceneID = __that.m_scSceneID;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            auto charInfo = __that.m_scCharInfo[i][j];
            m_scCharInfo[i][j].SetBattleCharaData(charInfo.GetCharaID(), (EColorID)charInfo.GetColorID(), charInfo.GetScriptType(), (ECostumeID)charInfo.GetCostumeID(), (HANDICAP_TYPE)charInfo.GetHandicap());
        }
    }
    m_scBGMID = __that.m_scBGMID;
    m_scBattleStage = __that.m_scBattleStage;
    m_scBattleInitPos = __that.m_scBattleInitPos;
    m_scAdvStage = __that.m_scAdvStage;
    m_scGameMode = __that.m_scGameMode;
    m_DispNewChallenger = __that.m_DispNewChallenger;
    m_scStoryEnd = __that.m_scStoryEnd;
    m_SoftReset = __that.m_SoftReset;
    m_RankMatchBattle = __that.m_RankMatchBattle;
    m_NetworkBattle = __that.m_NetworkBattle;
    m_LobbySubMenuID = __that.m_LobbySubMenuID;
    m_scSetFadeOutColor = __that.m_scSetFadeOutColor;
    m_scFadeOutColor = __that.m_scFadeOutColor;
    return *this;
}

void CSceneChangeCharaInfo::CSceneChangeCharaInfoInit()
{
}

void CSceneChangeCharaInfo::SetBattleCharaData(ECharaID charaID, EColorID colorID, EBattleScript scriptType, ECostumeID costumeID, HANDICAP_TYPE handicap)
{
    m_CharaID = charaID;
    m_ColorID = colorID;
    m_ScriptType = scriptType;
    m_CostumeID = costumeID;
    m_Handicap = handicap;
}

bool red::cmn::SceneChange(const CSceneChange& sc)
{
    if (!g_SceneChangeFinish) return false;
    g_SceneChangeReq = sc;
    g_SceneChangeFinish = false;
    return true;
}

REDGameCommon* REDGameCommon::GetInstance()
{
    static REDGameCommon sInstance;
    return &sInstance;
}

REDGameCommon::REDGameCommon()
{
    m_CurrentScene = std::make_unique<SCENE_CBoot>();
    m_CurrentScene->SceneInitialize();
}

void REDGameCommon::ChangeScene()
{
    m_CurrentScene->SceneFinalize();

    switch (m_CurrentSceneID)
    {
    case SCENE_ID_BATTLE:
    case SCENE_ID_BATTLE_DIRECT:
    case SCENE_ID_STORY_BATTLE:
        m_CurrentScene = std::make_unique<SCENE_CBattle>();
    default:
        break;
    }
    m_CurrentScene->SceneInitialize();
}

void REDGameCommon::Tick(float DeltaSeconds)
{
    m_CurrentScene->Tick(DeltaSeconds);
}