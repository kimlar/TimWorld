#include "Mouse.h"

#include "ResourceManager.h"

Mouse::Mouse(SharedContext* sharedContext, std::string filename)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;
	this->textureFileName = filename;

	this->position = sf::Vector2f(0, 0);
	this->size = sf::Vector2f(24, 24);

	vao.setPrimitiveType(sf::PrimitiveType::Quads);
	int numCursors = 1;	
	vao.resize(numCursors * 4);
	
	float w = size.x;
	float h = size.y;
	int numCount = 0;
	vao[numCount + 0].position = sf::Vector2f(0, 0);
	vao[numCount + 1].position = sf::Vector2f(w, 0);
	vao[numCount + 2].position = sf::Vector2f(w, h);
	vao[numCount + 3].position = sf::Vector2f(0, h);
	vao[numCount + 0].texCoords = sf::Vector2f(0, 0);
	vao[numCount + 1].texCoords = sf::Vector2f(w, 0);
	vao[numCount + 2].texCoords = sf::Vector2f(w, h);
	vao[numCount + 3].texCoords = sf::Vector2f(0, h);


	texture = sharedContext->GetResourceManager()->AcquireTexture(textureFileName);
	LogTest(!texture, "Mouse.cpp: Could not load texture: " + textureFileName);

	renderStates.texture = texture;
}

Mouse::~Mouse()
{
	GetSharedContext()->GetResourceManager()->ReleaseTexture(textureFileName);
}

void Mouse::CheckEvents(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			left = true;
		else if (event.mouseButton.button == sf::Mouse::Right)
			right = true;
		else if (event.mouseButton.button == sf::Mouse::Middle)
			middle = true;

		return;
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			left = false;
		else if (event.mouseButton.button == sf::Mouse::Right)
			right = false;
		else if (event.mouseButton.button == sf::Mouse::Middle)
			middle = false;

		return;
	}

	if (event.type == sf::Event::MouseMoved)
	{
		mouseX = event.mouseMove.x;
		mouseY = event.mouseMove.y;


		vao[0].position = sf::Vector2f((float)mouseX, (float)mouseY);
		vao[1].position = sf::Vector2f((float)mouseX + size.x, (float)mouseY);
		vao[2].position = sf::Vector2f((float)mouseX + size.x, (float)mouseY + size.y);
		vao[3].position = sf::Vector2f((float)mouseX, (float)mouseY + size.y);
		return;
	}
}

void Mouse::Update(float delta)
{

}

void Mouse::Render()
{
	renderWindow->draw(vao, renderStates);
}

SharedContext* Mouse::GetSharedContext()
{
	return sharedContext;
}

bool Mouse::IsLeftDown()
{
	return left;
}

bool Mouse::IsMiddleDown()
{
	return middle;
}

bool Mouse::IsRightDown()
{
	return right;
}
