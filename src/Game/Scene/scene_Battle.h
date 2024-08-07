#pragma once
#include "scene_Base.h"
#include "Battle/BattleEventManager.h"
#include "Battle/battle_ObjectManager.h"
#include "Battle/BattleState.h"

class SCENE_CBattle : public SCENE_CBase 
{
public:
    SCENE_CBattle();
    
    virtual void SceneInitialize() override;
	virtual void Tick(float DeltaSeconds) override;
    BATTLE_CObjectManager* GetBattleObjectManager() { return BattleObjectManager.get(); }
    BattleEventManager* GetBattleEventManager() { return EventManager.get(); }
    BattleState* GetBattleState() { return State.get(); }

protected:
    std::unique_ptr<BATTLE_CObjectManager> BattleObjectManager;
    std::unique_ptr<BattleEventManager> EventManager;
    std::unique_ptr<BattleState> State;

private:
    void SetupBattle();
    void UpdateBattle(float DeltaSeconds, bool bUpdateDraw);
};