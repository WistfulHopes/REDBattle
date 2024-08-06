#pragma once
#include <cstdint>

enum FPACK_STYLE
{
	FPACST_NORMAL = 0x0,
	FPACST_AUTOLEN_FILENAME = 0x1,
	FPACST_ID_ONLY = 0x2,
	FPACST_PATHCUT = 0x10,
	FPACST_LONGNAME = 0x20000000,
	FPACST_HASHSORT = 0x40000000,
	FPACST_VERSION2 = 0x80000000,
};
struct FILEPACK_HEADER
{
	uint32_t packID; // 0x0
	uint32_t sizeHeader; // 0x4
	uint32_t sizeFile; // 0x8
	uint32_t numFile; // 0xC
	uint32_t stylePack; // 0x10
	uint32_t maxlenName; // 0x14
	uint32_t reserve1; // 0x18
	uint32_t reserve2; // 0x1C
};
struct FILEPACK_FILEOFFADDR
{
	uint32_t idFile; // 0x0
	uint32_t offsetAddr; // 0x4
	uint32_t offsetFileSize; // 0x8
};
struct FILEPACK_FILEOFFADDR_VER2
{
	char nameFile[32]; // 0x0
	uint32_t idFile; // 0x20
	uint32_t offsetAddr; // 0x24
	uint32_t offsetFileSize; // 0x28
	uint32_t hash; // 0x2C
};
struct FILEPACK_FILEOFFADDR_VER2_LONGNAME
{
	char nameFile[64]; // 0x0
	uint32_t idFile; // 0x40
	uint32_t offsetAddr; // 0x44
	uint32_t offsetFileSize; // 0x48
	uint32_t hash; // 0x4C
};
struct FILEPACK_FILEOFFADDR_VER2_NONAME
{
	uint32_t idFile; // 0x0
	uint32_t offsetAddr; // 0x4
	uint32_t offsetFileSize; // 0x8
	uint32_t hash; // 0xC
};