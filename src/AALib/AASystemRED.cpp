#include "AASystemRED.h"

#include <chrono>

AASystemRED::AASystemRED() 
{
    m_bInitialized = false;
}

void AASystemRED::Initialize()
{
    auto cam = new AA_CCamera();
    m_CameraManager.RegistInstance(cam);

    for (int i = 0; i < 2; i++)
    {
        auto rand = new AA_CRandMT();
        m_RandomManager.RegistInstance(rand);

        auto now = std::chrono::system_clock::now();
        m_RandomManager.Init(now.time_since_epoch().count(), i);

        s_Rand.Init(now.time_since_epoch().count());
        m_bInitialized = true;
    }
}

void AASystemRED::StaticInitialize()
{
    if (s_Instance) return;

    s_Instance = new AASystemRED();
    s_Instance->Initialize();
}