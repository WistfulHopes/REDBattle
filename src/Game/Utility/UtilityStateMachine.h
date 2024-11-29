#pragma once
#include <cstdint>

class REDStateMachine {
public:
    REDStateMachine() = default;
    virtual ~REDStateMachine() { delete CurrentSubState; }

private:
    REDStateMachine* NewSubState();

public:
    REDStateMachine * GetCurrentState() { return CurrentSubState; }
    int32_t GetResult() { return Result; }
    
protected:
    virtual void BeginState();
    virtual void TickState(float DeltaSeconds);
    virtual void EndState();
	void SetResult(int32_t inResult) { Result = inResult; }
    
public:
	void ChangeSubState(REDStateMachine* state);

private:
	float StateTime {}; // 0x28
	uint32_t TickCounter {}; // 0x2C
	int32_t Result {}; // 0x30
	REDStateMachine* CurrentSubState {}; // 0x38
};

class REDStateMachineRoot : public REDStateMachine
{
public:
    REDStateMachineRoot() {}
    void BeginState() override;
    void EndState() override;

private:
    bool bStarted {};
};