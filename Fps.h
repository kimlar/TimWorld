#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"

class Fps
{
public:
	Fps(SharedContext* sharedContext);
	virtual ~Fps();

	void Update(float delta);
	void Render();

	SharedContext* sharedContext;
	bool active = false;

private:	
	float fpsTime = 0.0f;
	int fps = 0;
	int fpsCount = 0;
	sf::Text fpsText;

	sf::RenderWindow* renderWindow;
	sf::Font* font;
	sf::Vector2f position;
};
