#include "Controls.h"

/*
void Controls::BindControls()
{
	//bindings[BindActions::MoveCameraLeft] = {};
	//bindings[BindActions::MoveCameraLeft].type = sf::Event::KeyPressed;
	//bindings[BindActions::MoveCameraLeft].key.code = sf::Keyboard::A;
	
	//bindings[BindActions::MoveCameraRight] = {};
	//bindings[BindActions::MoveCameraRight].type = sf::Event::KeyPressed;
	//bindings[BindActions::MoveCameraRight].key.code = sf::Keyboard::D;

	//bindings[BindActions::MoveCameraUp] = {};
	//bindings[BindActions::MoveCameraUp].type = sf::Event::KeyPressed;
	//bindings[BindActions::MoveCameraUp].key.code = sf::Keyboard::W;

	//bindings[BindActions::MoveCameraDown] = {};
	//bindings[BindActions::MoveCameraDown].type = sf::Event::KeyPressed;
	//bindings[BindActions::MoveCameraDown].key.code = sf::Keyboard::S;

	bindings[BindActions::ZoomCameraIn] = {};
	bindings[BindActions::ZoomCameraIn].type = sf::Event::MouseWheelScrolled;
	bindings[BindActions::ZoomCameraIn].mouseWheelScroll.wheel = sf::Mouse::VerticalWheel;

	bindings[BindActions::ZoomCameraOut] = {};
	bindings[BindActions::ZoomCameraOut].type = sf::Event::MouseWheelScrolled;
	bindings[BindActions::ZoomCameraOut].mouseWheelScroll.wheel = sf::Mouse::VerticalWheel;
}
*/

void Controls::CheckEvents(sf::Event &event)
{
	for (auto &i : bindings)
	{
		// Check keyboard events
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			if (i.second.type == sf::Event::KeyPressed || i.second.type == sf::Event::KeyReleased)
			{
				if (event.key.code == i.second.key.code)
				{
					DoAction(i.first, (event.type == sf::Event::KeyPressed) ? true : false);
					break;
				}
			}
		}
		// Check mouse events
		if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
		{
			if (i.second.type == sf::Event::MouseButtonPressed || i.second.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == i.second.mouseButton.button)
				{
					DoAction(i.first, (event.type == sf::Event::MouseButtonPressed) ? true : false);
					break;
				}
			}
		}
	}
}

void Controls::DoAction(int action, bool activate)
{
	switch (action)
	{
	case BindActions::MoveCameraLeft:
		moveCameraLeft = activate;
		break;
	case BindActions::MoveCameraRight:
		moveCameraRight = activate;
		break;
	case BindActions::MoveCameraUp:
		moveCameraUp = activate;
		break;
	case BindActions::MoveCameraDown:
		moveCameraDown = activate;
		break;
	}
}
