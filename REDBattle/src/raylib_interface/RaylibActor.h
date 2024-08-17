#pragma once
#include "raylib.h"
#include "AALib/Common/tl_Filepack.h"

class OBJ_CBase;

class RaylibActor
{
    OBJ_CBase* parentObj {};
    AA_Filepack_FPAC imgPac {};
    Texture2D texture {};
    char curSpriteName[0x20];
    
public:
    RaylibActor() {}
    RaylibActor(OBJ_CBase* inObj);

    void LoadSprites();
    bool SetSprite();
    void Draw();
};
