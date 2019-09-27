#include "TestBox.h"

#include "ResourceManager.h"

TestBox::TestBox(SharedContext* sharedContext)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;

	textureFileName = "TestBox.png"; //textureFileName = "Assets/Images/TestBox.png";
	std::string shaderVertFile = "Assets/Shaders/Default.vert";
	std::string shaderFragFile = "Assets/Shaders/Default.frag";

	// Load texture
	texture = GetSharedContext()->GetResourceManager()->AcquireTexture(textureFileName);
	LogTest(!texture, "TestBox.cpp: Could not load texture: " + textureFileName);

	// Load shader
	bool shaderLoaded = shader.loadFromFile(shaderVertFile, shaderFragFile);
	LogTest(!shaderLoaded, "Shader not loaded");

	// This will allow us to acces the texture atlas image from the pixel shader.
	// Matches the 'uniform sampler2D tileGraphics;' line in the fragment shader.
	shader.setUniform("tex", *texture);

	// Set sprite
	sprite.setTexture(*texture);
	//sprite.setTextureRect(sf::IntRect(0, 0, 256 * 16, 256 * 16));
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);
	sprite.setPosition(0, 0);

	// Set render states
	renderStates.shader = &shader;
}

TestBox::~TestBox()
{
	GetSharedContext()->GetResourceManager()->ReleaseTexture(textureFileName);
}

void TestBox::Update(float delta)
{
	tpos += 0.1f * delta;
	if (tpos > 0.8f)
		tpos = 0.2f;
	sprite.setPosition(500 * cos(tpos), 500 * sin(tpos));
}

void TestBox::Render()
{
	renderWindow->draw(sprite, renderStates);
}

SharedContext* TestBox::GetSharedContext()
{
	return sharedContext;
}
