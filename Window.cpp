#include "Window.h"

#include "Settings.h"

void Window::Setup(Settings* settings)
{
	width = settings->GetWindowWidth();
	height = settings->GetWindowHeight();
	displayMode = settings->GetDisplayMode();
	defaultFullscreenMode = settings->GetDefaultFullscreenMode();
	vsync = settings->GetVSync();
	framerateLimit = settings->GetFramerateLimit();
	antiAliasing = settings->GetAntiAliasing();

	ChangeVideoMode(); // Apply changes
}

void Window::ChangeVideoMode()
{
	sf::ContextSettings contextSettings;
	//contextSettings.attributeFlags = sf::ContextSettings::Attribute::Core; // OpenGL core profile
	//contextSettings.majorVersion = 4; // OpenGL 4.3
	//contextSettings.minorVersion = 3; // ..
	//contextSettings.antialiasingLevel = 8; // 8x Anti Aliasing
	contextSettings.antialiasingLevel = antiAliasing; // 8x Anti Aliasing

	renderWindow.close();
	renderWindow.create(sf::VideoMode(width, height), "TimWorld", displayMode, contextSettings);
	renderWindow.setVerticalSyncEnabled(vsync);
	renderWindow.setFramerateLimit(framerateLimit); // 0:No limit
	renderWindow.setMouseCursorGrabbed((displayMode == DisplayMode::FULLSCREEN ? true : false));
	renderWindow.setMouseCursorVisible(false);

	// Place mouse cursor in the center of the window. If not things aren't drawn.
	sf::Mouse::setPosition(sf::Vector2i(renderWindow.getSize().x/2, renderWindow.getSize().y/2), renderWindow);
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &renderWindow;
}

void Window::CheckEvents(sf::Event &event)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		if (event.key.alt && event.key.code == sf::Keyboard::Return)
		{
			if (displayMode == DisplayMode::FULLSCREEN || displayMode == DisplayMode::BORDERLESS)
				displayMode = DisplayMode::WINDOWED;
			else
				displayMode = defaultFullscreenMode;
			ChangeVideoMode();
		}
		break;
	case sf::Event::Closed:
		renderWindow.close();
		break;
	}
}

void Window::RenderBegin()
{
//	renderWindow.clear(sf::Color::Black);
	//renderWindow.clear(sf::Color(47,47,47)); // Dark theme
	//renderWindow.clear(sf::Color(192, 192, 192)); // Win95 theme

	renderWindow.clear(sf::Color(91, 91, 91));
}

void Window::RenderEnd()
{
	renderWindow.display();
}
