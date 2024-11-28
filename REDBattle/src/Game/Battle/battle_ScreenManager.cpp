#include "battle_ScreenManager.h"

#include <set>
#include <AALib/AASystemRED.h>

#include "Game/REDGameCommon.h"
#include "Game/Scene/scene_Battle.h"

const int ScreenY_TargetOffset = -100;

bool BATTLE_CScreenManager::LinkCameraMove()
{
    if (!m_pCamera) return false;

    auto dir = AA_Vector3();
    m_pCamera->CreateVec3Dir(&dir);

    float normalY = 0;
    auto len = sqrtf(dir.X * dir.X + dir.Z * dir.Z);

    if (len != 0.f)
    {
        normalY = dir.Y / len;
    }

    auto normalX = -(normalY * dir.X);
    auto normalZ = -(normalY * dir.Z);

    auto unk = normalX * normalX + len + normalZ * normalZ;
    if (FLT_EPSILON < unk)
    {
        auto tmp = 1.f / sqrtf(unk);
        tmp += tmp * (0.5 - (unk * 0.5) * (tmp * tmp));
        tmp += tmp * (0.5 - (unk * 0.5) * (tmp * tmp));
        normalX *= tmp;
        len *= tmp;
        normalZ *= tmp;
    }

    auto unkZ = len * dir.Z - normalZ * dir.Y;
    auto unkX = len * dir.X - normalX * dir.Z;
    auto unkY = len * dir.Y - len * dir.X;

    auto len2Sq = unkX * unkX + unkZ * unkZ + unkY * unkY;
    if (FLT_EPSILON < len2Sq)
    {
        auto tmp = 1.f / sqrt(len2Sq);
        tmp += tmp * (0.5 - (unk * 0.5) * (tmp * tmp));
        tmp += tmp * (0.5 - (unk * 0.5) * (tmp * tmp));
        unkZ *= tmp;
        unkX *= tmp;
        unkY *= tmp;
    }

    auto moveXLinkMagn = (float)m_MoveX * m_LinkMagn;
    auto moveYLinkMagn = (float)m_MoveY * m_LinkMagn;
    auto screenW = (float)m_ScreenW * 0.421875f;

    auto posX = m_pCamera->GetPosX() - moveYLinkMagn * normalZ + unkZ * moveXLinkMagn;
    auto posY = m_pCamera->GetPosY() - moveYLinkMagn * normalX + unkX * moveXLinkMagn;
    auto posZ = screenW - len * moveYLinkMagn + unkY * moveXLinkMagn;

    m_pCamera->SetPos(posX, posY, posZ);

    auto upX = normalX;
    auto upY = len;
    auto upZ = normalZ;

    // m_pCamera->SetUp(upX, upY, upZ);

    auto atX = dir.X + posX;
    auto atY = dir.Y + posY;
    auto atZ = dir.Z + posZ;

    m_pCamera->SetLookAt(atX, atY, atZ);

    // TODO world side break

    auto worldWidthScale = 3200;
    auto tmp = (float)worldWidthScale * 6 /* matrix list num */ * m_LinkMagn * 0.15915494f;
    auto worldWidth = (float)worldWidthScale + 1500.f;
    AA_Rotator rot = AA_Rotator(0, (float)m_ScreenWorldCenterX * m_LinkMagn * (-57.295776f / tmp), 0);

    if constexpr (false) // TODO world side break
    {
        m_WorldSideMoveDeg = rot.Yaw;
    }

    rot.Yaw = m_WorldSideMoveDeg;

    float unk2 = 1.0;

    auto worldSideMoveValue = (float)(m_WorldSideMoveValue % 6) * 60;
    if (worldSideMoveValue <= rot.Yaw)
    {
        if (worldSideMoveValue < rot.Yaw)
        {
            rot.Yaw -= 60;
            m_WorldSideMoveDeg = rot.Yaw;

            if (rot.Yaw < worldSideMoveValue)
            {
                m_WorldSideMoveDeg = worldSideMoveValue;
                rot.Yaw = worldSideMoveValue;
            }
            else
            {
                unk2 = 1 - abs(worldSideMoveValue - rot.Yaw) / 60;
            }
        }
    }
    else
    {
        rot.Yaw += 60;
        m_WorldSideMoveDeg = rot.Yaw;

        if (rot.Yaw > worldSideMoveValue)
        {
            m_WorldSideMoveDeg = worldSideMoveValue;
            rot.Yaw = worldSideMoveValue;
        }
        else
        {
            unk2 = 1 - abs(worldSideMoveValue - rot.Yaw) / 60;
        }
    }

    auto scale = 3200;

    auto matTmp = (float)worldWidthScale * (float)m_WorldSideMoveValuePrev * m_LinkMagn;
    matTmp = (float)scale * (float)m_WorldSideMoveValue * m_LinkMagn - matTmp * unk2 + matTmp;

    auto mat = AA_Matrix(AA_Vector4(1, 0, 0, 0),
                         AA_Vector4(0, 1, 0, 0),
                         AA_Vector4(0, 0, 1, 0),
                         AA_Vector4(matTmp, 0, m_pCamera->GetPosZ(), 1));

    rot.Pitch = 0;
    rot.Roll = 0;

    auto rotMat = AA_Matrix(rot);

    auto worldWidthNegative = -worldWidth;

    auto rotMat0 = AA_Vector4(rotMat.M[0][0], rotMat.M[0][1], rotMat.M[0][2], rotMat.M[0][3]);
    auto rotMat1 = AA_Vector4(rotMat.M[1][0], rotMat.M[1][1], rotMat.M[1][2], rotMat.M[1][3]);
    auto rotMat2 = AA_Vector4(rotMat.M[2][0], rotMat.M[2][1], rotMat.M[2][2], rotMat.M[2][3]);
    auto rotMat3 = AA_Vector4(rotMat.M[1][0] * worldWidth + rotMat.M[2][0] * m_pCamera->GetPosZ() + rotMat.M[3][0],
                              rotMat.M[1][1] * worldWidth + rotMat.M[2][1] * m_pCamera->GetPosZ() + rotMat.M[3][1],
                              rotMat.M[1][2] * worldWidth + rotMat.M[2][2] * m_pCamera->GetPosZ() + rotMat.M[3][2],
                              rotMat.M[1][3] * worldWidth + rotMat.M[2][3] * m_pCamera->GetPosZ() + rotMat.M[3][3]);

    rotMat0.Y = rotMat0.Y + rotMat0.W * worldWidthNegative;
    rotMat1.Y = rotMat1.Y + rotMat1.W * worldWidthNegative;
    rotMat2.Y = rotMat2.Y + rotMat2.W * worldWidthNegative;
    rotMat3.Y = rotMat3.Y + rotMat3.W * worldWidthNegative;

    auto matInv = mat.Inverse();

    m_OffsetMatrix.M[0][0] = matInv.M[0][0] * rotMat0.X + matInv.M[0][1] * rotMat1.X + matInv.M[0][2] * rotMat2.X + matInv.M[0][3] * rotMat3.X; 
    m_OffsetMatrix.M[0][1] = matInv.M[0][0] * rotMat0.Y + matInv.M[0][1] * rotMat1.Y + matInv.M[0][2] * rotMat2.Y + matInv.M[0][3] * rotMat3.Y; 
    m_OffsetMatrix.M[0][2] = matInv.M[0][0] * rotMat0.Z + matInv.M[0][1] * rotMat1.Z + matInv.M[0][2] * rotMat2.Z + matInv.M[0][3] * rotMat3.Z; 
    m_OffsetMatrix.M[0][3] = matInv.M[0][0] * rotMat0.W + matInv.M[0][1] * rotMat1.W + matInv.M[0][2] * rotMat2.W + matInv.M[0][3] * rotMat3.W;
    m_OffsetMatrix.M[1][0] = matInv.M[1][0] * rotMat0.X + matInv.M[1][1] * rotMat1.X + matInv.M[1][2] * rotMat2.X + matInv.M[1][3] * rotMat3.X; 
    m_OffsetMatrix.M[1][1] = matInv.M[1][0] * rotMat0.Y + matInv.M[1][1] * rotMat1.Y + matInv.M[1][2] * rotMat2.Y + matInv.M[1][3] * rotMat3.Y; 
    m_OffsetMatrix.M[1][2] = matInv.M[1][0] * rotMat0.Z + matInv.M[1][1] * rotMat1.Z + matInv.M[1][2] * rotMat2.Z + matInv.M[1][3] * rotMat3.Z; 
    m_OffsetMatrix.M[1][3] = matInv.M[1][0] * rotMat0.W + matInv.M[1][1] * rotMat1.W + matInv.M[1][2] * rotMat2.W + matInv.M[1][3] * rotMat3.W;
    m_OffsetMatrix.M[2][0] = matInv.M[2][0] * rotMat0.X + matInv.M[2][1] * rotMat1.X + matInv.M[2][2] * rotMat2.X + matInv.M[2][3] * rotMat3.X; 
    m_OffsetMatrix.M[2][1] = matInv.M[2][0] * rotMat0.Y + matInv.M[2][1] * rotMat1.Y + matInv.M[2][2] * rotMat2.Y + matInv.M[2][3] * rotMat3.Y; 
    m_OffsetMatrix.M[2][2] = matInv.M[2][0] * rotMat0.Z + matInv.M[2][1] * rotMat1.Z + matInv.M[2][2] * rotMat2.Z + matInv.M[2][3] * rotMat3.Z; 
    m_OffsetMatrix.M[2][3] = matInv.M[2][0] * rotMat0.W + matInv.M[2][1] * rotMat1.W + matInv.M[2][2] * rotMat2.W + matInv.M[2][3] * rotMat3.W;
    m_OffsetMatrix.M[3][0] = matInv.M[3][0] * rotMat0.X + matInv.M[3][1] * rotMat1.X + matInv.M[3][2] * rotMat2.X + matInv.M[3][3] * rotMat3.X; 
    m_OffsetMatrix.M[3][1] = matInv.M[3][0] * rotMat0.Y + matInv.M[3][1] * rotMat1.Y + matInv.M[3][2] * rotMat2.Y + matInv.M[3][3] * rotMat3.Y; 
    m_OffsetMatrix.M[3][2] = matInv.M[3][0] * rotMat0.Z + matInv.M[3][1] * rotMat1.Z + matInv.M[3][2] * rotMat2.Z + matInv.M[3][3] * rotMat3.Z;
    m_OffsetMatrix.M[3][3] = matInv.M[3][0] * rotMat0.W + matInv.M[3][1] * rotMat1.W + matInv.M[3][2] * rotMat2.W + matInv.M[3][3] * rotMat3.W;

    return true;
}

BATTLE_CScreenManager::BATTLE_CScreenManager()
{
    m_ObjLeft = 0;
    m_ObjRight = 0;
    m_ObjTop = 0;
    m_ObjBottom = 0;
    m_ObjLenX = 0;
    m_ObjLenY = 0;
    m_ScreenWorldCenterX = 0;
    m_ScreenWorldCenterY = 0;
    m_ScreenWorldLeft = 0;
    m_ScreenWorldRight = 0;
    m_TargetCenterX = 0;
    m_TargetCenterY = 0;
    m_TargetWidth = 0;
    m_VelCenterX = 0;
    m_VelCenterY = 0;
    m_VelWidth = 0;
    m_SetPosX = 0;
    m_SetPosY = 0;
    m_SetPosW = 0;
    m_ObjectScale = 0;
    m_ScreenX = 0;
    m_ScreenY = 0;
    m_ScreenXLeft = 0;
    m_ScreenYUp = 0;
    m_MoveX = 0;
    m_MoveY = 0;
    m_LinkMagn = 1;
    m_LinkMagnRecip = 1;
    m_Flag = 0;
    m_TargetOffsetAirYMax = 180;
    m_TargetOffsetAirYAdd = 3;
    m_TargetOffsetAirYPos = 400;
    m_TargetOffsetAirYDist = 570;
    m_TargetOffsetLandYMax = 350;
    m_TargetOffsetLandYAdd = 6;
    m_TargetOffsetY = 350;
    m_ZoomMoveY = 0;
    m_ZoomOutBeginDistX = 1280;
    m_ZoomOutBeginDistY = 600;
    m_MaxZoomOutWidth = 1536;
    m_bTouchWorldSide = false;
    m_ScreenWorldWidth = 1280;
    m_ShakeX = 0;
    m_ShakeY = 0;
    m_ShakeTime = 0;
    m_ScreenCollisionLeft = 0;
    m_ScreenCollisionRight = 0;
    m_ScreenCollisionYUp = 0;
    m_ScreenCenterXNoShake = 0;
    m_ScreenCenterYNoShake = 0;
    m_LastFlag = 0;
    m_Stable = false;
    m_bStopScreenPositionUpdate = false;
    m_pCamera = nullptr;
    m_WorldLeftSide = -1600;
    m_WorldRightSide = 1600;
    m_WorldTopSide = 5400;
    m_TargetObjectNum = 0;
    m_WorldSideMoveValue = 0;
    m_WorldSideMoveValuePrev = 0;
    m_WorldSideMoveDir = 0;
    m_WorldSideMoveResetDir = 0;
    m_WorldSideMoveDeg = 0;
    auto a = AA_Vector4(1, 0, 0, 0);
    auto b = AA_Vector4(0, 1, 0, 0);
    auto c = AA_Vector4(0, 0, 1, 0);
    auto d = AA_Vector4(0, 0, 0, 1);
    m_OffsetMatrix.Set(a, b, c, d);
    m_PrevCameraMatrix.Set(a, b, c, d);
}

float CalcBattleCameraLinkMagn(AA_CCamera* cam, AA_Vector3& pos0, AA_Vector3& pos1)
{
    auto vecPos0 = AA_Vector4(pos0, 1);
    vecPos0 = cam->GetViewProjMatrix().TransformFVector4(vecPos0);
    vecPos0 /= vecPos0.W;
    auto vecPos1 = AA_Vector4(pos1, 1);
    vecPos1 = cam->GetViewProjMatrix().TransformFVector4(vecPos1);
    vecPos1 /= vecPos1.W;

    const float sx = vecPos0.X * 640.f - vecPos1.X * 640.f;
    const float sy = vecPos0.Y * -360.f - vecPos1.Y * -360.f;

    return 1.f / sqrtf(sx * sx + sy * sy) * (pos0 - pos1).Size();
}

void BATTLE_CScreenManager::ResetScreenManager()
{
    m_pCamera = AASystemRED::GetInstance()->GetCameraManager().Get(0);
    if (m_pCamera)
    {
        m_pCamera->SetFOV(0.558505f); // y fov
        m_pCamera->SetBackClip(-50000);
        m_pCamera->SetBasePos(0, 106.4231f, 540);
        m_pCamera->SetPos(0, 106.4231f, 540);
        m_pCamera->SetBaseLookAt(0, 106.4231f, 0);
        m_pCamera->SetLookAt(0, 106.4231f, 0);
        m_pCamera->SetAspectRatio(16.f / 9.f);
    }

    auto pos0 = AA_Vector3(0, 0, 0);
    auto pos1 = AA_Vector3(1, 1, 0);
    if (m_pCamera)
    {
        m_pCamera->Update();
        m_LinkMagn = CalcBattleCameraLinkMagn(m_pCamera, pos0, pos1);
        m_LinkMagnRecip = 1 / m_LinkMagn;
    }

    m_bStopScreenPositionUpdate = false;
    m_ScreenCenterXNoShake = 0;
    m_ScreenCenterYNoShake = 0;
    m_TargetCenterX = 0;
    m_TargetCenterY = 0;
    m_ScreenWorldCenterX = 0;
    m_ScreenWorldCenterY = 0;
    m_TargetWidth = 1280;
    m_VelCenterX = 0;
    m_VelCenterY = 0;
    m_VelWidth = 0;
    m_ScreenWorldWidth = 1280;
    m_DelayW = 0;
    m_ShakeTime = 0;
    m_ScreenX = 0;
    m_ScreenY = 0;
    m_ScreenW = 1280;
    m_ScreenCameraControl.m_Target.SetX(0);
    m_ScreenCameraControl.m_Target.SetY(0);
    m_ScreenCameraControl.m_Target.SetZ(1);
    m_ScreenCameraControl.m_Param.SetX(0);
    m_ScreenCameraControl.m_Param.SetY(0);
    m_ScreenCameraControl.m_Param.SetZ(1);
    m_ScreenCameraControl.m_Vel.SetX(0);
    m_ScreenCameraControl.m_Vel.SetY(0);
    m_ScreenCameraControl.m_Vel.SetZ(0);
    m_ScreenCameraControl.m_Hold = true;
    m_ScreenCameraControl.m_Repeat = true;
    m_ScreenCameraControl.m_FixX = true;
    m_ScreenCameraControl.m_FixY = true;
    m_ScreenCameraControl.m_FixZ = true;
    m_ScreenCameraControl.m_Level = 1;
    m_ScreenCameraControl.m_Friction = 1;
    m_ScreenCameraControl.m_Flag = 0;

    if (m_pCamera)
    {
        m_pCamera->ResetPos();
        m_pCamera->ResetLookAt();
        m_pCamera->ResetUp();
        m_pCamera->Update();
    }
    m_WorldLeftSide = -1600;
    m_WorldRightSide = 1600;
    m_WorldTopSide = 5400;
}

void BATTLE_CScreenManager::SetScreenCornerObject(bool bQuick)
{
    int32_t v5 = 0;
    int32_t v31 = 0;
    int32_t v50 = 0;
    int32_t arg_8 = 0;

    if (m_TargetObjectNum <= 0)
    {
        m_ObjTop = 0;
        m_ObjBottom = 0;
        m_ObjLeft = 0;
        m_ObjRight = 0;
    }
    else
    {
        int32_t objBottom = 0;

        for (uint32_t i = 0; i < m_TargetObjectNum; i++)
        {
            auto objRef = &m_ppObject[i];
            auto flag = m_TargetObjectFlag[i] & 1;

            if (objRef == nullptr) objBottom = arg_8;
            else if (flag == 0)
            {
            START:
                int l, t, r, b;

                (*objRef)->GetPushScreenRect(l, t, r, b);

                int screenWorldCenterX = l = l / 1000;
                int screenWorldRight = r = r / 1000;
                int screenWorldCenterY = t = t / 1000;
                objBottom = b /= 1000;

                if (flag)
                {
                    l = r = screenWorldCenterX = m_ScreenWorldCenterX;
                    objBottom = t = b = screenWorldCenterY = m_ScreenWorldCenterY;
                }
                if (screenWorldCenterX < m_ScreenWorldLeft) l = screenWorldCenterX = m_ScreenWorldLeft;
                if (screenWorldRight > m_ScreenWorldRight) r = screenWorldRight = m_ScreenWorldRight;

                objBottom = b;
                screenWorldRight = r;
                screenWorldCenterY = t;
                screenWorldCenterX = l;

                const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                    GetBattleObjectManager();

                if (objManager->m_BOMFlag & BOMFLG_TUTORIAL_CAMERA_MODE)
                {
                    auto obj = *objRef;
                    if (obj->m_SideID == SIDE_2P)
                    {
                        auto plyPos = obj->m_pParentPly.GetPtr()->GetPosX();
                        auto tgtPos = obj->m_pTargetObj.GetPtr()->GetPosX();

                        int32_t screenWorldCenterX2;

                        if (tgtPos < plyPos)
                        {
                            screenWorldCenterX2 = tgtPos / 1000 + 560;
                        }
                        else if (tgtPos > plyPos)
                        {
                            screenWorldCenterX2 = tgtPos / 1000 - 560;
                        }
                        else
                        {
                            screenWorldCenterX2 = tgtPos / 1000;
                        }

                        screenWorldRight = r;
                        screenWorldCenterX = l;
                        screenWorldCenterY = t;

                        v5 = v50;

                        if (r > screenWorldCenterX2) screenWorldRight = screenWorldCenterX2;
                        if (l < screenWorldCenterX2) screenWorldCenterX = screenWorldCenterX2;

                        r = screenWorldRight;
                        objBottom = b;
                        l = screenWorldCenterX;
                    }
                }

                if (arg_8 != 0)
                {
                    auto objLeft = m_ObjLeft;
                    if (screenWorldCenterX < objLeft) objLeft = screenWorldCenterX;
                    m_ObjLeft = objLeft;

                    auto objRight = m_ObjRight;
                    if (screenWorldRight > objRight) objRight = screenWorldRight;
                    m_ObjRight = objRight;

                    auto objTop = m_ObjTop;
                    if (screenWorldCenterY > objTop) objTop = screenWorldCenterY;
                    m_ObjTop = objTop;

                    auto tmp_objBottom = m_ObjBottom;
                    if (b < tmp_objBottom) tmp_objBottom = b;
                    m_ObjBottom = tmp_objBottom;

                    if (b > v5) v5 = b;
                    v50 = v5;
                    objBottom = arg_8;
                }
                else
                {
                    v5 = v50 = m_ObjBottom = objBottom;
                    objBottom = 1;
                    arg_8 = 1;
                    m_ObjLeft = screenWorldCenterX;
                    m_ObjRight = screenWorldRight;
                    m_ObjTop = screenWorldCenterY;
                }
            }
            else if ((*objRef)->IsDead())
            {
                objBottom = arg_8;
            }
            else
            {
                auto obj = *objRef;
                auto ply = (OBJ_CCharBase*)obj->m_pParentPly.GetPtr();

                if (ply->IsEntry() && ply->IsEntryBattle() && ply->IsEntryBattleDoing())
                {
                    goto START;
                }

                objBottom = arg_8;
            }
        }

        if (objBottom == 0)
        {
            m_ObjTop = 0;
            m_ObjBottom = 0;
            m_ObjLeft = 0;
            m_ObjRight = 0;
        }
    }

    m_ObjLenX = m_ObjRight - m_ObjLeft;
    m_ObjBox.left = m_ObjLeft;
    m_ObjLenY = m_ObjTop - m_ObjBottom;
    m_ObjBox.right = m_ObjRight;
    m_ObjBox.top = m_ObjTop;
    m_ObjBox.bottom = m_ObjBottom;
    m_ObjBox.higherBottom = v5;
}

bool BATTLE_CScreenManager::UpdateScreenPosition(bool bQuick)
{
    m_MaxZoomOutWidth = 1689;
    m_ZoomOutBeginDistX = 1280;
    m_ZoomOutBeginDistY = 600;

    if (m_bStopScreenPositionUpdate) return true;

    SetScreenCornerObject(bQuick);

    m_ScreenWorldCenterX = m_ScreenCenterXNoShake;
    m_ScreenWorldCenterY = m_ScreenCenterYNoShake;

    if ((m_Flag & 1) == 0)
    {
        auto flag = m_Flag;
        if ((flag & 4) == 0) m_TargetCenterX = ObjBox()->CenterX();
        if ((flag & 2) == 0)
        {
            auto zoomOut = m_ZoomOutBeginDistX / 4 + ObjBox()->Width();
            int32_t widthY;
            if (zoomOut >= m_ZoomOutBeginDistX)
            {
                auto zoomWidth = 1280;
                widthY = m_MaxZoomOutWidth;

                if (zoomOut > 1280) zoomWidth = zoomOut;
                if (zoomWidth < m_MaxZoomOutWidth) widthY = zoomWidth;
            }
            else
            {
                widthY = 1280;
            }

            m_WidthY = widthY;
            if (widthY < m_MaxZoomOutWidth) m_TargetWidth = widthY;
        }
        if ((flag & 8) == 0)
        {
            auto targetOffsetAirYMax = ScreenY_TargetOffset + 350;
            m_TargetOffsetLandYMax = targetOffsetAirYMax;

            int tmp = 1280000 / m_TargetWidth;
            if (tmp * ObjBox()->Bottom() / 1000 <= m_TargetOffsetAirYPos ||
                tmp * (ObjBox()->HigherBottom() - ObjBox()->Bottom()) / 1000 >= m_TargetOffsetAirYDist)
            {
                if (m_TargetOffsetY + m_TargetOffsetLandYAdd < targetOffsetAirYMax)
                {
                    targetOffsetAirYMax = m_TargetOffsetY + m_TargetOffsetLandYAdd;
                }
            }
            else
            {
                targetOffsetAirYMax = m_TargetOffsetAirYMax;
                if (m_TargetOffsetY - m_TargetOffsetLandYAdd > targetOffsetAirYMax)
                {
                    targetOffsetAirYMax = m_TargetOffsetY - m_TargetOffsetLandYAdd;
                }
            }
            m_TargetOffsetY = targetOffsetAirYMax;

            int32_t worldTopSide;

            if (ObjBox()->HigherBottom() - ObjBox()->Bottom() > m_ZoomOutBeginDistY)
            {
                auto maxZoomWidth = ObjBox()->HigherBottom() - ObjBox()->Bottom() + 1280;

                if (maxZoomWidth > m_MaxZoomOutWidth) maxZoomWidth = m_MaxZoomOutWidth;
            }

            auto widthY = 1000 * m_MaxZoomOutWidth / m_WidthY;

            worldTopSide = widthY * ObjBox()->HigherBottom() / 1000 - widthY * targetOffsetAirYMax / 1000;

            if (worldTopSide < 0 || worldTopSide > m_WorldTopSide)
                m_TargetCenterY = m_WorldTopSide;
            else m_TargetCenterY = worldTopSide;
        }
    }

    auto width = m_TargetWidth - m_ScreenWorldWidth;
    m_DelayW = 0;

    if (width > 0)
    {
        auto velWidth = width * 10 / 20 + (width * 10 >> 0x1F);
        velWidth -= velWidth >> 0x1F;
        width = 0x28;
        if (width < velWidth) width = velWidth;

        m_VelWidth = width;
        m_DelayW = 450;
    }
    else if (width == 0)
    {
        m_VelWidth = 0;
        m_DelayW = 450;
    }
    else
    {
        width = width / 14 - 1;
        m_VelWidth = width;
    }

    m_ScreenWorldWidth += m_VelWidth;

    if (bQuick || (m_VelWidth < 0 && m_ScreenWorldWidth <= m_TargetWidth))
    {
        m_ScreenWorldWidth = m_TargetWidth;
        m_VelWidth = 0;
    }

    auto screenXSpeedFrame = 2;
    auto screenXSpeed = 100;

    const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
        GetBattleObjectManager();

    auto velCenterX = screenXSpeedFrame - 5;

    if ((objManager->m_BOMFlag & 0x400000) == 0)
    {
        velCenterX = screenXSpeedFrame;
    }

    m_VelCenterX = (m_TargetCenterX - m_ScreenWorldCenterX) / velCenterX;

    if (m_VelCenterX <= screenXSpeed)
    {
        auto tmpScreenXSpeed = -screenXSpeed;
        screenXSpeed = m_VelCenterX;

        if (screenXSpeed < tmpScreenXSpeed)
        {
            screenXSpeed = m_VelCenterX = tmpScreenXSpeed;
        }
    }
    else m_VelCenterX = screenXSpeed;

    if (m_TargetCenterX - m_ScreenWorldCenterX > 0)
    {
        m_VelCenterX = ++screenXSpeed;
    }
    else if (m_TargetCenterX - m_ScreenWorldCenterX < 0)
    {
        m_VelCenterX = --screenXSpeed;
    }

    m_ScreenWorldCenterX += velCenterX;

    if (bQuick)
    {
        m_ScreenWorldCenterX = m_TargetCenterX;
        m_VelCenterX = 0;
    }
    else
    {
        if (velCenterX <= 0)
        {
            m_ScreenWorldCenterX = m_TargetCenterX;
            m_VelCenterX = 0;
        }

        if (m_ScreenWorldCenterX <= m_TargetCenterX)
        {
            m_ScreenWorldCenterX = m_TargetCenterX;
            m_VelCenterX = 0;
        }
        else
        {
            if (velCenterX > 0 && m_ScreenWorldCenterX > m_TargetCenterX)
            {
                m_ScreenWorldCenterX = m_TargetCenterX;
                m_VelCenterX = 0;
            }
        }
    }

    auto velCenterY = 4000;
    auto screenYSpeed = 70;

    if (m_TargetCenterY - m_ScreenWorldCenterY <= 0) velCenterY = 3000;

    m_VelCenterY = (m_TargetCenterY - m_ScreenWorldCenterY) * 1000 / velCenterY;

    if (m_VelCenterY <= screenYSpeed)
    {
        auto tmpScreenYSpeed = -screenYSpeed;
        screenYSpeed = m_VelCenterY;

        if (screenYSpeed < tmpScreenYSpeed)
        {
            screenYSpeed = m_VelCenterY = tmpScreenYSpeed;
        }
    }
    else m_VelCenterY = screenYSpeed;

    if (m_TargetCenterY - m_ScreenWorldCenterY > 0)
    {
        m_VelCenterY = ++screenYSpeed;
    }
    else if (m_TargetCenterY - m_ScreenWorldCenterY < 0)
    {
        m_VelCenterY = --screenYSpeed;
    }

    m_ScreenWorldCenterY += velCenterY;

    if (bQuick)
    {
        m_ScreenWorldCenterY = m_TargetCenterY;
        m_VelCenterY = 0;
    }
    else
    {
        if (velCenterY <= 0)
        {
            m_ScreenWorldCenterY = m_TargetCenterY;
            m_VelCenterY = 0;
        }

        if (m_ScreenWorldCenterY <= m_TargetCenterY)
        {
            m_ScreenWorldCenterY = m_TargetCenterY;
            m_VelCenterY = 0;
        }
        else
        {
            if (velCenterY > 0 && m_ScreenWorldCenterY > m_TargetCenterY)
            {
                m_ScreenWorldCenterY = m_TargetCenterY;
                m_VelCenterY = 0;
            }
        }
    }

    m_bTouchWorldSide = false;

    if (const auto halfWidth = m_ScreenWorldWidth / 2; m_ScreenWorldCenterX - halfWidth >= m_WorldLeftSide)
    {
        if (m_ScreenWorldCenterX + halfWidth > m_WorldRightSide)
        {
            m_ScreenWorldCenterX -= halfWidth;
            m_bTouchWorldSide = true;
        }
    }
    else
    {
        m_ScreenWorldCenterX += halfWidth;
        m_bTouchWorldSide = true;
    }

    auto shakeX = 0.f;
    auto shakeY = 0.f;

    if (m_ShakeTime % 4 == 1)
    {
        shakeX = m_ShakeX;
        shakeY = m_ShakeY;
    }

    else if (m_ShakeTime % 4 == 3)
    {
        shakeX = -m_ShakeX;
        shakeY = -m_ShakeY;
    }

    if (m_ShakeTime <= 0)
    {
        m_ShakeX = 0;
        m_ShakeY = 0;
    }
    else
    {
        m_ShakeTime--;
        m_ShakeX *= 0.9f;
        m_ShakeY *= 0.9f;
    }

    m_WorldLeftSide = -1600;
    m_WorldRightSide = -1600;

    m_ScreenCollisionLeft = m_ScreenWorldCenterX - m_ScreenWorldWidth / 2;
    m_ScreenCollisionRight = m_ScreenWorldCenterX + m_ScreenWorldWidth / 2;
    m_WorldTopSide = 5400;

    auto worldLeft = -3200;
    auto worldRight = 3200;
    auto worldTop = 10800;

    m_WorldLeftSide = worldLeft;
    m_WorldRightSide = worldRight;
    m_WorldTopSide = worldTop;

    if (m_Flag & 0x1000)
    {
        m_WorldLeftSide -= 640;
        m_WorldRightSide += 640;
    }

    if (m_WorldSideMoveValue)
    {
        m_WorldLeftSide += 3200;
        m_WorldRightSide += 3200;
    }

    if (m_Flag & 0x800)
    {
        m_ScreenCollisionLeft = worldLeft;
        m_ScreenCollisionRight = worldRight;
    }

    m_ScreenCenterYNoShake = m_ScreenWorldCenterY;
    m_ScreenCollisionYUp = 135000.0f / (1280000.0f / m_ScreenWorldWidth) * this->m_LinkMagnRecip + 368000.0f /
        (1280000.0f / m_ScreenWorldWidth) + m_ScreenWorldCenterY;

    m_ScreenCenterXNoShake = m_ScreenWorldCenterX;
    m_ScreenWorldCenterX += m_ShakeX;
    m_ScreenWorldCenterY += m_ShakeY;

    auto flagPre = m_Flag;
    auto flag = m_Flag;

    if (shakeX == 0.0f && shakeY == 0.0f)
    {
        if (m_Flag & 0x200)
        {
            flag = m_Flag & 0xFFFFF8FF | 0x400;
        }
        else
        {
            if (m_Flag & 0x400)
            {
                flag &= ~0x400;
            }
            flag &= 0xFFFFFCFF;
        }
        m_Flag = flag;
    }
    else
    {
        if (m_Flag & 0x400)
        {
            if (flag & 0x100) flag &= ~0x100;
        }
        else
        {
            flag |= 0x100;
        }
        m_Flag = flag;
    }

    auto controlFlag = true;

    auto screenWPre = m_ScreenW;
    auto screenXPre = m_ScreenX;
    auto screenYPre = m_ScreenY;

    m_ScreenWorldLeft = m_ScreenWorldCenterX - m_ScreenWorldWidth / 2;
    m_ScreenWorldRight = m_ScreenWorldCenterX + m_ScreenWorldWidth / 2;
    if (m_ScreenCameraControl.Update())
    {
        m_ScreenW = m_ScreenWorldWidth;
        m_ScreenX = m_ScreenWorldCenterX;
        m_ScreenY = m_ScreenWorldCenterY;
    }
    else
    {
        controlFlag = (GetScreenCameraControl()->m_Flag & 2) == 0;
        m_ScreenW = (int)(GetScreenCameraControl()->m_Param.Z * 1280.f);
        m_ScreenX = (int)(m_LinkMagnRecip * GetScreenCameraControl()->m_Param.X) + shakeX;
        m_ScreenY = (int)(m_LinkMagnRecip * (GetScreenCameraControl()->m_Param.Y - GetScreenCameraControl()->m_Param.Z *
            135.f)) + shakeY;
    }

    if (m_Flag & 0x10)
    {
        controlFlag = true;
        auto cam = AASystemRED::GetInstance()->GetCameraManager().Get(0);
        m_ScreenW = (int)(cam->GetPosZ() * 2.7826087f);
        m_ScreenX = (int)(cam->GetPosX() * m_LinkMagnRecip);
        m_ScreenY = (int)(cam->GetPosY() - (float)m_ScreenW * 0.10546875f * m_LinkMagnRecip);
    }

    if (m_ScreenW <= 0) m_ScreenW = 1;

    if (controlFlag)
    {
        if (m_ScreenX - GetScreenW() / 2 < m_WorldLeftSide)
        {
            m_ScreenX = GetScreenW() / 2 + m_WorldLeftSide;
        }
        if (m_ScreenX + GetScreenW() / 2 > m_WorldRightSide)
        {
            m_ScreenX = m_WorldRightSide - GetScreenW() / 2;
        }
    }

    auto objectScalePre = m_ObjectScale;
    if (m_ScreenY >= m_WorldTopSide - 900) m_ScreenY = m_WorldTopSide - 900;

    m_MoveX = screenXPre - m_ScreenX;
    m_MoveY = screenYPre - m_ScreenY;
    m_ScreenXLeft -= m_ScreenW / 2;
    m_ObjectScale = (uint32_t)(1280000.f / (float)m_ScreenW);
    m_ZoomMoveY = (float)screenWPre * 0.10546875f - (float)m_ScreenW * 0.10546875f;
    m_ScreenYUp = (int)(135000.f / (float)m_ObjectScale * m_LinkMagnRecip + 368000.0 / (float)m_ObjectScale +
        m_ScreenY);

    m_Stable = bQuick || (!m_MoveX && !m_MoveY && screenWPre == m_ScreenW && (m_TargetObjectNum != 1 || m_ObjectScale ==
        1000) && objectScalePre == m_ObjectScale && !m_VelWidth && m_LastFlag == flagPre);

    LinkCameraMove();

    m_LastFlag = m_Flag;
    return true;
}

BATTLE_ScreenCameraControl::BATTLE_ScreenCameraControl()
{
    m_Target.Set(0, 0, 1);
    m_Param.Set(0, 0, 1);
    m_Vel.Set(0, 0, 0);
    m_Hold = true;
    m_Repeat = true;
    m_FixX = true;
    m_FixY = true;
    m_FixZ = true;
    m_Level = 1;
    m_Friction = 1;
    m_Flag = 0;
}

bool BATTLE_ScreenCameraControl::Update()
{
    const auto screenManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
        GetBattleScreenManager();

    float velX, velY;
    auto velZ = (float)screenManager->GetScreenW() * 0.00078125f;

    if (!m_Hold)
    {
        velX = (float)screenManager->GetScreenCenterX() * screenManager->GetLinkMagn();
        velY = (float)screenManager->GetScreenCenterY() * screenManager->GetLinkMagn();
    }
    else
    {
        velX = m_Target.X;
        velY = m_Target.Y;
        velZ = m_Target.Z;
    }

    auto paramX = m_Param.X;
    auto paramY = m_Param.Y;
    auto paramZ = m_Param.Z;

    uint32_t level = m_Level;
    if (!m_Hold)
    {
        level = 31;
    }

    m_Vel.X += (velX - m_Param.X) * (1.0f / (float)level);
    m_Vel.Y += (velY - m_Param.Y) * (1.0f / (float)level);
    m_Vel.Z += (velZ - m_Param.Z) * (1.0f / (float)level);

    m_Param.X += m_Vel.X;
    m_Param.Y += m_Vel.Y;
    m_Param.Z += m_Vel.Z;

    m_Vel.X *= 0.75f;
    m_Vel.Y *= 0.75f;
    m_Vel.Z *= 0.75f;

    if (velX > paramX)
    {
        if (velX < m_Param.X)
        {
            m_Param.X = velX;
            m_Vel.X = 0;
            goto Y_VEL;
        }
    }
    if (velX < paramX && velX >= m_Param.X || m_FixX)
    {
        m_Param.X = velX;
        m_Vel.X = 0;
    }

Y_VEL:
    if (velY > paramY)
    {
        if (velY < m_Param.Y)
        {
            m_Param.Y = velY;
            m_Vel.Y = 0;
            goto Z_VEL;
        }
    }
    if (velY < paramY && velY >= m_Param.Y || m_FixY)
    {
        m_Param.Y = velY;
        m_Vel.Y = 0;
    }

Z_VEL:
    if (velZ > paramZ)
    {
        if (velZ < m_Param.Z)
        {
            m_Param.Z = velZ;
            m_Vel.Z = 0;
            goto VEL_END;
        }
    }
    if (velZ < paramZ && velZ >= m_Param.Z || m_FixZ)
    {
        m_Param.Z = velZ;
        m_Vel.Z = 0;
    }

VEL_END:

    if (!m_Hold)
    {
        if (velX == m_Param.X) m_FixX = true;
        if (velY == m_Param.Y) m_FixY = true;
        if (velZ == m_Param.Z) m_FixZ = true;
    }

    if (!m_Repeat) m_Hold = false;

    return m_FixX && m_FixY && m_FixZ;
}

BATTLE_CScreenManager::OBJ_BOX::OBJ_BOX()
{
    left = 0;
    top = 0;
    right = 0;
    bottom = 0;
    higherBottom = 0;
}
