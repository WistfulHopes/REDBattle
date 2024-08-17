#pragma once
#include "sys_Math.h"

class AA_CCamera
{
protected:
	AA_Matrix m_ViewMatrix {}; // 0x10
	AA_Matrix m_ProjMatrix {}; // 0x50
	AA_Matrix m_ViewProjMatrix {}; // 0x90
	AA_Matrix m_InvViewProjMatrix {}; // 0xD0
	AA_Vector4 m_FOVLeftPlane {}; // 0x110
	AA_Vector4 m_FOVRightPlane {}; // 0x120
	AA_Vector4 m_FOVTopPlane {}; // 0x130
	AA_Vector4 m_FOVBottomPlane {}; // 0x140
	AA_Matrix m_ViewProjMatrixFinal {}; // 0x150
	AA_Vector3 m_Pos {}; // 0x190
	AA_Vector3 m_Up {}; // 0x19C
	AA_Vector3 m_At {}; // 0x1A8
	AA_Vector3 m_BasePos {}; // 0x1B4
	AA_Vector3 m_BaseUp {}; // 0x1C0
	AA_Vector3 m_BaseAt {}; // 0x1CC
	float m_FOV {}; // 0x1D8
	float m_FrontClip {}; // 0x1DC
	float m_BackClip {}; // 0x1E0
	float m_AspectRatio {}; // 0x1E4
	void PlaneFromPoint(AA_Vector3 *pP0, AA_Vector3 *pP1, AA_Vector3 *pP2, AA_Vector4 *pPlane);
public:
	AA_CCamera();
	~AA_CCamera() {}
	bool Update();
	void InitPos(float x, float y, float z);
	void InitPosAt(float, float, float, float, float, float);
	void InitPosDir(float, float, float, float, float, float);
	void SetBasePos(float x, float y, float z) { m_BasePos.Set(x, y, z); }
	void SetBaseLookAt(float x, float y, float z) { m_BaseAt.Set(x, y, z); }
	void SetBaseUp(float, float, float);
	void ResetPos() { m_Pos = m_BasePos; }
	void ResetLookAt() { m_At = m_BaseAt; }
	void ResetUp() { m_Up = m_BaseUp; }
	void SetPos(float x, float y, float z) { m_Pos.Set(x, y, z); }
	void SetLookAt(float x, float y, float z) { m_At.Set(x, y, z); }
	void SetUp(float, float, float);
	void SetDir(float, float, float);
	void SetFOV(float fov) { m_FOV = fov; }
	void SetFrontClip(float frontClip) { m_FrontClip = frontClip; }
	void SetBackClip(float backClip) { m_BackClip = backClip; }
	void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
	void CreateVec3Dir(AA_Vector3 *);
	void CreateFOVPlane();
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	float GetUpX();
	float GetUpY();
	float GetUpZ();
	float GetLookAtX();
	float GetLookAtY();
	float GetLookAtZ();
	float GetAspectRatio();
	float GetFOV() { return m_FOV; }
	float GetFrontClip();
	float GetBackClip();
	const AA_Vector3 & GetPos() { return m_Pos; }
	const AA_Vector3 & GetUp() { return m_Up; }
	const AA_Vector3 & GetLookAt() { return m_At; }
	const AA_Matrix & GetViewMatrix() { return m_ViewMatrix; }
	const AA_Matrix & GetProjMatrix()  { return m_ProjMatrix; }
	const AA_Matrix & GetViewProjMatrix() { return m_ViewProjMatrix; }
	const AA_Matrix & GetViewProjMatrixFinal();
	void SetViewProjMatrixFinal(const AA_Matrix &);
	const AA_Matrix & GetInvViewProjMatrix();
	const AA_Vector4 & GetFOVLeftPlane();
	const AA_Vector4 & GetFOVRightPlane();
	const AA_Vector4 & GetFOVTopPlane();
	const AA_Vector4 & GetFOVBottomPlane();
	struct FRollbackData;
	void MakeRollbackData(FRollbackData&);
	void ApplyRollbackData(const FRollbackData&);
	AA_CCamera & operator=(const AA_CCamera &);
};
struct AA_CCamera::FRollbackData
{
	AA_Vector3 m_Pos {}; // 0x0
	AA_Vector3 m_Up {}; // 0xC
	AA_Vector3 m_At {}; // 0x18
	FRollbackData();
	FRollbackData& operator=(FRollbackData&);
	FRollbackData& operator=(const FRollbackData&);
};