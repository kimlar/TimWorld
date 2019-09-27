#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"

class Frame
{
public:
	Frame(SharedContext* sharedContext, sf::Vector2f position, sf::Vector2f size);
	virtual ~Frame();

	void Update(float delta);
	void Render();

	SharedContext* GetSharedContext();

	void SetPressedDown(bool down);
	void SetButtonColor(sf::Color color);
	void SetPosition(sf::Vector2f position);

private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;
	sf::Texture* texture;
	sf::VertexArray vao;
	sf::RenderStates renderStates;
	sf::Transform transform;
	std::string textureFileName;

	sf::Vector2f position;
	sf::Vector2f size;

	bool isPressedDown;

	void PlacetInPosition();
};
