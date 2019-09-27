#include "GameplayState.h"

#include "Controls.h"
#include "Engine.h"

#include "MainMenuState.h" //TEMP!

GameplayState::GameplayState(SharedContext* sharedContext) : State(sharedContext)
{
	Log("GameplayState: Constructor");
}

GameplayState::~GameplayState()
{
	Log("GameplayState: Destructor");
}

void GameplayState::Enter()
{
	Log("GameplayState: Enter");

	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(0, 0, 100, 45), "Exit", 28));

	GetSharedContext()->GetCamera()->SetCameraPosition(0.0f, 0.0f);

	terrain = new Terrain(GetSharedContext());

	building = new Building(GetSharedContext(), "Building-treehouse-01.png", sf::Vector2f(320, 320));
	
	//house = new House(GetSharedContext(), "Building-treehouse-01.png", sf::Vector2f(200, 100), sf::Vector2i(352, 192));
	//house = new House(GetSharedContext(), "Building-treehouse-01.png", sf::Vector2f(200, 100));
	//house = new House(GetSharedContext(), "Building-treehouse-01.txt", sf::Vector2f(200, 100));

	houses.push_back(new House(GetSharedContext(), "Building-treehouse-01.txt", sf::Vector2f(200, 100)));
	houses.push_back(new House(GetSharedContext(), "Building-treehouse-01.txt", sf::Vector2f(900, 300)));
	houses.push_back(new House(GetSharedContext(), "Building-treehouse-02.txt", sf::Vector2f(1200, 600)));


	/*
	house->PreRenderClear();
	// 0
	house->PreRenderAdd(sf::Vector2f(0, 0), 0);
	house->PreRenderAdd(sf::Vector2f(32, 0), 1);
	house->PreRenderAdd(sf::Vector2f(64, 0), 1);
	house->PreRenderAdd(sf::Vector2f(96, 0), 1);
	house->PreRenderAdd(sf::Vector2f(128, 0), 1);
	house->PreRenderAdd(sf::Vector2f(160, 0), 0);
	house->PreRenderAdd(sf::Vector2f(192, 0), 1);
	house->PreRenderAdd(sf::Vector2f(224, 0), 1);
	house->PreRenderAdd(sf::Vector2f(256, 0), 1);
	house->PreRenderAdd(sf::Vector2f(288, 0), 1);
	house->PreRenderAdd(sf::Vector2f(320, 0), 0);
	// 1
	house->PreRenderAdd(sf::Vector2f(0, 32), 2);
	house->PreRenderAdd(sf::Vector2f(320, 32), 2);
	// 2
	house->PreRenderAdd(sf::Vector2f(0, 64), 2);
	house->PreRenderAdd(sf::Vector2f(320, 64), 2);
	// 3
	house->PreRenderAdd(sf::Vector2f(0, 96), 2);
	house->PreRenderAdd(sf::Vector2f(320, 96), 2);
	// 4
	house->PreRenderAdd(sf::Vector2f(0, 128), 2);
	house->PreRenderAdd(sf::Vector2f(320, 128), 2);
	// 5
	house->PreRenderAdd(sf::Vector2f(0, 160), 0);
	house->PreRenderAdd(sf::Vector2f(32, 160), 1);
	house->PreRenderAdd(sf::Vector2f(64, 160), 1);
	house->PreRenderAdd(sf::Vector2f(96, 160), 1);
	house->PreRenderAdd(sf::Vector2f(128, 160), 1);
	house->PreRenderAdd(sf::Vector2f(160, 160), 0);
	house->PreRenderAdd(sf::Vector2f(192, 160), 1);
	house->PreRenderAdd(sf::Vector2f(224, 160), 1);
	house->PreRenderAdd(sf::Vector2f(256, 160), 1);
	house->PreRenderAdd(sf::Vector2f(288, 160), 1);
	house->PreRenderAdd(sf::Vector2f(320, 160), 0);
	
	house->PreRenderCompile();
	*/
}

void GameplayState::Exit()
{
	Log("GameplayState: Exit");

	delete building;
	building = nullptr;

	delete terrain;
	terrain = nullptr;

	//delete house;
	//house = nullptr;
		
	for (int i = 0; i < houses.size(); i++)
	{
		//Log("GameplayState: Exit: deleting houses[" + std::to_string(i) + "]");
		delete houses[i];
		houses[i] = nullptr;
	}
	houses.clear();

	for (int i = 0; i < buttons.size(); i++)
	{
		Log("GameplayState: Exit: deleting button[" + std::to_string(i) + "]");
		delete buttons[i];
		buttons[i] = nullptr;
	}
	buttons.clear();
}

void GameplayState::Event(sf::Event &event)
{
	//Log("GameplayState: Event");


	if (buttons[0]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		GetStateManager()->PopState();
		GetStateManager()->PushState(new MainMenuState(GetSharedContext()));
		return;
	}
	////////////////////////


	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
	{
		GetStateManager()->PopState();
		GetStateManager()->PushState(new MainMenuState(GetSharedContext()));
	}


	GetSharedContext()->GetControls()->CheckEvents(event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		GetSharedContext()->GetEngine()->Shutdown();
	}
}

void GameplayState::Update(float delta)
{
	//Log("GameplayState: Update");

	terrain->Update(delta);

	building->Update(delta);

	//house->Update(delta);

	for (int i = 0; i < houses.size(); i++)
		houses[i]->Update(delta);
}

void GameplayState::Render()
{
	//Log("GameplayState: Render");

	terrain->Render();

	building->Render();

	//house->Render();

	for (int i = 0; i < houses.size(); i++)
		houses[i]->Render();


	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->Render();
}
