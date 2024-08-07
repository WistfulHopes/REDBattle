#pragma once
#include "scene_Base.h"
#include "Utility/UtilityStateMachine.h"

class REDBootSequenceRoot : public REDStateMachineRoot 
{
public:
    REDBootSequenceRoot();
    
    virtual void BeginState() override;
	virtual void TickState(float DeltaSeconds) override;

private:
	class REDBootSequenceInit * SeqInit; // 0x50
	class REDBootSequenceStaticLoad * SeqStaticLoad; // 0x58
	class REDBootSequencePreLoadData * SeqPreLoadData; // 0x68
	class REDBootSequenceSaveDataRoot * SeqSaveData; // 0x70
};

class REDBootSequenceInit : public REDStateMachine 
{
public:
    REDBootSequenceInit() {}
    
    virtual void BeginState() override;
};

class REDBootSequenceStaticLoad : public REDStateMachine 
{
public:
    REDBootSequenceStaticLoad() {}
    
    virtual void BeginState() override;
	virtual void TickState(float DeltaSeconds) override;
};

class REDBootSequencePreLoadData : public REDStateMachine 
{
public:
    REDBootSequencePreLoadData() {}

	virtual void BeginState() override;
	virtual void TickState(float DeltaSeconds) override;
	virtual void EndState() override;
};

class REDBootSequenceSaveDataRoot : public REDStateMachine
{
public:
    REDBootSequenceSaveDataRoot() {}

	virtual void BeginState() override;
	virtual void TickState(float DeltaSeconds) override;

private:
    float TotalTickTime;
};

class SCENE_CBoot : public SCENE_CBase 
{
public:
    SCENE_CBoot();
    ~SCENE_CBoot();

public:
    virtual void SceneInitialize();
    
private:
    REDBootSequenceRoot* Sequencer;
};