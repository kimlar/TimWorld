#include "Frame.h"

#include "ResourceManager.h"

Frame::Frame(SharedContext* sharedContext, sf::Vector2f position, sf::Vector2f size)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;
	this->position = position;
	this->size = size;

	textureFileName = "Frame.png"; //textureFileName = "Assets/Images/Frame.png";

	vao.setPrimitiveType(sf::PrimitiveType::Quads);
	vao.resize(9 * 4);

	PlacetInPosition();

	/*
	int numCount = 0;

	float x = this->position.x;
	float y = this->position.y;
	float w = this->size.x;
	float h = this->size.y;

	// Upper left corner
	numCount = 0 * 4;
	vao[numCount + 0].position = sf::Vector2f(x, y);
	vao[numCount + 1].position = sf::Vector2f(x + 2, y);
	vao[numCount + 2].position = sf::Vector2f(x + 2, y + 2);
	vao[numCount + 3].position = sf::Vector2f(x, y + 2);
	vao[numCount + 0].texCoords = sf::Vector2f(0, 0);
	vao[numCount + 1].texCoords = sf::Vector2f(2, 0);
	vao[numCount + 2].texCoords = sf::Vector2f(2, 2);
	vao[numCount + 3].texCoords = sf::Vector2f(0, 2);

	// Top
	numCount = 1 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + 2, y);
	vao[numCount + 1].position = sf::Vector2f(x + w, y);
	vao[numCount + 2].position = sf::Vector2f(x + w, y + 2);
	vao[numCount + 3].position = sf::Vector2f(x + 2, y + 2);
	vao[numCount + 0].texCoords = sf::Vector2f(2, 0);
	vao[numCount + 1].texCoords = sf::Vector2f(4, 0);
	vao[numCount + 2].texCoords = sf::Vector2f(4, 2);
	vao[numCount + 3].texCoords = sf::Vector2f(2, 2);

	// Upper right corner
	numCount = 2 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + w - 2, y);
	vao[numCount + 1].position = sf::Vector2f(x + w, y);
	vao[numCount + 2].position = sf::Vector2f(x + w, y + 2);
	vao[numCount + 3].position = sf::Vector2f(x + w - 2, y + 2);
	vao[numCount + 0].texCoords = sf::Vector2f(4, 0);
	vao[numCount + 1].texCoords = sf::Vector2f(6, 0);
	vao[numCount + 2].texCoords = sf::Vector2f(6, 2);
	vao[numCount + 3].texCoords = sf::Vector2f(4, 2);

	// Left
	numCount = 3 * 4;
	vao[numCount + 0].position = sf::Vector2f(x, y + 2);
	vao[numCount + 1].position = sf::Vector2f(x + 2, y + 2);
	vao[numCount + 2].position = sf::Vector2f(x + 2, y + h - 2);
	vao[numCount + 3].position = sf::Vector2f(x, y + h - 2);
	vao[numCount + 0].texCoords = sf::Vector2f(0, 2);
	vao[numCount + 1].texCoords = sf::Vector2f(2, 2);
	vao[numCount + 2].texCoords = sf::Vector2f(2, 4);
	vao[numCount + 3].texCoords = sf::Vector2f(0, 4);

	// Center
	numCount = 4 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + 2, y + 2);
	vao[numCount + 1].position = sf::Vector2f(x + w - 2, y + 2);
	vao[numCount + 2].position = sf::Vector2f(x + w - 2, y + h - 2);
	vao[numCount + 3].position = sf::Vector2f(x + 2, y + h - 2);
	vao[numCount + 0].texCoords = sf::Vector2f(2, 2);
	vao[numCount + 1].texCoords = sf::Vector2f(4, 2);
	vao[numCount + 2].texCoords = sf::Vector2f(4, 4);
	vao[numCount + 3].texCoords = sf::Vector2f(2, 4);

	// Right
	numCount = 5 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + w - 2, y + 2);
	vao[numCount + 1].position = sf::Vector2f(x + w, y + 2);
	vao[numCount + 2].position = sf::Vector2f(x + w, y + h - 2);
	vao[numCount + 3].position = sf::Vector2f(x + w - 2, y + h - 2);
	vao[numCount + 0].texCoords = sf::Vector2f(4, 2);
	vao[numCount + 1].texCoords = sf::Vector2f(6, 2);
	vao[numCount + 2].texCoords = sf::Vector2f(6, 4);
	vao[numCount + 3].texCoords = sf::Vector2f(4, 4);

	// Lower left corner
	numCount = 6 * 4;
	vao[numCount + 0].position = sf::Vector2f(x, y + h - 2);
	vao[numCount + 1].position = sf::Vector2f(x + 2, y + h - 2);
	vao[numCount + 2].position = sf::Vector2f(x + 2, y + h);
	vao[numCount + 3].position = sf::Vector2f(x, y + h);
	vao[numCount + 0].texCoords = sf::Vector2f(0, 4);
	vao[numCount + 1].texCoords = sf::Vector2f(2, 4);
	vao[numCount + 2].texCoords = sf::Vector2f(2, 6);
	vao[numCount + 3].texCoords = sf::Vector2f(0, 6);

	// Bottom
	numCount = 7 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + 2, y + h - 2);
	vao[numCount + 1].position = sf::Vector2f(x + w - 2, y + h - 2);
	vao[numCount + 2].position = sf::Vector2f(x + w - 2, y + h);
	vao[numCount + 3].position = sf::Vector2f(x + 2, y + h);
	vao[numCount + 0].texCoords = sf::Vector2f(2, 4);
	vao[numCount + 1].texCoords = sf::Vector2f(4, 4);
	vao[numCount + 2].texCoords = sf::Vector2f(4, 6);
	vao[numCount + 3].texCoords = sf::Vector2f(2, 6);

	// Lower right corner
	numCount = 8 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + w - 2, y + h - 2);
	vao[numCount + 1].position = sf::Vector2f(x + w, y + h - 2);
	vao[numCount + 2].position = sf::Vector2f(x + w, y + h);
	vao[numCount + 3].position = sf::Vector2f(x + w - 2, y + h);
	vao[numCount + 0].texCoords = sf::Vector2f(4, 4);
	vao[numCount + 1].texCoords = sf::Vector2f(6, 4);
	vao[numCount + 2].texCoords = sf::Vector2f(6, 6);
	vao[numCount + 3].texCoords = sf::Vector2f(4, 6);
	*/


	texture = sharedContext->GetResourceManager()->AcquireTexture(textureFileName);
	LogTest(!texture, "Frame.cpp: Could not load texture: " + textureFileName);

	renderStates.texture = texture;

	SetButtonColor(sf::Color(191, 184, 191)); // Default button color
}

Frame::~Frame()
{
	GetSharedContext()->GetResourceManager()->ReleaseTexture(textureFileName);
}

void Frame::Update(float delta)
{
	//renderStates.transform = sf::Transform().translate(0, 0);
}

void Frame::Render()
{
	renderWindow->draw(vao, renderStates);
}

SharedContext* Frame::GetSharedContext()
{
	return sharedContext;
}

void Frame::SetPressedDown(bool down)
{
	if (isPressedDown != down)
		renderStates.transform.rotate(180, position.x + size.x / 2, position.y + size.y / 2);

	isPressedDown = down;
}
void Frame::SetButtonColor(sf::Color color)
{
	vao[16].color = color;
	vao[17].color = color;
	vao[18].color = color;
	vao[19].color = color;
}

void Frame::SetPosition(sf::Vector2f position)
{
	this->position = position;
	PlacetInPosition();
}

void Frame::PlacetInPosition()
{
	int numCount = 0;

	float x = this->position.x;
	float y = this->position.y;
	float w = this->size.x;
	float h = this->size.y;

	// Upper left corner
	numCount = 0 * 4;
	vao[numCount + 0].position = sf::Vector2f(x, y);
	vao[numCount + 1].position = sf::Vector2f(x + 2, y);
	vao[numCount + 2].position = sf::Vector2f(x + 2, y + 2);
	vao[numCount + 3].position = sf::Vector2f(x, y + 2);
	vao[numCount + 0].texCoords = sf::Vector2f(0, 0);
	vao[numCount + 1].texCoords = sf::Vector2f(2, 0);
	vao[numCount + 2].texCoords = sf::Vector2f(2, 2);
	vao[numCount + 3].texCoords = sf::Vector2f(0, 2);

	// Top
	numCount = 1 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + 2, y);
	vao[numCount + 1].position = sf::Vector2f(x + w, y);
	vao[numCount + 2].position = sf::Vector2f(x + w, y + 2);
	vao[numCount + 3].position = sf::Vector2f(x + 2, y + 2);
	vao[numCount + 0].texCoords = sf::Vector2f(2, 0);
	vao[numCount + 1].texCoords = sf::Vector2f(4, 0);
	vao[numCount + 2].texCoords = sf::Vector2f(4, 2);
	vao[numCount + 3].texCoords = sf::Vector2f(2, 2);

	// Upper right corner
	numCount = 2 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + w - 2, y);
	vao[numCount + 1].position = sf::Vector2f(x + w, y);
	vao[numCount + 2].position = sf::Vector2f(x + w, y + 2);
	vao[numCount + 3].position = sf::Vector2f(x + w - 2, y + 2);
	vao[numCount + 0].texCoords = sf::Vector2f(4, 0);
	vao[numCount + 1].texCoords = sf::Vector2f(6, 0);
	vao[numCount + 2].texCoords = sf::Vector2f(6, 2);
	vao[numCount + 3].texCoords = sf::Vector2f(4, 2);

	// Left
	numCount = 3 * 4;
	vao[numCount + 0].position = sf::Vector2f(x, y + 2);
	vao[numCount + 1].position = sf::Vector2f(x + 2, y + 2);
	vao[numCount + 2].position = sf::Vector2f(x + 2, y + h - 2);
	vao[numCount + 3].position = sf::Vector2f(x, y + h - 2);
	vao[numCount + 0].texCoords = sf::Vector2f(0, 2);
	vao[numCount + 1].texCoords = sf::Vector2f(2, 2);
	vao[numCount + 2].texCoords = sf::Vector2f(2, 4);
	vao[numCount + 3].texCoords = sf::Vector2f(0, 4);

	// Center
	numCount = 4 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + 2, y + 2);
	vao[numCount + 1].position = sf::Vector2f(x + w - 2, y + 2);
	vao[numCount + 2].position = sf::Vector2f(x + w - 2, y + h - 2);
	vao[numCount + 3].position = sf::Vector2f(x + 2, y + h - 2);
	vao[numCount + 0].texCoords = sf::Vector2f(2, 2);
	vao[numCount + 1].texCoords = sf::Vector2f(4, 2);
	vao[numCount + 2].texCoords = sf::Vector2f(4, 4);
	vao[numCount + 3].texCoords = sf::Vector2f(2, 4);

	// Right
	numCount = 5 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + w - 2, y + 2);
	vao[numCount + 1].position = sf::Vector2f(x + w, y + 2);
	vao[numCount + 2].position = sf::Vector2f(x + w, y + h - 2);
	vao[numCount + 3].position = sf::Vector2f(x + w - 2, y + h - 2);
	vao[numCount + 0].texCoords = sf::Vector2f(4, 2);
	vao[numCount + 1].texCoords = sf::Vector2f(6, 2);
	vao[numCount + 2].texCoords = sf::Vector2f(6, 4);
	vao[numCount + 3].texCoords = sf::Vector2f(4, 4);

	// Lower left corner
	numCount = 6 * 4;
	vao[numCount + 0].position = sf::Vector2f(x, y + h - 2);
	vao[numCount + 1].position = sf::Vector2f(x + 2, y + h - 2);
	vao[numCount + 2].position = sf::Vector2f(x + 2, y + h);
	vao[numCount + 3].position = sf::Vector2f(x, y + h);
	vao[numCount + 0].texCoords = sf::Vector2f(0, 4);
	vao[numCount + 1].texCoords = sf::Vector2f(2, 4);
	vao[numCount + 2].texCoords = sf::Vector2f(2, 6);
	vao[numCount + 3].texCoords = sf::Vector2f(0, 6);

	// Bottom
	numCount = 7 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + 2, y + h - 2);
	vao[numCount + 1].position = sf::Vector2f(x + w - 2, y + h - 2);
	vao[numCount + 2].position = sf::Vector2f(x + w - 2, y + h);
	vao[numCount + 3].position = sf::Vector2f(x + 2, y + h);
	vao[numCount + 0].texCoords = sf::Vector2f(2, 4);
	vao[numCount + 1].texCoords = sf::Vector2f(4, 4);
	vao[numCount + 2].texCoords = sf::Vector2f(4, 6);
	vao[numCount + 3].texCoords = sf::Vector2f(2, 6);

	// Lower right corner
	numCount = 8 * 4;
	vao[numCount + 0].position = sf::Vector2f(x + w - 2, y + h - 2);
	vao[numCount + 1].position = sf::Vector2f(x + w, y + h - 2);
	vao[numCount + 2].position = sf::Vector2f(x + w, y + h);
	vao[numCount + 3].position = sf::Vector2f(x + w - 2, y + h);
	vao[numCount + 0].texCoords = sf::Vector2f(4, 4);
	vao[numCount + 1].texCoords = sf::Vector2f(6, 4);
	vao[numCount + 2].texCoords = sf::Vector2f(6, 6);
	vao[numCount + 3].texCoords = sf::Vector2f(4, 6);
}
