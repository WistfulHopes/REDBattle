﻿#include "RaylibState.h"

#include "RaylibActor.h"
#include "AALib/Base/sys_Camera.h"
#include "Game/Scene/scene_Battle.h"

void RaylibState::Init(SCENE_CBase* scene)
{
    for (auto actor : actors)
    {
        delete actor;
    }
    actors.clear();
    
    cam3D.up = {0, 1, 0};
    cam3D.fovy = 54;
    cam3D.projection = CAMERA_PERSPECTIVE;

    if (auto battleScene = dynamic_cast<SCENE_CBattle*>(scene))
    {
        AddRaylibActor(battleScene->GetBattleObjectManager()->GetPlayer(SIDE_1P, MemberID_01));
        AddRaylibActor(battleScene->GetBattleObjectManager()->GetPlayer(SIDE_2P, MemberID_01));
    }
}

void RaylibState::UpdateCamera()
{
    if (!sysCamera) return;

    cam.offset = Vector2 { 640, 360 };
    cam.target = Vector2 { sysCamera->GetPos().X, -sysCamera->GetPos().Y + 135 };
    cam.rotation = 0;
    cam.zoom = 1;
    
    cam3D.position.x = sysCamera->GetPos().X;
    cam3D.position.y = sysCamera->GetPos().Y;
    cam3D.position.z = sysCamera->GetPos().Z;
    cam3D.up.x = sysCamera->GetUp().X;
    cam3D.up.y = sysCamera->GetUp().Y;
    cam3D.up.z = sysCamera->GetUp().Z;
    cam3D.target.x = sysCamera->GetLookAt().X;
    cam3D.target.y = sysCamera->GetLookAt().Y;
    cam3D.target.z = sysCamera->GetLookAt().Z;
    cam3D.fovy = atanf(sysCamera->GetFOV()) * 57.2957795f;
}

void RaylibState::Draw()
{
    UpdateCamera();

    BeginMode3D(cam3D);

    DrawGrid(20, 62.5f);

    DrawCubeV({0, 0, 0}, {10, 10, 10}, RED);
    DrawCubeWiresV({0, 0, 0}, {10, 10, 10}, MAROON);

    DrawCubeV({0, 50, 0}, {10, 10, 10}, RED);
    DrawCubeWiresV({0, 50, 0}, {10, 10, 10}, MAROON);

    EndMode3D();

    BeginMode2D(cam);

    for (auto actor : actors)
    {
        actor->Draw();
    }
    
    EndMode2D();
}

void RaylibState::AddRaylibActor(OBJ_CBase* obj)
{
    actors.push_back(new RaylibActor(obj));
    actors.back()->LoadSprites();
}
