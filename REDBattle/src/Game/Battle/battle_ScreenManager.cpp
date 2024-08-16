#include "battle_ScreenManager.h"

#include <AALib/AASystemRED.h>

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

float CalcBattleCameraLinkMagn(AA_CCamera * cam, AA_Vector3 & pos0, AA_Vector3 & pos1)
{
    auto BaseMatrix = AA_Matrix::CreateIdentity().Mult(cam->GetViewMatrix());
    BaseMatrix = BaseMatrix.Mult(cam->GetProjMatrix());
    auto vecPos0 = AA_Vector4(pos0, 1);
    vecPos0 = BaseMatrix.TransformFVector4(vecPos0);
    vecPos0 /= BaseMatrix.M[3][3];
    auto vecPos1 = AA_Vector4(pos1, 1);
    vecPos1 = BaseMatrix.TransformFVector4(vecPos1);
    vecPos1 /= BaseMatrix.M[3][3];

    auto ScreenMatrix = AA_Matrix::CreateIdentity();
    ScreenMatrix.Set(0, 0, 640);
    ScreenMatrix.Set(0, 3, 640);

    auto sx = ScreenMatrix.TransformFVector4(vecPos0).GetX();
    auto sy = ScreenMatrix.TransformFVector4(vecPos1).GetY();

    return 1.f / sqrtf(sx * sx + sy * sy) * (pos0 - pos1).Size();
}

void BATTLE_CScreenManager::ResetScreenManager()
{
    m_pCamera = AASystemRED::GetInstance()->GetCameraManager().Get(0);
    if (m_pCamera)
    {
        m_pCamera->SetFOV(1.134464f);
        m_pCamera->SetBackClip(-50000);
        m_pCamera->SetBasePos(0, 135, 460);
        m_pCamera->SetPos(0, 135, 460);
        m_pCamera->SetBaseLookAt(0, 135, 0);
        m_pCamera->SetLookAt(0, 135, 0);
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

BATTLE_CScreenManager::OBJ_BOX::OBJ_BOX()
{
    left = 0;
    top = 0;
    right = 0;
    bottom = 0;
    higherBottom = 0;
}