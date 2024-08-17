#pragma once
#include <cstdint>
#include "AALib/Base/sys_Math.h"
#include "Object/obj_Base.h"
#include "AALib/Common/cmn_class.h"
#include "AALib/Base/sys_Camera.h"

enum BTL_SCREENFLAG
{
	BTL_SCREENFLAG_NON = 0,
	BTL_SCREENFLAG_SCRLOCK = 1,
	BTL_SCREENFLAG_SCRLOCKW = 2,
	BTL_SCREENFLAG_SCRLOCKX = 4,
	BTL_SCREENFLAG_SCRLOCKY = 8,
	BTL_SCREENFLAG_POSCAMLINK = 16,
	BTL_SCREENFLAG_SHAKESTART = 256,
	BTL_SCREENFLAG_SHAKING = 512,
	BTL_SCREENFLAG_SHAKEEND = 1024,
	BTL_SCREENFLAG_SCREEN_SIDE_OFF = 2048,
	BTL_SCREENFLAG_WORLD_SIDE_EXPAND = 4096,
	BTL_SCREENFLAG_SCREEN_SIDE_FORCEON = 65536,
	BTL_SCREENFLAG_ROUNDWINSETTING = 2048,
};
enum BTL_SCREEN_TARGET_FLAG
{
	BTL_SCREEN_TARGET_FLAG_NONE = 0,
	BTL_SCREEN_TARGET_FLAG_SUBCHARA = 1,
};
enum BTL_SCRCTR_FLAG
{
	BTL_SCRCAMCTR_FLAG_NON = 0,
	BTL_SCRCAMCTR_FLAG_NO_CEILING = 1,
	BTL_SCRCAMCTR_FLAG_NO_WALL = 2,
};
class BATTLE_ScreenCameraControl
{
public:
	AA_Vector3 m_Target; // 0x0
	AA_Vector3 m_Param; // 0xC
	AA_Vector3 m_Vel; // 0x18
	bool m_Hold; // 0x24
	bool m_Repeat; // 0x25
	bool m_FixX; // 0x26
	bool m_FixY; // 0x27
	bool m_FixZ; // 0x28
	uint32_t m_Level; // 0x2C
	float m_Friction; // 0x30
	uint32_t m_Flag; // 0x34
	BATTLE_ScreenCameraControl();
	~BATTLE_ScreenCameraControl() {}
	void Reset();
	bool Update();
	BATTLE_ScreenCameraControl & operator=(const BATTLE_ScreenCameraControl &);
};
class BATTLE_CScreenManager
{
private:
	OBJ_CBase * m_ppObject[6] {}; // 0x0
	uint32_t m_TargetObjectFlag[6]; // 0x30
	uint32_t m_TargetObjectNum; // 0x48
	AA_CCamera * m_pCamera; // 0x50
	int32_t m_ObjLeft; // 0x58
	int32_t m_ObjRight; // 0x5C
	int32_t m_ObjTop; // 0x60
	int32_t m_ObjBottom; // 0x64
	int32_t m_ObjLenX; // 0x68
	int32_t m_ObjLenY; // 0x6C
	int32_t m_ZoomOutBeginDistX; // 0x70
	int32_t m_ZoomOutBeginDistY; // 0x74
	int32_t m_MaxZoomOutWidth; // 0x78
	int32_t m_TargetOffsetY; // 0x7C
	int32_t m_TargetOffsetAirYMax; // 0x80
	int32_t m_TargetOffsetAirYAdd; // 0x84
	int32_t m_TargetOffsetAirYPos; // 0x88
	int32_t m_TargetOffsetAirYDist; // 0x8C
	int32_t m_WidthY; // 0x90
	int32_t m_TargetOffsetLandYMax; // 0x94
	int32_t m_TargetOffsetLandYAdd; // 0x98
	int32_t m_ScreenWorldLeft; // 0x9C
	int32_t m_ScreenWorldRight; // 0xA0
	int32_t m_ScreenWorldCenterX; // 0xA4
	int32_t m_ScreenWorldCenterY; // 0xA8
	int32_t m_ScreenWorldWidth; // 0xAC
	int32_t m_TargetCenterX; // 0xB0
	int32_t m_TargetCenterY; // 0xB4
	int32_t m_TargetWidth; // 0xB8
	int32_t m_VelCenterX; // 0xBC
	int32_t m_VelCenterY; // 0xC0
	int32_t m_VelWidth; // 0xC4
	int32_t m_SetPosX; // 0xC8
	int32_t m_SetPosY; // 0xCC
	int32_t m_SetPosW; // 0xD0
	int32_t m_DelayW; // 0xD4
	uint32_t m_ObjectScale; // 0xD8
	int32_t m_ScreenX; // 0xDC
	int32_t m_ScreenY; // 0xE0
	int32_t m_ScreenW; // 0xE4
	int32_t m_ScreenXLeft; // 0xE8
	int32_t m_ScreenYUp; // 0xEC
	int32_t m_MoveX; // 0xF0
	int32_t m_MoveY; // 0xF4
	float m_ZoomMoveY; // 0xF8
	AA_Handle m_hLinkCamera; // 0xFC
	float m_LinkMagn; // 0x100
	float m_LinkMagnRecip; // 0x104
	uint32_t m_Flag; // 0x108
	uint32_t m_LastFlag; // 0x10C
	float m_ShakeX; // 0x110
	float m_ShakeY; // 0x114
	int32_t m_ShakeTime; // 0x118
	int32_t m_ScreenCollisionLeft; // 0x11C
	int32_t m_ScreenCollisionRight; // 0x120
	int32_t m_ScreenCollisionYUp; // 0x124
	int32_t m_ScreenCenterXNoShake; // 0x128
	int32_t m_ScreenCenterYNoShake; // 0x12C
	int32_t m_WorldLeftSide; // 0x130
	int32_t m_WorldRightSide; // 0x134
	int32_t m_WorldTopSide; // 0x138
	BATTLE_ScreenCameraControl m_ScreenCameraControl; // 0x13C
	uint32_t m_FilterControl; // 0x174
	bool m_Stable; // 0x178
	bool m_bStopScreenPositionUpdate; // 0x179
	bool m_bStopZoomCamera; // 0x17A
	bool m_bTouchWorldSide; // 0x17B
	int32_t m_WorldSideMoveValue; // 0x17C
	int32_t m_WorldSideMoveValuePrev; // 0x180
	int32_t m_WorldSideMoveDir; // 0x184
	int32_t m_WorldSideMoveResetDir; // 0x188
	float m_WorldSideMoveDeg; // 0x18C
	AA_Matrix m_OffsetMatrix; // 0x190
	AA_Matrix m_PrevCameraMatrix; // 0x1D0
    struct OBJ_BOX
    {
        int32_t left; // 0x0
        int32_t top; // 0x4
        int32_t right; // 0x8
        int32_t bottom; // 0xC
        int32_t higherBottom; // 0x10
        OBJ_BOX();
        int32_t Left() { return left; }
        int32_t Right() { return right; }
        int32_t Top() { return top; }
        int32_t Bottom() { return bottom; }
        int32_t HigherBottom() { return higherBottom; }
        int32_t Width();
        int32_t Height();
        int32_t CenterX();
        int32_t CenterY();
        int32_t StandDistY();
        void Initialize();
    };
	OBJ_BOX m_ObjBox; // 0x210
	const OBJ_BOX * ObjBox() { return &m_ObjBox; }
	void ResetWorldSide();
	void SetWorldSideScale(int32_t, int32_t);
	void SetWorldSide(int32_t, int32_t, int32_t);
	void ResetZoomParam();
	void SetZoomParam(int32_t, int32_t, int32_t);
	void SetZoomParamScale(int32_t, int32_t, int32_t);
	bool LinkCameraMove();
public:
	BATTLE_CScreenManager();
	~BATTLE_CScreenManager() {}
	void ResetScreenManager();
	void ResetOnRoundReset(unsigned char);
	void ResetToCenter(int32_t, int32_t);
	bool AddScreenTarget(OBJ_CBase *, uint32_t);
	bool ResetScreenTarget();
	void SetScreenCornerObject(bool);
	bool SetLinkCameraMagn(AA_Vector3 &, AA_Vector3 &);
	bool SetLinkCamera(const AA_Handle *);
	bool IsScreenStable();
	bool UpdateScreenPosition(bool);
	void ResetScreenPos(int32_t, int32_t, int32_t);
	int32_t GetObjectScale();
	int32_t GetScreenX();
	int32_t GetScreenY();
	int32_t GetScreenW();
	int32_t GetCameraPosX();
	int32_t GetCameraPosY();
	int32_t GetCameraPosW();
	int32_t GetScreenXLeft();
	int32_t GetScreenYUp();
	int32_t GetScreenLeftSide();
	int32_t GetScreenRightSide();
	int32_t GetWorldLeftSide();
	int32_t GetWorldRightSide();
	int32_t GetWorldTopSide();
	int32_t GetCollLeftSide();
	int32_t GetCollRightSide();
	int32_t GetCollYUp();
	int32_t GetScreenCenterX();
	int32_t GetScreenCenterY();
	void SetTargetX(int32_t);
	void SetTargetY(int32_t);
	void SetTargetW(int32_t);
	void SetScreenX(int32_t);
	void SetPosX(int32_t);
	void SetPosY(int32_t);
	void SetPosW(int32_t);
	void ResetCamera();
	AA_Handle & GetLinkCamera();
	float GetLinkMagn() { return m_LinkMagn; }
	float GetLinkMagnRecip() { return m_LinkMagnRecip; }
	AA_CCamera * GetLinkCameraInstance() { return m_pCamera; }
	void ResetFlag();
	void AddFlag(uint32_t);
	void DelFlag(uint32_t);
	void SetFlag(uint32_t);
	bool CheckFlag(uint32_t);
	uint32_t GetFlag();
	bool RequestShake(float, float);
	BATTLE_ScreenCameraControl * GetScreenCameraControl() { return &m_ScreenCameraControl; }
	void StopScreenPositionUpdate(bool stop) { m_bStopScreenPositionUpdate = stop; } 
	void StopZoomCamera(bool);
	void ResetWorldSideMove(unsigned char);
	int32_t GetWorldSideCountMax();
	void AddWorldSideMove(int32_t);
	int32_t GetWorldSideMove() { return m_WorldSideMoveValue; }
	int32_t GetWorldSideMoveDir();
	int32_t GetWorldSideMoveResetDir();
	int32_t GetWorldSideMoveValue() { return 1600; }
	int32_t GetWorldSideMove_ObjOffsetX();
	const AA_Matrix & GetOffsetMatrix();
	AA_Vector3 ApplyOffsetMatrix(AA_Vector3 *, AA_Rotator *);
	void CalcBaseLocAndRot(AA_Vector3 *, AA_Rotator *);
	void SetPrevFrameCameraMatrix(const AA_Matrix &);
	const AA_Matrix & GetPrevFrameCameraMatrix();
	void ResetWorldSideMoveOrigin();
	void DebugDisp();
	BATTLE_CScreenManager & operator=(const BATTLE_CScreenManager &);
};