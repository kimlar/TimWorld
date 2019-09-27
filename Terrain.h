#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"
#include "Camera.h"

class Terrain
{
public:
	Terrain(SharedContext* sharedContext);
	virtual ~Terrain();

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
};
