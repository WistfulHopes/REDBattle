#pragma once
#include "Object/Char/char_Base.h"
#include "Object/obj_AttackParam.h"
#include "Object/obj_Flag.h"

enum BATTLE_RECORD_TYPE
{
	BTLREC_LIGHT_ATTACK = 0,
	BTLREC_MIDDLE_ATTACK = 1,
	BTLREC_HEAVY_ATTACK = 2,
	BTLREC_CHUDAN_ATTACK = 3,
	BTLREC_SPECIAL_ATTACK = 4,
	BTLREC_EXSPECIAL_ATTACK = 5,
	BTLREC_ULTIMATE_ATTACK = 6,
	BTLREC_METEOULTIMATE_ATTACK = 7,
	BTLREC_SPECIAL = 8,
	BTLREC_EXSPECIAL = 9,
	BTLREC_ULTIMATE = 10,
	BTLREC_METEOULTIMATE = 11,
	BTLREC_GUARDCANCEL_ATTACK = 12,
	BTLREC_SHOT = 13,
	BTLREC_SOUSAI = 14,
	BTLREC_SHOT_SOUSAI = 15,
	BTLREC_HOMINGDASH_ATTACK = 16,
	BTLREC_HOMINGDASH = 17,
	BTLREC_MIKIWAMEMOVE_ATTACK = 18,
	BTLREC_MIKIWAMEMOVE = 19,
	BTLREC_SHOTREFLECT = 20,
	BTLREC_ZREVERSE = 21,
	BTLREC_RUSHSTART = 22,
	BTLREC_RUSHRUSH = 23,
	BTLREC_RUSHCHANGE = 24,
	BTLREC_RUSHSOUSAI = 25,
	BTLREC_RUSHDAMAGE = 26,
	BTLREC_BURST = 27,
	BTLREC_SPARKING_BURST = 28,
	BTLREC_ASSIST = 29,
	BTLREC_CHANGE = 30,
	BTLREC_GUARDCANCEL_CHANGE = 31,
	BTLREC_ULTIMATE_CHANGE = 32,
	BTLREC_FIRSTATTACK = 33,
	BTLREC_COUNTER = 34,
	BTLREC_COUNTER_DAMAGE = 35,
	BTLREC_GUARD = 36,
	BTLREC_CHUDAN_GUARD = 37,
	BTLREC_GEDAN_GUARD = 38,
	BTLREC_SHENLONG = 39,
	BTLREC_DOWN = 40,
	BTLREC_ENEMY_DOWN = 41,
	BTLREC_SPECIALATK_FINISH = 42,
	BTLREC_EXSPECIALATK_FINISH = 43,
	BTLREC_ULTIMATE_FINISH = 44,
	BTLREC_METEOULTIMATE_FINISH = 45,
	BTLREC_FUTTOBI_FINISH = 46,
	BTLREC_DESTRUCTION_FINISH = 47,
	BTLREC_DRAMATIC_FINISH = 48,
	BTLREC_BG_DESTROY = 49,
	BTLREC_GROUND_DESTROY = 50,
	BTLREC_FRONTWALK = 51,
	BTLREC_INVALID = 52,
};
class CBattleRecord
{
public:
	CBattleRecord(const CBattleRecord &);
	CBattleRecord() {}
	~CBattleRecord() {}
    struct Battle_Record
    {
        unsigned short m_LightAtk; // 0x0
        unsigned short m_MiddleAtk; // 0x2
        unsigned short m_HeavyAtk; // 0x4
        unsigned short m_chudanAtk; // 0x6
        unsigned short m_SpecialAtk; // 0x8
        unsigned short m_ExSpecialAtk; // 0xA
        unsigned short m_UltimateAtk; // 0xC
        unsigned short m_MeteoUltimateAtk; // 0xE
        unsigned short m_Special; // 0x10
        unsigned short m_ExSpecial; // 0x12
        unsigned short m_Ultimate; // 0x14
        unsigned short m_MeteoUltimate; // 0x16
        unsigned short m_GuardCancelAttack; // 0x18
        unsigned short m_Shot; // 0x1A
        unsigned short m_Sousai; // 0x1C
        unsigned short m_ShotSousai; // 0x1E
        unsigned short m_HomingDashAtk; // 0x20
        unsigned short m_HomingDash; // 0x22
        unsigned short m_MikiwameMoveAtk; // 0x24
        unsigned short m_MikiwameMove; // 0x26
        unsigned short m_ShotReflect; // 0x28
        unsigned short m_ZReverse; // 0x2A
        unsigned short m_RushStart; // 0x2C
        unsigned short m_RushRush; // 0x2E
        unsigned short m_RushChange; // 0x30
        unsigned short m_RushSousai; // 0x32
        unsigned short m_RushDamage; // 0x34
        unsigned short m_Burst; // 0x36
        unsigned short m_SparkingBurst; // 0x38
        unsigned short m_Assist; // 0x3A
        unsigned short m_Change; // 0x3C
        unsigned short m_GuardCancelChange; // 0x3E
        unsigned short m_UltimateChange; // 0x40
        unsigned short m_FirstAtk; // 0x42
        unsigned short m_Counter; // 0x44
        unsigned short m_CounterDamage; // 0x46
        unsigned short m_Guard; // 0x48
        unsigned short m_ChudanGuard; // 0x4A
        unsigned short m_GedanGuard; // 0x4C
        unsigned short m_Shenlong; // 0x4E
        unsigned short m_Down; // 0x50
        unsigned short m_EnemyDown; // 0x52
        unsigned short m_SpecialAtkFinish; // 0x54
        unsigned short m_ExSpecialAtkFinish; // 0x56
        unsigned short m_UltimateFinish; // 0x58
        unsigned short m_MeteoUltimateFinish; // 0x5A
        unsigned short m_FuttobiFinish; // 0x5C
        unsigned short m_DestructionFinish; // 0x5E
        unsigned short m_DramaticFinish; // 0x60
        unsigned short m_BGDestroy; // 0x62
        unsigned short m_GroundDestroy; // 0x64
        unsigned short m_FrontWalkFrame; // 0x66
    };
private:
	CBattleRecord::Battle_Record m_Record[2]; // 0x8
	const CSkillInfo * m_pSkill[2]; // 0xD8
	void Initialize();
public:
	void ResetRecord();
	CBattleRecord::Battle_Record * GetRecord(SIDE_ID);
	unsigned short GetRecordVal(SIDE_ID, BATTLE_RECORD_TYPE);
	void SetSkill(SIDE_ID, const CSkillInfo *, bool);
	const CSkillInfo * GetSkill(SIDE_ID);
	void AddRecord(SIDE_ID, BATTLE_RECORD_TYPE, unsigned short);
	void SetRecord(SIDE_ID, BATTLE_RECORD_TYPE, unsigned short);
	BATTLE_RECORD_TYPE GetRecordType(const CAtkParam *, SIDE_ID, HIT_TYPE, GUARD_DAN);
	BATTLE_RECORD_TYPE GetRecordType(SKILL_CATEGORY, AT_Type, int32_t, int32_t, ATKDAN, bool);
	CBattleRecord & operator=(const CBattleRecord &);
};
