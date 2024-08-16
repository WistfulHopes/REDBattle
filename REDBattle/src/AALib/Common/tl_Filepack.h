#pragma once
#include <cstdint>

class AA_Filepack_FPAC
{
private:
	void * m_pData {}; // 0x0
public:
	uint32_t SearchFileIDFromHash(uint32_t namehash);
	AA_Filepack_FPAC();
	void SetPackFile(void* data) { m_pData = data; }
	void* GetPackFile() { return m_pData; }
	void * GetPackOffsetAddr(uint32_t num);
	uint32_t GetPackOffsetFileSize(uint32_t num);
	const char * GetPackFileNum2FileName(uint32_t num);
	const char * GetFileNameTableTopPtr();
	uint32_t SearchFileID(const char * pFileName);
private:
	uint32_t MakeHash(const char * s);
};