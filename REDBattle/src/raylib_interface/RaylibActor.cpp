#include "RaylibActor.h"

#include "raylib.h"
#include "RaylibDraw.h"
#include "Game/Battle/Object/obj_base.h"
#include "Game/Scene/scene_Battle.h"

RaylibActor::RaylibActor(OBJ_CBase* inObj) : parentObj(inObj)
{
}

RaylibActor::~RaylibActor()
{
    for (auto kv : textures)
    {
        UnloadTexture(kv.second);
    }
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

    const auto offset = imgPac.GetPackOffsetAddr(idx);
    const auto size = imgPac.GetPackOffsetFileSize(idx);

    const auto img = LoadImageFromMemory(".png", (unsigned char*)offset, size);

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

    auto scene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());

    Vector2 size;
    size.x = parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_W * scene->GetBattleScreenManager()->GetLinkMagn();
    size.y = parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_H * scene->GetBattleScreenManager()->GetLinkMagn();

    Vector3 raylibPos{};

    red::btl::GamePos2RaylibPos(parentObj->m_PosX, parentObj->GetPosY(), parentObj->m_PosZ, raylibPos);

    Vector3 dest;
    dest.x = -raylibPos.x + (parentObj->GetObjDir() == 0 ? size.x / 2 : -size.x / 2);
    dest.y = raylibPos.y + size.y;
    dest.z = raylibPos.z;

    if (parentObj->GetObjDir() == 0) dest.x += parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_X * scene->
        GetBattleScreenManager()->GetLinkMagn();
    else dest.x -= parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_X * scene->GetBattleScreenManager()->GetLinkMagn();
    dest.y += parentObj->m_ClsnAnalyzer.GetViewWorldRect(0).m_Y * scene->GetBattleScreenManager()->GetLinkMagn();

    Vector2 texcoords[4];

    if (parentObj->GetObjDir() == 0)
    {
        texcoords[0] = Vector2{
            parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_X / (float)textures[imgName].width,
            -parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_Y / (float)textures[imgName].height
        };
        texcoords[1] = Vector2{
            parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_X / (float)textures[imgName].width,
            -(parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_Y + parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_H)
            / (float)textures[imgName].height
        };
        texcoords[2] = Vector2{
            (parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_X + parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_W)
            / (float)textures[imgName].width,
            -(parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_Y + parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_H)
            / (float)textures[imgName].height
        };
        texcoords[3] = Vector2{
            (parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_X + parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_W)
            / (float)textures[imgName].width,
            -parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_Y / (float)textures[imgName].height
        };
    }
    else
    {
        texcoords[0] = Vector2{
            (parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_X + parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_W)
            / (float)textures[imgName].width,
            -parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_Y / (float)textures[imgName].height
        };
        texcoords[1] = Vector2{
            (parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_X + parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_W)
            / (float)textures[imgName].width,
            -(parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_Y + parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_H)
            / (float)textures[imgName].height
        };
        texcoords[2] = Vector2{
            parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_X / (float)textures[imgName].width,
            -(parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_Y + parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_H)
            / (float)textures[imgName].height
        };
        texcoords[3] = Vector2{
            parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_X / (float)textures[imgName].width,
            -parentObj->m_ClsnAnalyzer.GetViewTextureRect(0).m_Y / (float)textures[imgName].height
        };
    }

    DrawTexturePlane(textures[imgName], dest, size, texcoords, WHITE);
}
