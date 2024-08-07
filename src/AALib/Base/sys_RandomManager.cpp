#include "sys_RandomManager.h"

bool AA_CRandomManager::Init(uint32_t val, int32_t idx)
{
    return Get(idx)->Init(val);
}
