#pragma once

#include "State.h"
#include "SharedContext.h"

#include "TestBox.h"
#include "Dialog.h"
#include "Button.h"
//#include "Label.h"
//#include "Frame.h"

class MainMenuState : public State
{
public:
	MainMenuState(SharedContext* sharedContext);
	~MainMenuState();

	void Enter();
	void Exit();

	void Event(sf::Event &event);
	void Update(float delta);
	void Render();

private:
	TestBox* testBox;

	Dialog* mainMenuDialog;

	//Frame* frameTest;
	//Label* mainMenuLabel;
	std::vector<Button*> buttons;
};
