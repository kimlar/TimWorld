#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"
struct SharedContext;

class Mouse
{
public:
	//Mouse(SharedContext* sharedContext, sf::Vector2f position, sf::Vector2f size);
	//Mouse(SharedContext* sharedContext);
	//virtual ~Mouse();

	//Mouse();
	Mouse(SharedContext* sharedContext, std::string filename);
	virtual ~Mouse();

	
	void CheckEvents(sf::Event &event);
	void Update(float delta);
	void Render();


	SharedContext* GetSharedContext();

	// Mouse
	int mouseX = 0; // TODO: Refactor
	int mouseY = 0;

	bool IsLeftDown();
	bool IsMiddleDown();
	bool IsRightDown();

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

	bool left;
	bool middle;
	bool right;
};