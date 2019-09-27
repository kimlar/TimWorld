#pragma once

#include <SFML/Graphics.hpp>

#include "Window.h"
#include "Controls.h"
#include "Camera.h"
#include "Mouse.h"

#include "StateManager.h"
#include "ResourceManager.h"
#include "Settings.h"
#include "SharedContext.h"

class Engine
{
public:
	void Run();
	void Shutdown();

	Window &GetWindow();
	bool restartVideo = false;

	void BindControls();

private:
	SharedContext sharedContext;
	StateManager* stateManager;
	ResourceManager resourceManager;
	Settings* settings;

	Window window;
	Controls controls;
	Camera camera;
	//Mouse mouse;
	Mouse* mouse;

	bool run = true;
};
