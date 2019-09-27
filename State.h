#pragma once

#include "SharedContext.h"
#include "StateManager.h"

struct SharedContext;
class StateManager;

class State
{
public:

	State(SharedContext* sharedContext);
	virtual ~State() {}

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Event(sf::Event &event) = 0;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
	
	SharedContext* GetSharedContext();
	StateManager* GetStateManager();
	
private:
	SharedContext* sharedContext;
	StateManager* stateManager;
};
