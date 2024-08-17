#include "scene_Battle.h"

SCENE_CBattle::SCENE_CBattle()
{
    BattleObjectManager = std::make_unique<BATTLE_CObjectManager>();
    ScreenManager = std::make_unique<BATTLE_CScreenManager>();
    Settings = std::make_unique<BattleSettings>();
    State = std::make_unique<BattleState>();
    EventManager = std::make_unique<BattleEventManager>();
}

void SCENE_CBattle::SceneInitialize()
{
    SCENE_CBase::SceneInitialize();
    SetupBattle();
}

void SCENE_CBattle::Tick(float DeltaSeconds)
{
    SCENE_CBase::Tick(DeltaSeconds);
    UpdateBattle(DeltaSeconds, true);
}

void SCENE_CBattle::SetupBattle()
{
    BattleObjectManager->ScriptAnalyze();
    BattleObjectManager->BOM_MatchOneceInitialize(false);
    BattleObjectManager->BOM_RoundAndEasyResetInitialize(false);
    ScreenManager->ResetScreenManager();
    State->Setup();
    EventManager->Setup();
}

void SCENE_CBattle::UpdateBattle(float DeltaSeconds, bool bUpdateDraw)
{
    bool IsPause = false;
    
    if (!IsPause)
    {
        if (!BattleObjectManager->m_WorldStopper || BattleObjectManager->m_WorldStopTimer <= 0)
        {
            if (BattleObjectManager->m_FinishStopCount > 0) BattleObjectManager->m_FinishStopCount--;
        }
        BattleObjectManager->ExecuteObjectManagerEvent(EventManager.get());
        BattleObjectManager->ControlBattleObject();
    }
}
