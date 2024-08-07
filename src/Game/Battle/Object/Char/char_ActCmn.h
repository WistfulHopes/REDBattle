#pragma once
#include "Common/cmn_typedef.h"

static inline CXXBYTE<32> AN_CmnActEntryWait = "CmnActEntryWait";
static inline CXXBYTE<32> FN_PreInit = "PreInit";
static inline CXXBYTE<32> FN_PreInit2nd = "PreInit2nd";

static inline CXXBYTE<32>* CmnActNameTable[1] = {
    &AN_CmnActEntryWait
};