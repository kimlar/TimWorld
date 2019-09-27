#include "InitState.h"

#include "MainMenuState.h"

InitState::InitState(SharedContext* sharedContext) : State(sharedContext)
{
	Log("InitState: Constructor");
}

InitState::~InitState()
{
	Log("InitState: Destructor");
}

void InitState::Enter()
{
	Log("InitState: Enter");
}

void InitState::Exit()
{
	Log("InitState: Exit");
}

void InitState::Event(sf::Event &event)
{
	//Log("InitState: Event");

	GetStateManager()->PopState();
	GetStateManager()->PushState(new MainMenuState(GetSharedContext()));
}

void InitState::Update(float delta)
{
	//Log("InitState: Update");
}

void InitState::Render()
{
	//Log("InitState: Render");
}
