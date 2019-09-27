#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"

#include "Frame.h"

class Button
{
public:
	Button(SharedContext* sharedContext, sf::Rect<int> rect, std::string text, int fontSize);
	virtual ~Button();

	enum class ButtonAction { Idle = 0, LeftClicked, MidClicked, RightClicked };

	ButtonAction CheckEvents(sf::Event &event);
	//void Update(float delta);
	void Render();

	SharedContext* GetSharedContext();

	void SetButtonColor(sf::Color color);
	void ResetButtonColor();

	//void SetPressedDown(bool down);

	void ResetEvent();

private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;

	Frame* frame;
	sf::Color colorRelease;
	sf::Color colorPressed;
	sf::Color colorHovered;
	sf::Color colorText;
	sf::Font* font;
	sf::Text text;
	
	sf::Rect<int> buttonRect;

	int fontSize;
	std::string buttonText;
	int textHeightAdjustment;
	int GetTextHeightAdjustment();

	sf::Vector2i textHomePosition;

	enum class ButtonState { Released = 0, Pressed, Hovered, Disabled };
	ButtonState buttonState = ButtonState::Released; // TODO: Refactor
	bool mouseInside = false;
	bool buttonDown = false;
	bool pressedDownInside = false;
	
	void SetButtonDown(bool down);
};
