#pragma once

#include <SFML/Graphics.hpp>

#include "StateManager.h"
#include "ResourceManager.h"
#include "Controls.h"
#include "Camera.h"
#include "Mouse.h"
#include "Settings.h"

class StateManager;
class Engine;
class Mouse;

struct SharedContext
{
	SharedContext() :	stateManager(nullptr),
						resourceManager(nullptr),
						renderWindow(nullptr),
						controls(nullptr),
						camera(nullptr),
						engine(nullptr),
						mouse(nullptr),
						settings(nullptr) {}
	StateManager* stateManager;
	ResourceManager* resourceManager;
	sf::RenderWindow* renderWindow;
	Controls* controls;
	Camera* camera;
	Engine* engine;
	Mouse* mouse;
	Settings* settings;

	StateManager* GetStateManager() { return stateManager; }
	ResourceManager* GetResourceManager() { return resourceManager; }
	sf::RenderWindow* GetRenderWindow() { return renderWindow; }
	Controls* GetControls() { return controls; }
	Camera* GetCamera() { return camera; }
	Engine* GetEngine() { return engine; }
	Mouse* GetMouse() { return mouse; }
	Settings* GetSettings() { return settings; }
};
