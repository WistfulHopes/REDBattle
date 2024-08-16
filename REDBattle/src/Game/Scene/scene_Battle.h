#pragma once
#include "scene_Base.h"
#include "Game/Battle/BattleEventManager.h"
#include "Game/Battle/battle_ObjectManager.h"
#include "Game/Battle/battle_ScreenManager.h"
#include "Game/Battle/BattleSettings.h"
#include "Game/Battle/BattleState.h"

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
    std::unique_ptr<BATTLE_CObjectManager> BattleObjectManager{};
    std::unique_ptr<BATTLE_CScreenManager> ScreenManager{};
    std::unique_ptr<BattleSettings> Settings{};
    std::unique_ptr<BattleState> State{};
    std::unique_ptr<BattleEventManager> EventManager{};

private:
    void SetupBattle();
    void UpdateBattle(float DeltaSeconds, bool bUpdateDraw);
};

namespace red
{
    namespace btl
    {
        inline void GamePos2RaylibPos(const int32_t& x, const int32_t& y, const int32_t& z, Vector3& v)
        {
            auto scene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());
            if (scene)
            {
                auto linkMagn = scene->GetBattleScreenManager()->GetLinkMagn();
                v.x = (float)x * 0.001f * linkMagn;
                v.y = (float)y * 0.001f * linkMagn;
                v.z = (float)z * 0.001f * linkMagn;
            }
        }
    }
}
