#include "BattleState.h"
#include <Game/Scene/scene_Battle.h>

void BattleState::Setup()
{
    m_RoundCount = 1;
    m_RoundMax = 2;
    m_FinalRound = false;
    m_PlayerResult[0].Reset();
    m_PlayerResult[1].Reset();

    m_PauseUpdate = false;
    m_RematchBattle = false;
    m_RematchRound = false;
    m_timerForcePauseSide = SIDE_ID_NUM;
    m_BattleQuickEnd = false;
    m_TimeLimitForceFinish = false;
    m_Winner = SIDE_ID_INVALID;
    m_IsBattleDoing = false;
    m_IsStartedBattle = false;

    // TODO finish

    const auto settings = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
        GetBattleSettings();
    
    if (settings->Time >= 0)
    {
        m_Timer.SetTimeMax(settings->Time * 60);
        m_Timer.Setup(settings->Time * 60);
    }
    else 
    {
        m_Timer.SetTimeInfinite();
    }
}
