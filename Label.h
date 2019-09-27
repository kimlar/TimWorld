#pragma once


#include <SFML/Graphics.hpp>

#include "SharedContext.h"

class Label
{
public:
	Label(SharedContext* sharedContext, sf::Vector2f position, std::string text, int fontSize);
	virtual ~Label();

	void Render();

	SharedContext* GetSharedContext();

	//void SetPosition(sf::Vector2f position);
	void SetColor(sf::Color color);
	void SetText(std::string text);

	std::string GetText();
	int GetTextWidth();
	int GetWidthOfPartText(int location);

private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;

	sf::Color color;
	sf::Font* font;
	sf::Text text;
};
