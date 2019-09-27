#include "Label.h"

Label::Label(SharedContext* sharedContext, sf::Vector2f position, std::string text, int fontSize)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;

	//color = sf::Color(255, 248, 255);
	color = sf::Color::Black;

	font = GetSharedContext()->GetResourceManager()->AcquireFont("OpenSans-SemiBold.ttf");
	this->text.setFont(*font);
	this->text.setPosition(position);
	this->text.setString(text);
	this->text.setCharacterSize(fontSize);
	this->text.setFillColor(color);
	//this->text.setStyle(sf::Text::Style::Bold);
}

Label::~Label()
{
}

void Label::Render()
{
	renderWindow->draw(text);
}

SharedContext* Label::GetSharedContext()
{
	return sharedContext;
}

/*
void Label::SetPosition(sf::Vector2f position)
{
	this->text.setPosition(position);
}
*/

void Label::SetColor(sf::Color color)
{
	this->text.setFillColor(color);
}

void Label::SetText(std::string text)
{
	this->text.setString(text);
}

std::string Label::GetText()
{
	return text.getString();
}

int Label::GetTextWidth()
{
	return (int)text.getLocalBounds().width;
}

int Label::GetWidthOfPartText(int location)
{
	if (location >= 0 && location < text.getString().getSize() + 1)
	{
		std::string strTemp = text.getString();
		//text.setString(strTemp[location]);
		text.setString(strTemp.substr(0, location));
		int width = (int)text.getLocalBounds().width;
		text.setString(strTemp);
		return width;
	}
	return -1; // Indicate error
}
