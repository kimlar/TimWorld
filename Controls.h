#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

enum BindActions
{
	MoveCameraLeft = 0,
	MoveCameraRight,
	MoveCameraUp,
	MoveCameraDown,
};

class Controls
{
public:
	//void BindControls();
	void CheckEvents(sf::Event &event);
	
	// Actions
	bool quitGame;
	bool moveCameraLeft;
	bool moveCameraRight;
	bool moveCameraUp;
	bool moveCameraDown;

	// Bindings
	std::unordered_map<int, sf::Event> bindings;

private:
	void DoAction(int action, bool activate);
};
