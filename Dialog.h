#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"

#include "Frame.h"
#include "Label.h"

class Dialog
{
public:
	Dialog(SharedContext* sharedContext, sf::Vector2f position, sf::Vector2f size,
		std::string title, int fontSize,
		sf::Color frameColor = sf::Color(127, 127, 127), sf::Color textColor = sf::Color::White);
	virtual ~Dialog();

	void Render();

	SharedContext* GetSharedContext();

	void SetPosition(sf::Vector2f position);

private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;

	Frame* frame;
	Label* label;

	sf::Vector2f position;
	sf::Vector2f size;
	std::string title;
	int fontSize;
};
