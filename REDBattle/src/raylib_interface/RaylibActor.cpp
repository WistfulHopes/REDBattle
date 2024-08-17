﻿#include "RaylibActor.h"

#include "raylib.h"
#include "Game/Battle/Object/obj_base.h"
#include "Game/Scene/scene_Battle.h"

RaylibActor::RaylibActor(OBJ_CBase* inObj) : parentObj(inObj)
{
}

void RaylibActor::LoadSprites()
{
    int imgPacSize = 0;

    char imgPacPath[256] = "\\assets\\IMG_";
    if (parentObj->m_IsPlayerObj)
    {
        strcat(imgPacPath, ((OBJ_CCharBase*)parentObj)->m_CharName.GetStr());
    }
    else
    {
        strcat(imgPacPath, ((OBJ_CCharBase*)parentObj->m_pParentPly.GetPtr())->m_CharName.GetStr());
        strcat(imgPacPath, "EF");
    }
    strcat(imgPacPath, ".pac");

    imgPac.SetPackFile(LoadFileData((std::string(GetApplicationDirectory()) + imgPacPath).data(), &imgPacSize));
}

bool RaylibActor::SetSprite(const char* imgName)
{
    if (!strncmp(imgName, curSpriteName, 0x20)) return true;
    if (textures.find(imgName) != textures.end()) return true;
    
    auto idx = imgPac.SearchFileID(imgName);

    if ((int)idx == -1) return false;

    strcpy(curSpriteName, imgName);

    auto offset = imgPac.GetPackOffsetAddr(idx);
    auto size = imgPac.GetPackOffsetFileSize(idx);

    auto img = LoadImageFromMemory(".png", (unsigned char*)offset, size);

    auto texture = LoadTextureFromImage(img);
    UnloadImage(img);

    textures.insert(std::make_pair(std::string(imgName), texture));
    
    return true;
}

void RaylibActor::Draw()
{
    const auto imgName = parentObj->m_ClsnAnalyzer.GetImageFileName(0);
    if (!imgName) return;
    
    if (!SetSprite(imgName)) return;

    Rectangle source;
    source.x = parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_X;
    source.y = parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_Y;
    if (parentObj->GetObjDir() == 0) source.width = -parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_W;
    else source.width = parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_W;
    source.height = parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_H;

    Vector3 raylibPos{};

    red::btl::GamePos2RaylibPos(parentObj->m_PosX, parentObj->GetPosY(), parentObj->m_PosZ, raylibPos);

    Rectangle dest;
    dest.x = raylibPos.x;
    dest.y = -raylibPos.y;
    dest.width = parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_W;
    dest.height = parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_H;

    Vector2 origin;
    if (parentObj->GetObjDir() == 0) origin.x = dest.width - parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_X;
    else origin.x = parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_X;
    origin.y = -parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_Y;

    DrawTexturePro(textures[imgName], source, dest, origin, 0, WHITE);
}
