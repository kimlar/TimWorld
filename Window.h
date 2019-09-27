#pragma once

#include <SFML/Graphics.hpp>

class Settings;

enum DisplayMode
{
	FULLSCREEN = sf::Style::Fullscreen,	// fullscreen mode
	BORDERLESS = sf::Style::None,		// borderless windowed mode
	WINDOWED = sf::Style::Titlebar | sf::Style::Close,		// windowed mode
};

class Window
{
public:
	Window() {}
	virtual ~Window() {}

	void Setup(Settings* settings);
	void ChangeVideoMode();

	void CheckEvents(sf::Event &event);

	void RenderBegin();
	void RenderEnd();

	sf::RenderWindow* GetRenderWindow();

private:
	sf::RenderWindow renderWindow;
	int width;
	int height;

	DisplayMode displayMode = DisplayMode::FULLSCREEN;
	DisplayMode defaultFullscreenMode = DisplayMode::FULLSCREEN;
	bool vsync = false;
	int framerateLimit = 0;
	int antiAliasing = 0;
};
