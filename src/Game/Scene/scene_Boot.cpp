#include "scene_Boot.h"
#include <AASystemRED.h>

static bool s_bInitialized;

void REDInitializeOnce() 
{
    if (s_bInitialized) return;

    AASystemRED::StaticInitialize();

    s_bInitialized = true;
}

SCENE_CBoot::SCENE_CBoot()
{
    Sequencer = new REDBootSequenceRoot();
}

SCENE_CBoot::~SCENE_CBoot()
{
    delete Sequencer;
}

void SCENE_CBoot::SceneInitialize()
{
    SCENE_CBase::SceneInitialize();
    Sequencer->BeginState();
}

void REDBootSequenceRoot::BeginState()
{
    REDStateMachineRoot::BeginState();
    ChangeSubState(SeqInit);
}
