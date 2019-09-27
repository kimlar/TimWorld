#pragma once

#include "State.h"
#include "SharedContext.h"

#include "Button.h"

#include "Terrain.h"
#include "Building.h"
#include "House.h"

class GameplayState : public State
{
public:
	GameplayState(SharedContext* sharedContext);
	~GameplayState();

	void Enter();
	void Exit();

	void Event(sf::Event &event);
	void Update(float delta);
	void Render();

private:
	std::vector<Button*> buttons;
	bool showInGameMenu = false;

	Terrain* terrain;
	Building* building;
	//House* house;

	std::vector<House*> houses;

};
