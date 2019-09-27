#include "Building.h"

Building::Building(SharedContext* sharedContext, std::string textureFileName, sf::Vector2f position)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;
	this->camera = sharedContext->camera;
	this->textureFileName = textureFileName;
	this->position = position;


	float x = position.x;
	float y = position.y;
	float w = 32;
	float h = 32;
	float texX = 0;
	float texY = 0;
	float texW = 32;
	float texH = 32;

	enum PartType { Corner = 0, HWallTop, VWallTop, Floor, HCorner, HWall };
	
	struct TextureCoords
	{
		float x;
		float y;
		float w;
		float h;
	};
	std::vector<TextureCoords> texCoords;
	texCoords.push_back(TextureCoords{ 0, 0, 32, 32 });		// Corner
	texCoords.push_back(TextureCoords{ 32, 0, 32, 32 });	// HWallTop
	texCoords.push_back(TextureCoords{ 64, 0, 32, 32 });	// VWallTop
	texCoords.push_back(TextureCoords{ 128, 0, 32, 32 });	// Floor
	texCoords.push_back(TextureCoords{ 0, 32, 32, 32 });	// HCorner
	texCoords.push_back(TextureCoords{ 32, 32, 32, 32 });	// HWall
	//texCoords.push_back(TextureCoords{ 128, 32, 32, 32 });	//

	struct Parts
	{
		float x;
		float y;
		float w;
		float h;
		PartType type;
	};
	std::vector<Parts> parts;
	//
	parts.push_back(Parts{ x, y, 32, 32, PartType::Corner });
	parts.push_back(Parts{ x + 32, y, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 64, y, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 96, y, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 128, y, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 160, y, 32, 32, PartType::Corner });
	parts.push_back(Parts{ x + 192, y, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 224, y, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 256, y, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 288, y, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 320, y, 32, 32, PartType::Corner });
	//
	parts.push_back(Parts{ x, y + 32, 32, 32, PartType::VWallTop });
	parts.push_back(Parts{ x + 32, y + 32, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 64, y + 32, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 96, y + 32, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 128, y + 32, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 160, y + 32, 32, 32, PartType::HCorner });
	parts.push_back(Parts{ x + 192, y + 32, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 224, y + 32, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 256, y + 32, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 288, y + 32, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 320, y + 32, 32, 32, PartType::VWallTop });
	//
	parts.push_back(Parts{ x, y + 64, 32, 32, PartType::VWallTop });
	parts.push_back(Parts{ x + 32, y + 64, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 64, y + 64, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 96, y + 64, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 128, y + 64, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 160, y + 64, 32, 32, PartType::HCorner });
	parts.push_back(Parts{ x + 192, y + 64, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 224, y + 64, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 256, y + 64, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 288, y + 64, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 320, y + 64, 32, 32, PartType::VWallTop });
	//
	parts.push_back(Parts{ x, y + 96, 32, 32, PartType::VWallTop });
	parts.push_back(Parts{ x + 32, y + 96, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 64, y + 96, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 96, y + 96, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 128, y + 96, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 160, y + 96, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 192, y + 96, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 224, y + 96, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 256, y + 96, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 288, y + 96, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 320, y + 96, 32, 32, PartType::VWallTop });
	//
	parts.push_back(Parts{ x, y + 128, 32, 32, PartType::VWallTop });
	parts.push_back(Parts{ x + 32, y + 128, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 64, y + 128, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 96, y + 128, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 128, y + 128, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 160, y + 128, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 192, y + 128, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 224, y + 128, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 256, y + 128, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 288, y + 128, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 320, y + 128, 32, 32, PartType::VWallTop });
	//
	parts.push_back(Parts{ x, y + 160, 32, 32, PartType::Corner });
	parts.push_back(Parts{ x + 32, y + 160, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 64, y + 160, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 96, y + 160, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 128, y + 160, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 160, y + 160, 32, 32, PartType::Corner });
	parts.push_back(Parts{ x + 192, y + 160, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 224, y + 160, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 256, y + 160, 32, 32, PartType::Corner });
	parts.push_back(Parts{ x + 288, y + 160, 32, 32, PartType::HWallTop });
	parts.push_back(Parts{ x + 320, y + 160, 32, 32, PartType::Corner });
	//
	parts.push_back(Parts{ x, y + 192, 32, 32, PartType::HCorner });
	parts.push_back(Parts{ x + 32, y + 192, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 64, y + 192, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 96, y + 192, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 128, y + 192, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 160, y + 192, 32, 32, PartType::HCorner });
	parts.push_back(Parts{ x + 192, y + 192, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 224, y + 192, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 256, y + 192, 32, 32, PartType::HCorner });
	parts.push_back(Parts{ x + 288, y + 192, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 320, y + 192, 32, 32, PartType::HCorner });
	//
	parts.push_back(Parts{ x, y + 224, 32, 32, PartType::HCorner });
	parts.push_back(Parts{ x + 32, y + 224, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 64, y + 224, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 96, y + 224, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 128, y + 224, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 160, y + 224, 32, 32, PartType::HCorner });
	parts.push_back(Parts{ x + 192, y + 224, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 224, y + 224, 32, 32, PartType::Floor });
	parts.push_back(Parts{ x + 256, y + 224, 32, 32, PartType::HCorner });
	parts.push_back(Parts{ x + 288, y + 224, 32, 32, PartType::HWall });
	parts.push_back(Parts{ x + 320, y + 224, 32, 32, PartType::HCorner });



	int numQuads = (int)parts.size();
	vao.setPrimitiveType(sf::PrimitiveType::Quads);
	vao.resize(numQuads * 4);

	int curQuad = 0;
	float cx = 0;
	float cy = 0;
	int curPart = PartType::Corner;

	int iv = 0;
	for (int i = 0; i < numQuads; i++)
	{
		vao[iv] = { sf::Vector2f(parts[i].x, parts[i].y), sf::Vector2f(texCoords[parts[i].type].x,  texCoords[parts[i].type].y) };
		vao[iv+1] = { sf::Vector2f(parts[i].x + parts[i].w, parts[i].y), sf::Vector2f(texCoords[parts[i].type].x + texCoords[parts[i].type].w,  texCoords[parts[i].type].y) };
		vao[iv+2] = { sf::Vector2f(parts[i].x + parts[i].w, parts[i].y + parts[i].h), sf::Vector2f(texCoords[parts[i].type].x + texCoords[parts[i].type].w,  texCoords[parts[i].type].y + texCoords[parts[i].type].h) };
		vao[iv+3] = { sf::Vector2f(parts[i].x, parts[i].y + parts[i].h), sf::Vector2f(texCoords[parts[i].type].x,  texCoords[parts[i].type].y + texCoords[parts[i].type].h) };
		iv += 4;
	}

	texture = sharedContext->GetResourceManager()->AcquireTexture(textureFileName);
	LogTest(!texture, "Building.cpp: Could not load texture: " + textureFileName);

	renderStates.texture = texture;
}

Building::~Building()
{
	GetSharedContext()->GetResourceManager()->ReleaseTexture(textureFileName);
}

void Building::Update(float delta)
{
	renderStates.transform = sf::Transform().translate(-camera->GetX(), -camera->GetY());
}

void Building::Render()
{
	renderWindow->draw(vao, renderStates);
}

SharedContext* Building::GetSharedContext()
{
	return sharedContext;
}
