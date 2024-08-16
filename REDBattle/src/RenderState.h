#pragma once
#include "raylib.h"

class AA_CCamera;

class RenderState
{
    Camera2D cam {};
    Camera3D cam3D {};
    AA_CCamera* sysCamera {};
public:
    void Init();
    void SetSysCamera(AA_CCamera* inSysCamera) { sysCamera = inSysCamera; }
    void UpdateCamera();
    void Draw();
};
