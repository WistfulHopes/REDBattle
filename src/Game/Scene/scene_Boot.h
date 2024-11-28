#pragma once
#include "scene_Base.h"
#include "Game/Utility/UtilityStateMachine.h"

class REDBootSequenceRoot : public REDStateMachineRoot 
{
public:
    REDBootSequenceRoot();

    void BeginState() override;
    void TickState(float DeltaSeconds) override;

private:
	class REDBootSequenceInit * SeqInit {}; // 0x50
	class REDBootSequenceStaticLoad * SeqStaticLoad {}; // 0x58
	class REDBootSequencePreLoadData * SeqPreLoadData {}; // 0x68
	class REDBootSequenceSaveDataRoot * SeqSaveData {}; // 0x70
};

class REDBootSequenceInit : public REDStateMachine 
{
public:
    REDBootSequenceInit() {}

    void BeginState() override;
};

class REDBootSequenceStaticLoad : public REDStateMachine 
{
public:
    REDBootSequenceStaticLoad() {}

    void BeginState() override;
    void TickState(float DeltaSeconds) override;
};

class REDBootSequencePreLoadData : public REDStateMachine 
{
public:
    REDBootSequencePreLoadData() {}

    void BeginState() override;
    void TickState(float DeltaSeconds) override;
    void EndState() override;
};

class REDBootSequenceSaveDataRoot : public REDStateMachine
{
public:
    REDBootSequenceSaveDataRoot() {}

    void BeginState() override;
    void TickState(float DeltaSeconds) override;

private:
    float TotalTickTime {};
};

class SCENE_CBoot : public SCENE_CBase 
{
public:
    SCENE_CBoot();
    ~SCENE_CBoot();

public:
    void SceneInitialize() override;
    void Tick(float DeltaSeconds) override;
    
private:
    REDBootSequenceRoot* Sequencer {};
};