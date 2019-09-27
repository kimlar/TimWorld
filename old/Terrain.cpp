#include "Terrain.h"

Terrain::Terrain(SharedContext* sharedContext)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;
	this->camera = sharedContext->camera;

	textureFileName = "Terrain.png"; //textureFileName = "Assets/Images/Terrain.png";

	float quaW = 32;
	float quaH = 32;
	float texX = 0;
	float texY = 64;
	float texW = 32;
	float texH = 32;
	int mapW = 1920 / 32;
	int mapH = 1080 / 32;

	//float quaW = 64;
	//float quaH = 64;
	//float texX = 0;
	//float texY = 0;
	//float texW = 64;
	//float texH = 64;
	//int mapW = 1920 / 64;7
	//int mapH = 1080 / 64;
	int numQuads = 4 * mapW * mapH;
	int numCount = 0;
	vao.setPrimitiveType(sf::PrimitiveType::Quads);
	vao.resize(numQuads);
	for (int y = 0; y < mapH; y++)
	{
		for (int x = 0; x < mapW; x++)
		{
			vao[numCount + 0].position = sf::Vector2f(x * quaW, y * quaH);
			vao[numCount + 1].position = sf::Vector2f(x * quaW + quaW, y * quaH);
			vao[numCount + 2].position = sf::Vector2f(x * quaW + quaW, y * quaH + quaH);
			vao[numCount + 3].position = sf::Vector2f(x * quaW, y * quaH + quaH);
			vao[numCount + 0].texCoords = sf::Vector2f(texX, texY);
			vao[numCount + 1].texCoords = sf::Vector2f(texX + texW, texY);
			vao[numCount + 2].texCoords = sf::Vector2f(texX + texW, texY + texH);
			vao[numCount + 3].texCoords = sf::Vector2f(texX, texY + texH);
			numCount += 4;
		}
	}

	texture = sharedContext->GetResourceManager()->AcquireTexture(textureFileName);
	LogTest(!texture, "Terrain.cpp: Could not load texture: " + textureFileName);

	renderStates.texture = texture;
}

Terrain::~Terrain()
{
	GetSharedContext()->GetResourceManager()->ReleaseTexture(textureFileName);
}

void Terrain::Update(float delta)
{
	renderStates.transform = sf::Transform().translate(-camera->GetX(), -camera->GetY());
}

void Terrain::Render()
{
	renderWindow->draw(vao, renderStates);
}

SharedContext* Terrain::GetSharedContext()
{
	return sharedContext;
}
