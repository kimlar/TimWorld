#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"
#include "Camera.h"

class House
{
public:
	//House(SharedContext* sharedContext, std::string textureFileName, sf::Vector2f position, sf::Vector2i size);
	//House(SharedContext* sharedContext, std::string textureFileName, sf::Vector2f position);
	House(SharedContext* sharedContext, std::string objectFile, sf::Vector2f position);
	virtual ~House();

	void Update(float delta);
	void Render();

	// Pre render system
	void PreRenderClear();
	//void PreRenderAdd(sf::Vector2f position, sf::IntRect texRect);
	//void PreRenderAdd(sf::Vector2f position, std::string partName);
	void PreRenderAdd(sf::Vector2f position, int partNum);
	void PreRenderCompile();
	
	SharedContext* GetSharedContext();

private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;
	sf::RenderTexture* renderTexture;	
	Camera* camera;

	sf::Sprite houseSprite;
	sf::Texture* houseTexture;
	std::string textureFileName;
	sf::RenderStates renderStates;

	std::vector<sf::IntRect> parts;

	////////////////////////////////////////////////////////////////

	sf::Vector2i size;
	std::vector<sf::Vector3i> vArr;

	void LoadObjectFile(std::string filename);
};
