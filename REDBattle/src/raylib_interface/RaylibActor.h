#pragma once
#include "raylib.h"
#include "AALib/Common/tl_Filepack.h"

class OBJ_CBase;

class RaylibActor
{
    OBJ_CBase* parentObj {};
    AA_Filepack_FPAC imgPack {};
    Texture2D texture;
    
public:
    RaylibActor() {}
    RaylibActor(OBJ_CBase* inObj);

    void LoadSprites();
    void SetSprite();
    void Draw();
};
