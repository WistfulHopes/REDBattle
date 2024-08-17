#pragma once
#include <vector>

#include "raylib.h"

class SCENE_CBase;
class OBJ_CBase;
class RaylibActor;
class AA_CCamera;

class RaylibState
{
    Camera2D cam {};
    Camera3D cam3D {};
    AA_CCamera* sysCamera {};

    std::vector<RaylibActor*> actors;
    
public:
    void Init(SCENE_CBase* scene);
    void SetSysCamera(AA_CCamera* inSysCamera) { sysCamera = inSysCamera; }
    void UpdateCamera();
    void Draw();

    void AddRaylibActor(OBJ_CBase* obj);
};
