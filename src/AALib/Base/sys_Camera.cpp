#include "sys_Camera.h"
#include <cmath>

void AA_CCamera::PlaneFromPoint(AA_Vector3* pP0, AA_Vector3* pP1, AA_Vector3* pP2, AA_Vector4* pPlane)
{
    auto v0 = (*pP2 - *pP0) ^ (*pP1 - *pP0);
    auto v1 = v0.GetSafeNormal();
    pPlane->SetX(v1.GetX());
    pPlane->SetY(v1.GetY());
    pPlane->SetZ(v1.GetZ());
    pPlane->SetW(-(*pP0 | v1));
}

AA_CCamera::AA_CCamera()
{
    m_FOVLeftPlane.Set(0, 0, 0, 1);
    m_FOVRightPlane.Set(0, 0, 0, 1);
    m_FOVTopPlane.Set(0, 0, 0, 1);
    m_FOVBottomPlane.Set(0, 0, 0, 1);
    m_BasePos.Set(0, 0, 0);
    m_Pos.Set(0, 0, 0);
    m_BaseAt.Set(0, 0, 1);
    m_At.Set(0, 0, 1);
    m_BaseUp.Set(0, 1, 0);
    m_Up.Set(0, 1, 0);
    m_FOV = 1.5707964f;
    m_FrontClip = 3;
    m_BackClip = 5000;
    m_AspectRatio = 16.f / 9.f;
}

bool AA_CCamera::Update()
{
    auto halfFOV = m_FOV * 0.5f;

    m_ViewMatrix = AA_Matrix(m_Pos, m_At, m_Up);
    m_ProjMatrix = AA_Matrix(halfFOV, halfFOV, 1, 1, m_FrontClip, m_BackClip);
    m_ViewProjMatrix = m_ViewMatrix.Mult(m_ProjMatrix);
    m_InvViewProjMatrix = m_ViewProjMatrix.Inverse();
    CreateFOVPlane();

    return true;
}

void AA_CCamera::CreateFOVPlane()
{
    auto tangent = tanf(m_FOV * 0.5f);
    auto p0 = AA_Vector3(0, 0, 0);
    auto p1 = AA_Vector3(-(tangent * m_BackClip * m_AspectRatio), -m_BackClip * tangent, m_BackClip);
    auto p2 = AA_Vector3(-(tangent * m_BackClip * m_AspectRatio), m_BackClip * tangent, m_BackClip);
    PlaneFromPoint(&p0, &p1, &p2, &m_FOVLeftPlane);

    p1 = AA_Vector3((tangent * m_BackClip * m_AspectRatio), m_BackClip * tangent, m_BackClip);
    p2 = AA_Vector3((tangent * m_BackClip * m_AspectRatio), -m_BackClip * tangent, m_BackClip);
    PlaneFromPoint(&p0, &p1, &p2, &m_FOVRightPlane);

    p1 = AA_Vector3(-(tangent * m_BackClip * m_AspectRatio), m_BackClip * tangent, m_BackClip);
    p2 = AA_Vector3((tangent * m_BackClip * m_AspectRatio), m_BackClip * tangent, m_BackClip);
    PlaneFromPoint(&p0, &p1, &p2, &m_FOVTopPlane);

    p1 = AA_Vector3((tangent * m_BackClip * m_AspectRatio), -m_BackClip * tangent, m_BackClip);
    p2 = AA_Vector3(-(tangent * m_BackClip * m_AspectRatio), m_BackClip * tangent, m_BackClip);
    PlaneFromPoint(&p0, &p1, &p2, &m_FOVBottomPlane);
}