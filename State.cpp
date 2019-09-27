#include "State.h"

State::State(SharedContext* sharedContext) : sharedContext(sharedContext)
{
	stateManager = sharedContext->stateManager;
}

SharedContext* State::GetSharedContext()
{
	return sharedContext;
}

StateManager* State::GetStateManager()
{
	return stateManager;
}
