#include "scene_Boot.h"
#include <AASystemRED.h>

static bool s_bInitialized;

void REDInitializeOnce() 
{
    if (s_bInitialized) return;

    AASystemRED::StaticInitialize();

    s_bInitialized = true;
}

REDBootSequenceRoot::REDBootSequenceRoot()
{
    SeqInit = new REDBootSequenceInit();
    SeqStaticLoad = new REDBootSequenceStaticLoad();
    SeqPreLoadData = new REDBootSequencePreLoadData();
    SeqSaveData = new REDBootSequenceSaveDataRoot();
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
    REDInitializeOnce();
    ChangeSubState(SeqInit);
}

void REDBootSequenceRoot::TickState(float DeltaSeconds)
{
    REDStateMachineRoot::TickState(DeltaSeconds);

    if (GetCurrentState() && GetCurrentState()->GetResult() != -1)
    {
        if (GetCurrentState() == SeqInit)
        {
            ChangeSubState(SeqStaticLoad);
        }
        else if (GetCurrentState() == SeqStaticLoad)
        {
            ChangeSubState(SeqPreLoadData);   
        }
        else if (GetCurrentState() == SeqPreLoadData)
        {
            ChangeSubState(SeqSaveData);
        }
        else if (GetCurrentState() == SeqSaveData)
        {
            ChangeSubState(nullptr);
            SetResult(0);
        }
    }
}

void REDBootSequenceInit::BeginState()
{
    REDStateMachine::BeginState();
    SetResult(0);
}

void REDBootSequenceStaticLoad::BeginState()
{
    REDStateMachine::BeginState();
}

void REDBootSequenceStaticLoad::TickState(float DeltaSeconds)
{
    if (GetResult() == -1)
    {
        SetResult(0);
    }
}

void REDBootSequencePreLoadData::BeginState()
{
    REDStateMachine::BeginState();
}

void REDBootSequencePreLoadData::TickState(float DeltaSeconds)
{
    if (GetResult() == -1)
    {
        SetResult(0);
    }
}

void REDBootSequencePreLoadData::EndState()
{
}

void REDBootSequenceSaveDataRoot::BeginState()
{
    REDStateMachine::BeginState();
}

void REDBootSequenceSaveDataRoot::TickState(float DeltaSeconds)
{
    if (GetResult() == -1)
    {
        SetResult(0);
    }
}