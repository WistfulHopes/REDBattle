#pragma once
#include <string>
#include <unordered_map>

#include "raylib.h"
#include "AALib/Common/tl_Filepack.h"

class OBJ_CBase;

class RaylibActor
{
    OBJ_CBase* parentObj{};
    AA_Filepack_FPAC imgPac{};
    std::pmr::unordered_map<std::string, Texture> textures{};
    char curSpriteName[0x20]{};

public:
    RaylibActor()
    {
    }

    RaylibActor(OBJ_CBase* inObj);

    ~RaylibActor();
    
    void LoadSprites();
    bool SetSprite(const char* imgName);
    void Draw();
};
