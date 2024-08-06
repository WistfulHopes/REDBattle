#pragma once
#include <cstdint>

class REDStateMachine {
public:
    REDStateMachine();

private:
    REDStateMachine* NewSubState();

protected:
    virtual void BeginState();
    virtual void TickState(float DeltaSeconds);
    virtual void EndState();
    
public:
	void ChangeSubState(REDStateMachine* state);

private:
	float StateTime; // 0x28
	uint32_t TickCounter; // 0x2C
	int32_t Result; // 0x30
	REDStateMachine* CurrentSubState; // 0x38
};

class REDStateMachineRoot : public REDStateMachine
{
public:
    REDStateMachineRoot();
	virtual void BeginState() override;
	virtual void EndState() override;

private:
    bool bStarted;
};