#include "AASystemRED.h"

AASystemRED::AASystemRED() 
{
    m_bInitialized = false;
}

void AASystemRED::Initialize()
{
    for (int i = 0; i < 2; i++)
    {
        
    }
}

void AASystemRED::StaticInitialize()
{
    if (s_Instance) return;

    s_Instance = new AASystemRED();
    s_Instance->Initialize();
}