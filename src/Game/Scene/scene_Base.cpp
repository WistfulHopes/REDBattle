#include "scene_Base.h"

namespace
{
    bool s_bReqSceneChangeFinish = false;
}

void SCENE_CBase::SceneInitialize()
{
    CurrentBGLayerIndex = 0;
    BGTimeSpeed = 1;
}

void SCENE_CBase::SceneFinalize()
{
    
}

void SCENE_CBase::Tick(float DeltaSeconds)
{
    GameTime += DeltaSeconds;
    if (red::cmn::g_SceneChangeFinish)
        bSceneChanging = false;
    else
        GoToNextScene(red::cmn::g_SceneChangeReq.m_scSceneID);
}

bool SCENE_CBase::UpdateChangeScene()
{
    if (red::cmn::g_SceneChangeFinish || bChangingController || bSignOutDialogDoing) return false;
    
    auto gameCommon = REDGameCommon::GetInstance();
    if (!bSceneChanging)
    {
        OnSceneChangeStart(&red::cmn::g_SceneChangeReq);
        bSceneChanging = true;

        if (red::cmn::g_SceneChangeReq.m_DispNewChallenger)
        {

        }
        else 
        {
            // fade out
        }
        SetSuspend(true);
    }
    GoToNextScene(red::cmn::g_SceneChangeReq.m_scSceneID);

    if (red::cmn::g_SceneChangeReq.m_scGameMode != GAME_MODE_INVALID)
    {
        gameCommon->SetGameMode(red::cmn::g_SceneChangeReq.m_scGameMode);
    }

    s_bReqSceneChangeFinish = true;
    bSceneChanging = false;
    return true;
}

void SCENE_CBase::GoToNextScene(SCENE_ID _sc_id)
{
    auto gameCommon = REDGameCommon::GetInstance();
    switch (_sc_id)
    {
        case SCENE_ID_BATTLE:
        case SCENE_ID_BATTLE_DIRECT:
        case SCENE_ID_STORY_BATTLE:
        {
            // set level
        }
        default:
            break;
    }
    gameCommon->SetSceneID(_sc_id);
}
