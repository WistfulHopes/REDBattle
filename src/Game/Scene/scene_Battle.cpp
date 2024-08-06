#include "scene_Battle.h"

void SCENE_CBattle::SceneInitialize()
{
    SCENE_CBase::SceneInitialize();
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
    }
}