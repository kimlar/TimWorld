#pragma once

#include <queue>

#include "SharedContext.h"
#include "State.h"

struct SharedContext;
class State;

class StateManager
{
public:
	StateManager(SharedContext* sharedContext);
	~StateManager();

	void PushState(State* state);
	void PopState();
	
	State* GetCurrentState();

	void Free();
	void ApplyQueue();

	SharedContext* GetSharedContext();

private:
	SharedContext* sharedContext;
	
	std::stack<State*> states;

	struct StateAction
	{
		bool push;
		State* state;
	};
	std::queue<StateAction> stateQueue;
};
