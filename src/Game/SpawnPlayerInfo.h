#pragma once
#include <cstdint>
#include "REDGameConstant.h"
#include <vector>
#include <string>

struct IDConvertTable
{
	int32_t SourceID; // 0x0
	int32_t DestID; // 0x4
};

class FSpawnPlayerInfo
{
public:
	SIDE_ID SideID {}; // 0x0
	EMemberID MemberID {}; // 0x4
	std::string CharaID {}; // 0x8
	std::vector<std::string> SelfTeamMemberCharaID {}; // 0x18
	std::vector<std::string> EnemyTeamMemberCharaID {}; // 0x28
	std::vector<std::string> BGLayerNames {}; // 0x38
	int32_t CostumeID {}; // 0x48
	int32_t ColorID {}; // 0x4C
	EBattleScript ScriptType {}; // 0x50
	std::string VoiceLoc {}; // 0x58
	void Initialize(SIDE_ID, EMemberID, std::string &, const std::vector<std::string> &, const std::vector<std::string> &, const std::vector<std::string> &, int32_t, int32_t, EBattleScript, const wchar_t *);
	std::string GetCharaIDForLoadPackage();
	std::string GetCharaID();
	int32_t GetCostumeIDForPathName();
	int32_t GetColorIDForPathName();
	FSpawnPlayerInfo(FSpawnPlayerInfo &);
	FSpawnPlayerInfo(const FSpawnPlayerInfo &);
	FSpawnPlayerInfo();
	void SetCostumeIDConvTable(const IDConvertTable *, const int32_t);
	void SetColorIDConvTable(const IDConvertTable *, const int32_t);
	bool IsValidData();
	bool IsDummyData();
	bool IsCommonData();
private:
	const IDConvertTable * CostumeIDConvTable {}; // 0x70
	const IDConvertTable * ColorIDConvTable {}; // 0x78
	int32_t CostumeIDConvTableNum {}; // 0x80
	int32_t ColorIDConvTableNum {}; // 0x84
	int32_t ConvertCostumeID(int32_t);
	int32_t ConvertColorID(int32_t);
	int32_t ConvertID(int32_t, const IDConvertTable *, const int32_t);
public:
	~FSpawnPlayerInfo() {}
	FSpawnPlayerInfo & operator=(FSpawnPlayerInfo &);
	FSpawnPlayerInfo & operator=(const FSpawnPlayerInfo &);
};