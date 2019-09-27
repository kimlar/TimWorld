#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"

class TestBox
{
public:
	TestBox(SharedContext* sharedContext);
	virtual ~TestBox();

	void Update(float delta);
	void Render();

	SharedContext* GetSharedContext();

private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;
	sf::Texture* texture;
	sf::Shader shader;
	sf::RenderStates renderStates;
	sf::Sprite sprite;
	std::string textureFileName;
	float tpos = 0.0f;
};
