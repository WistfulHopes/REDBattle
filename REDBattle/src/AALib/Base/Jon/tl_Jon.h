#pragma once
#include "AALib/Base/sys_Collision.h"
#include <cstdint>
#include "JonStruct.h"

class AA_CCollision_JON : public AA_CCollision
{
public:
	static const int32_t COLLISION_IMAGE_MAX {}; // 0xFFFFFFFFFFFFFFFF
private:
	sJonElmView * m_ViewAddr {}; // 0x10
	sJonElmCollision * m_CollisionAddr[18] {}; // 0x18
	int32_t m_ViewNum {}; // 0xA8
	int32_t m_CollisionNum[18] {}; // 0xAC
	char * m_ImageFileName[8] {}; // 0xF8
	int32_t m_ImageFileNum {}; // 0x138
public:
	AA_CCollision_JON();
	bool AnalyzeCollisionFile(const void * col);
	uint32_t GetImageFileNum() { return m_ImageFileNum; }
	const char * GetImageFileName(int32_t idx) { return m_ImageFileName[idx]; }
	const wchar_t * GetAnimeName();
	int32_t GetAnimeFrame();
	CCmnRect GetViewTextureRect(int32_t idx) { return m_ViewAddr[idx].m_TextureRect; }
	CCmnRect GetViewWorldRect(int32_t idx)  { return m_ViewAddr[idx].m_WorldRect; }
};