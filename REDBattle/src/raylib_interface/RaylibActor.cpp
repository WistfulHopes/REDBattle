#include "RaylibActor.h"

#include "raylib.h"
#include "Game/Battle/Object/obj_base.h"
#include "Game/Scene/scene_Battle.h"

RaylibActor::RaylibActor(OBJ_CBase* inObj) : parentObj(inObj)
{
}

void RaylibActor::LoadSprites()
{
    int imgPackSize = 0;

    char imgPackPath[256] = "\\assets\\sprites\\IMG_";
    if (parentObj->m_IsPlayerObj)
    {
        strcat(imgPackPath, ((OBJ_CCharBase*)parentObj)->m_CharName.GetStr());
    }
    else
    {
        strcat(imgPackPath, ((OBJ_CCharBase*)parentObj->m_pParentPly.GetPtr())->m_CharName.GetStr());
        strcat(imgPackPath, "EF");
    }
    strcat(imgPackPath, ".pac");

    imgPack.SetPackFile(LoadFileData((std::string(GetApplicationDirectory()) + imgPackPath).data(), &imgPackSize));
}

void RaylibActor::SetSprite()
{
    const auto spriteName = strcat(parentObj->m_CellName.GetStrV(), ".png");
    auto idx = imgPack.SearchFileID(spriteName);

    if ((int)idx == -1) return;
    
    auto offset = imgPack.GetPackOffsetAddr(idx);
    auto size = imgPack.GetPackOffsetFileSize(idx);

    auto img = LoadImageFromMemory(".png", (unsigned char*)((uintptr_t)imgPack.GetPackFile() + (uintptr_t)offset),
                                   size);

    texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void RaylibActor::Draw()
{
    SetSprite();
    
    Rectangle source;
    source.x = parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_X;
    source.y = parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_Y;
    if (parentObj->GetObjDir() == 0) source.width = parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_W;
    else source.width = -parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_W;
    source.height = parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_H;

    Vector3 raylibPos{};

    red::btl::GamePos2RaylibPos(parentObj->m_PosX, parentObj->GetPosY(), parentObj->m_PosZ, raylibPos);

    Rectangle dest;
    dest.x = raylibPos.x;
    dest.y = raylibPos.y;
    dest.width = parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_W;
    dest.height = parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_H;

    Vector2 origin;
    if (parentObj->GetObjDir() == 0) origin.x = parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_X;
    else origin.x = -parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_X;
    origin.y = -parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_Y;

    DrawTexturePro(texture, source, dest, origin, 0, RAYWHITE);
}
