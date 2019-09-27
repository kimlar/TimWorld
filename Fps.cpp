#include "Fps.h"

Fps::Fps(SharedContext* sharedContext)
{
	this->sharedContext = sharedContext;
	renderWindow = sharedContext->GetRenderWindow();
	font = sharedContext->GetResourceManager()->AcquireFont("OpenSans-Regular.ttf");
	fpsText.setFont(*font);

	position = sf::Vector2f((float)sharedContext->GetRenderWindow()->getSize().x - 160, 0);
	fpsText.setPosition(position);
}

Fps::~Fps()
{
}

void Fps::Update(float delta)
{
	if (!active)
		return;

	fpsTime += delta;
	fpsCount++;
	if (fpsTime >= 1.0f)
	{
		fpsTime = 0.0f;
		fps = fpsCount;
		fpsCount = 0;
	}
	fpsText.setString(sf::String("FPS: " + sf::String(std::to_string(fps))));
}

void Fps::Render()
{
	if (!active)
		return;

	renderWindow->draw(fpsText);
}
