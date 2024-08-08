#pragma once
#include "scene_Base.h"
#include "Battle/BattleEventManager.h"
#include "Battle/battle_ObjectManager.h"
#include "Battle/battle_ScreenManager.h"
#include "Battle/BattleSettings.h"
#include "Battle/BattleState.h"

class SCENE_CBattle : public SCENE_CBase 
{
public:
    SCENE_CBattle();
    
    virtual void SceneInitialize() override;
	virtual void Tick(float DeltaSeconds) override;
    BATTLE_CObjectManager* GetBattleObjectManager() { return BattleObjectManager.get(); }
    BATTLE_CScreenManager* GetBattleScreenManager() { return ScreenManager.get(); }
    BattleSettings* GetBattleSettings() { return Settings.get(); }
    BattleState* GetBattleState() { return State.get(); }
    BattleEventManager* GetBattleEventManager() { return EventManager.get(); }

protected:
    std::unique_ptr<BATTLE_CObjectManager> BattleObjectManager;
    std::unique_ptr<BATTLE_CScreenManager> ScreenManager;
    std::unique_ptr<BattleSettings> Settings;
    std::unique_ptr<BattleState> State;
    std::unique_ptr<BattleEventManager> EventManager;

private:
    void SetupBattle();
    void UpdateBattle(float DeltaSeconds, bool bUpdateDraw);
};