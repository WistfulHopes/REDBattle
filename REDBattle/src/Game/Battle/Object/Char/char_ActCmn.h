#pragma once
#include "AALib/Common/cmn_typedef.h"

static inline CXXBYTE<32> AN_CmnActStand = "CmnActStand";
static inline CXXBYTE<32> AN_CmnActCrouch = "CmnActCrouch";
static inline CXXBYTE<32> AN_CmnActJump = "CmnActJump";
static inline CXXBYTE<32> AN_CmnActKizetsu = "CmnActKizetsu";
static inline CXXBYTE<32> AN_CmnActHizakuzure = "CmnActHizakuzure";
static inline CXXBYTE<32> AN_CmnActLockWait = "CmnActLockWait";
static inline CXXBYTE<32> AN_CmnActEntryWait = "CmnActEntryWait";
static inline CXXBYTE<32> AN_CmnActChangeLeave = "CmnActChangeLeave";

static inline CXXBYTE<32> ANCX_Neutral = "_NEUTRAL";

static inline CXXBYTE<32> FN_PreInit = "PreInit";
static inline CXXBYTE<32> FN_PreInit2nd = "PreInit2nd";
static inline CXXBYTE<32> FN_RoundInit = "RoundInit";
static inline CXXBYTE<32> FN_OnActionBeginPre = "OnActionBeginPre";
static inline CXXBYTE<32> FN_OnActionBegin = "OnActionBegin";
static inline CXXBYTE<32> FN_OnFinalize = "OnFinalize";

static inline CXXBYTE<32> CN_Null = "null";
static inline CXXBYTE<32> CN_Keep = "keep";

static inline CXXBYTE<32>* CmnActNameTable[8] = {
    &AN_CmnActStand,
    &AN_CmnActCrouch,
    &AN_CmnActJump,
    &AN_CmnActKizetsu,
    &AN_CmnActHizakuzure,
    &AN_CmnActLockWait,
    &AN_CmnActEntryWait,
    &AN_CmnActChangeLeave,
};