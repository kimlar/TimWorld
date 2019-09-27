#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"

#include "Frame.h"
#include "Label.h"

class CheckBox
{
public:
	enum class CheckBoxState { Unchecked = 0, Checked, Disabled };

	CheckBox(SharedContext* sharedContext, sf::Vector2f position, std::string text, CheckBoxState state = CheckBoxState::Unchecked);
	virtual ~CheckBox();

	void CheckEvents(sf::Event &event);
	void Render();

	SharedContext* GetSharedContext();

	void SetCheckBoxState(CheckBoxState state);
	bool IsChecked();

private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;

	Frame* frame;
	Label* label;

	sf::Vector2f position;
	sf::Vector2f size;
	std::string labelText;
	int fontSize;
	
	CheckBoxState checkBoxState;

	sf::RectangleShape markLine1; // TODO: Reimplement as textures instead
	sf::RectangleShape markLine2; // ...
};
