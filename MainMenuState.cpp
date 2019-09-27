#include "MainMenuState.h"

#include "GameplayState.h"
#include "OptionsState.h"

#include "Engine.h"

MainMenuState::MainMenuState(SharedContext* sharedContext) : State(sharedContext)
{
	Log("MainMenuState: Constructor");
}

MainMenuState::~MainMenuState()
{
	Log("MainMenuState: Destructor");
}

void MainMenuState::Enter()
{
	Log("MainMenuState: Enter");
	
	testBox = new TestBox(GetSharedContext());

	//frameTest = new Frame(GetSharedContext(), sf::Vector2f(200, 300), sf::Vector2f(200, 45));

	int menuW = 200;
	int menuH = 200;
	int menuX = GetSharedContext()->GetRenderWindow()->getSize().x / 2 - menuW/2;
	int menuY = GetSharedContext()->GetRenderWindow()->getSize().y / 2 - menuH/2;

	mainMenuDialog = new Dialog(GetSharedContext(), sf::Vector2f((float)menuX, (float)menuY),
		sf::Vector2f((float)menuW, (float)menuH), "MAIN MENU", 50, sf::Color(127, 127, 127, 140));

	//mainMenuLabel = new Label(GetSharedContext(), sf::Vector2f((float)menuX - 60, (float)menuY - 100), "MAIN MENU", 50);

	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(menuX - 50, menuY + 0, 300, 45), "New Game", 28));
	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(menuX - 50, menuY + 50, 300, 45), "Options", 28));
	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(menuX - 50, menuY + 100, 300, 45), "Exit", 28));
}

void MainMenuState::Exit()
{
	Log("MainMenuState: Exit");

	delete mainMenuDialog;
	mainMenuDialog = nullptr;

	//delete mainMenuLabel;
	//mainMenuLabel = nullptr;

	//delete frameTest;
	//frameTest = nullptr;

	for (int i = 0; i < buttons.size(); i++)
	{
		Log("MainMenuState: Exit: deleting button[" + std::to_string(i) + "]");
		delete buttons[i];
		buttons[i] = nullptr;
	}
	buttons.clear();

	delete testBox;
	testBox = nullptr;
}

void MainMenuState::Event(sf::Event &event)
{
	//Log("MainMenuState: Event");

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
	{
		//Log("push GameplayState()");

		GetStateManager()->PopState(); // Should I pop it or not ????
		GetStateManager()->PushState(new GameplayState(GetSharedContext()));
		return;
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
	{
		//Log("push OptionsState()");

		GetStateManager()->PopState(); // Should I pop it or not ????
		GetStateManager()->PushState(new OptionsState(GetSharedContext()));
		return;
	}

	////////////////////////

	if (buttons[0]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		GetStateManager()->PopState(); // Should I pop it or not ????
		GetStateManager()->PushState(new GameplayState(GetSharedContext()));
		return;
	}
	if (buttons[1]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		GetStateManager()->PopState(); // Should I pop it or not ????
		GetStateManager()->PushState(new OptionsState(GetSharedContext()));
		return;
	}
	if (buttons[2]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		GetSharedContext()->GetEngine()->Shutdown();
		return;
	}

}

void MainMenuState::Update(float delta)
{
	//Log("MainMenuState: Update");

	testBox->Update(delta);

	//frameTest->Update(delta);
}

void MainMenuState::Render()
{
	//Log("MainMenuState: Render");

	testBox->Render();

	mainMenuDialog->Render();

	//mainMenuLabel->Render();

	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->Render();

	//frameTest->Render();
}
