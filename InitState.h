#pragma once

#include "State.h"
#include "SharedContext.h"

class InitState : public State
{
public:
	InitState(SharedContext* sharedContext);
	~InitState();

	void Enter();
	void Exit();

	void Event(sf::Event &event);
	void Update(float delta);
	void Render();

private:
};
