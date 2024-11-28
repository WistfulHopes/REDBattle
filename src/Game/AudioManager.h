#pragma once
#include <cstdint>

struct FREDAudioHandle
{
	int32_t Index {}; // 0x0
	uint32_t UniqueId {}; // 0x4
	FREDAudioHandle() {}
	bool operator==(const FREDAudioHandle &);
	bool operator!=(const FREDAudioHandle &);
	bool IsValid();
	void Invalid();
};
