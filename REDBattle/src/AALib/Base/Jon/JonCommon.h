#pragma once
#include <cstdint>

enum _JONELMTYPE
{
	JONELMTYPE_GLOBAL_ATTRIBUTE = 0,
	JONELMTYPE_VIEW = 1,
	JONELMTYPE_LAYER = 2,
	JONELMTYPE_COLLISION = 3,
	JONELMTYPE_NUM = 4,
};
enum _ZTYPE
{
	ZTYPE_DEFAULT = 0,
	ZTYPE_MOST_FAR = 1,
	ZTYPE_FAR = 2,
	ZTYPE_LITTLE_FAR = 3,
	ZTYPE_LITTLE_NEAR = 4,
	ZTYPE_NEAR = 5,
	ZTYPE_MOST_NEAR = 6,
	ZTYPE_NUM = 7,
};
struct _sZType
{
	const char * m_ZTypeName; // 0x0
	float m_ZTypeZOfs; // 0x8
	const char * m_ZTypeDispName; // 0x10
};
enum _TRANSTYPE
{
	TTYPE_DEFAULT = 0,
	TTYPE_NORMAL = 1,
	TTYPE_ADD = 2,
	TTYPE_DEC = 3,
	TTYPE_REVERSE = 4,
	TTYPE_NUM = 5,
};
struct _sTransType
{
	const char * m_TransTypeName; // 0x0
	const char * m_TransTypeDispName; // 0x8
};
enum _CTYPE
{
	CTYPE_DAMAGE = 0,
	CTYPE_ATTACK = 1,
	CTYPE_EXPOINT = 2,
	CTYPE_EXRECT = 3,
	CTYPE_EXVECTOR = 4,
	CTYPE_PUSH = 5,
	CTYPE_TEMP_CENTER = 6,
	CTYPE_NECK = 7,
	CTYPE_ABDOMINAL = 8,
	CTYPE_ATTACK_VS_PUSH = 9,
	CTYPE_SP_GUARD = 10,
	CTYPE_R_LEG = 11,
	CTYPE_L_LEG = 12,
	CTYPE_PRIVATE_POINT_0 = 13,
	CTYPE_PRIVATE_POINT_1 = 14,
	CTYPE_PRIVATE_POINT_2 = 15,
	CTYPE_PRIVATE_POINT_3 = 16,
	CTYPE_EXTEND_JON = 17,
	CTYPE_NUM = 18,
};
enum _COLSHAPE
{
	CS_RECT = 0,
	CS_POINT = 1,
	CS_VECTOR = 2,
	CS_NUM = 3,
};
struct _sCollisionType
{
	const char * m_CollisionName; // 0x0
	_COLSHAPE m_Shape; // 0x8
	uint32_t m_Color; // 0xC
	const char * m_CollisionDispName; // 0x10
};
class string256
{
public:
	char m_Buffer[256]; // 0x0
};