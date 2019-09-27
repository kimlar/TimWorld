#include "Dialog.h"

Dialog::Dialog(SharedContext* sharedContext, sf::Vector2f position, sf::Vector2f size, std::string title, int fontSize, sf::Color frameColor, sf::Color textColor)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;

	this->position = position;
	this->size = size;
	this->title = title;
	this->fontSize = fontSize;

	label = new Label(GetSharedContext(), sf::Vector2f(position.x - 50, position.y - 100), title, fontSize);
	label->SetColor(textColor);

	frame = new Frame(GetSharedContext(), sf::Vector2f(position.x - 70, position.y - 100), sf::Vector2f(size.x + 140, size.y + 200));
	frame->SetButtonColor(frameColor);
}

Dialog::~Dialog()
{
	delete label;
	label = nullptr;

	delete frame;
	frame = nullptr;
}

void Dialog::Render()
{
	//renderWindow->draw(text);

	frame->Render();

	label->Render();
}

SharedContext* Dialog::GetSharedContext()
{
	return sharedContext;
}

void Dialog::SetPosition(sf::Vector2f position)
{
	this->position = position;
}
