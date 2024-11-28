#include "UtilityStateMachine.h"

void REDStateMachine::BeginState()
{
    Result = -1;
    CurrentSubState = nullptr;
    StateTime = 0;
    TickCounter = 0;
}

void REDStateMachine::TickState(float DeltaSeconds)
{
    if (CurrentSubState) CurrentSubState->TickState(DeltaSeconds);
    StateTime += DeltaSeconds;
    TickCounter++;
}

void REDStateMachine::EndState()
{
    if (CurrentSubState) CurrentSubState->EndState();
    CurrentSubState = nullptr;
}

void REDStateMachine::ChangeSubState(REDStateMachine* state)
{
    if (CurrentSubState) CurrentSubState->EndState();
    CurrentSubState = state;
    if (state) state->BeginState();
}

void REDStateMachineRoot::BeginState()
{
    REDStateMachine::BeginState();
    bStarted = true;
}

void REDStateMachineRoot::EndState()
{
    bStarted = false;
    REDStateMachine::EndState();
}
