#include "Engine.h"

#include <vector>

#include "Logger.h"
#include "Debugger.h"
#include "Todo.h"
#include "Settings.h"
#include "Fps.h"

#include "InitState.h"

void Engine::Run()
{
	LogBegin();
	DebugBegin();
	TodoBegin();

	// Shared context
	sharedContext.engine = this;
	sharedContext.resourceManager = &resourceManager;

	// State manager
	stateManager = new StateManager(&sharedContext);
	sharedContext.stateManager = stateManager;

	// Read settings
	//Settings settings;
	settings = new Settings(); // TODO: Implement SharedContext in Constructor
	settings->Setup();
	settings->Load();
	sharedContext.settings = settings;
	
	// Getting settings
	//bool skipIntro = settings.GetSkipIntro();
	//std::string language = settings.GetLanguage();
	//int masterVolume = settings.GetMasterVolume();
	//int musicVolume = settings.GetMusicVolume();
	//int soundFxVolume = settings.GetSoundFxVolume();
	//int voiceVolume = settings.GetVoiceVolume();

	// Binding controls	
	//controls.BindControls();
	/*
	controls.bindings[BindActions::MoveCameraLeft] = settings->GetMoveCameraLeft();
	controls.bindings[BindActions::MoveCameraRight] = settings->GetMoveCameraRight();
	controls.bindings[BindActions::MoveCameraUp] = settings->GetMoveCameraUp();
	controls.bindings[BindActions::MoveCameraDown] = settings->GetMoveCameraDown();
	*/
	BindControls();
	sharedContext.controls = &controls;

	// Window
	//window.Setup(&settings);
	window.Setup(settings);
	sharedContext.renderWindow = window.GetRenderWindow();

	// Quick refresh
	window.RenderBegin();
	window.RenderEnd();

	// Camera
	camera.SetCameraMoveSpeed(settings->GetCameraMoveSpeed());
	camera.Setup(controls);
	sharedContext.camera = &camera;

	// Mouse
	//Mouse mouse = Mouse();
	mouse = new Mouse(&sharedContext, "Mouse-08.png");
	//sharedContext.mouse = &mouse;
	sharedContext.mouse = mouse;
	
	// Timing
	sf::Clock clock;
	clock.restart();
	float delta = 0.0f;


	//Log("push InitState()");
	stateManager->PushState(new InitState(&sharedContext));
	stateManager->ApplyQueue();

	// Load fonts
	sharedContext.GetResourceManager()->PreLoadFont("OpenSans-Regular.ttf");
	sharedContext.GetResourceManager()->PreLoadFont("OpenSans-SemiBold.ttf");

	// FPS
	Fps fps(&sharedContext);
	fps.active = settings->GetShowFPS();

	//Log("Engine.cpp: Ready to enter game loop");
	while (sharedContext.GetRenderWindow()->isOpen() && run)
	{
		sf::Event event;
		while (sharedContext.GetRenderWindow()->pollEvent(event))
		{
			window.CheckEvents(event);
			//mouse.CheckEvents(event);
			mouse->CheckEvents(event);

			//stateManager->ApplyQueue();
			stateManager->GetCurrentState()->Event(event);
			stateManager->ApplyQueue();
		}
		
		//
		// Timing
		//
		delta = clock.restart().asSeconds();

		//
		// Update
		//
		fps.Update(delta);
		camera.Update(delta);
		stateManager->GetCurrentState()->Update(delta);

		//
		// Render
		//		
		window.RenderBegin();
		stateManager->GetCurrentState()->Render();
		fps.Render();
		mouse->Render();
		window.RenderEnd();
	}
	//Log("Engine.cpp: Just exited game loop");
	
	// Shutdown the state manager
	stateManager->Free();
	delete stateManager;
	stateManager = nullptr;

	delete mouse;
	mouse = nullptr;

	delete settings;
	settings = nullptr;
		
	// Shutdown all logger systems
	TodoEnd();
	DebugEnd();
	LogEnd();
}

void Engine::Shutdown()
{
	this->run = false;
}

Window &Engine::GetWindow()
{
	return window;
}

void Engine::BindControls()
{
	controls.bindings[BindActions::MoveCameraLeft] = settings->GetMoveCameraLeft();
	controls.bindings[BindActions::MoveCameraRight] = settings->GetMoveCameraRight();
	controls.bindings[BindActions::MoveCameraUp] = settings->GetMoveCameraUp();
	controls.bindings[BindActions::MoveCameraDown] = settings->GetMoveCameraDown();
}
