#pragma once
#include <cstdint>

#include "Game/REDGameConstant.h"

class CSceneChange;

class SCENE_CBase
{
public:
    SCENE_CBase() = default;
    virtual ~SCENE_CBase() = default;

public:
    float GameTime {};
    float BGTime {};
    float BGTimeSpeed {};
    bool bSceneChanging {};
    uint32_t GameStateCounter {};
    uint32_t CurrentBGLayerIndex {};
    int32_t ChangingControllerCountdown {};
    bool bEnableSigninAndControllerCheck {};
    bool bChangingController {};

private:
    bool bFirstTickCall {};
    bool bSuspend {};

public:
    virtual void SceneInitialize();
    virtual void SceneFinalize();
    virtual void Tick(float DeltaSeconds);
    virtual void UpdateOnPreTick(float DeltaSeconds);
    virtual void UpdateOnEndTick(float DeltaSeconds);

private:
    bool UpdateChangeScene();
    void GoToNextScene(SCENE_ID _sc_id);
    void ResetOnSceneChanged(const CSceneChange *);
    void OnFadeInDelegate(bool);
    void OnFadeOutDelegate(bool);

protected:
    void OnSceneChangeStart(const CSceneChange *) {}
    bool CheckGotoSceneChange(const CSceneChange *);
    
public:
    void SetSuspend(bool bInSuspend) { bSuspend = bInSuspend; }
    bool IsSuspend() { return bSuspend; }

private:
    bool bSignOutDialogDoing {}; // 0xA68
    int32_t SignOutDialogCountDown {}; // 0xA6C
};
