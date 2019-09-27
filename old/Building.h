#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"
#include "Camera.h"

class Building
{
public:
	Building(SharedContext* sharedContext, std::string textureFileName, sf::Vector2f position);
	virtual ~Building();

	void Update(float delta);
	void Render();

	SharedContext* GetSharedContext();

private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;
	sf::Texture* texture;
	sf::VertexArray vao;
	sf::RenderStates renderStates;
	sf::Transform transform;
	Camera* camera;
	std::string textureFileName;
	sf::Vector2f position;

	
};
