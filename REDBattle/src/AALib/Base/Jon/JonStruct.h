#pragma once
#include "JonCommon.h"
#include "AALib/Common/cmn_typedef.h"

class sJonElmGlobalAttribute
{
public:
	sJonElmGlobalAttribute();
	_ZTYPE m_ZType; // 0x0
	float m_OfsZ; // 0x4
	float m_Alpha01; // 0x8
	_TRANSTYPE m_TransType; // 0xC
	float m_RadZ; // 0x10
	float m_AngleCenterOfsX; // 0x14
	float m_AngleCenterOfsY; // 0x18
	float m_ScaleX; // 0x1C
	float m_ScaleY; // 0x20
	uint32_t m_Rsv[4]; // 0x24
};
class sJonElmView
{
public:
	sJonElmView();
	CCmnRect m_TextureRect; // 0x0
	CCmnRect m_WorldRect; // 0x10
	_ZTYPE m_ZType; // 0x20
	float m_OfsZ; // 0x24
	float m_Alpha01; // 0x28
	_TRANSTYPE m_TransType; // 0x2C
	float m_RadZ; // 0x30
	float m_AngleCenterOfsX; // 0x34
	float m_AngleCenterOfsY; // 0x38
	uint32_t m_ImageIndex; // 0x3C
	uint32_t m_Usage; // 0x40
	uint32_t m_AfterImage; // 0x44
	uint32_t m_Palette; // 0x48
	uint32_t m_Rsv; // 0x4C
};
class sJonElmLayer
{
public:
	sJonElmLayer();
	CCmnRect m_WorldRect; // 0x0
	_ZTYPE m_ZType; // 0x10
	float m_OfsZ; // 0x14
	float m_Alpha01; // 0x18
	_TRANSTYPE m_TransType; // 0x1C
	float m_RadZ; // 0x20
	float m_AngleCenterOfsX; // 0x24
	float m_AngleCenterOfsY; // 0x28
	float m_ScaleX; // 0x2C
	float m_ScaleY; // 0x30
	char m_LayerFileName[256]; // 0x34
};
class sJonElmCollision
{
public:
	sJonElmCollision();
	uint32_t m_CollisionType; // 0x0
	CCmnRect m_WorldRect; // 0x4
};