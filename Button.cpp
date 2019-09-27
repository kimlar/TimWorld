#include "Button.h"

Button::Button(SharedContext* sharedContext, sf::Rect<int> rect, std::string text, int fontSize)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;
	this->buttonRect = rect;
	this->buttonText = text;
	this->fontSize = fontSize;

	colorRelease = sf::Color(191, 184, 191);
	colorPressed = sf::Color(175, 168, 175);
	colorHovered = sf::Color(207, 200, 207);
	colorText = sf::Color(0, 0, 0);

	frame = new Frame(GetSharedContext(), sf::Vector2f((float)buttonRect.left, (float)buttonRect.top), sf::Vector2f((float)buttonRect.width, (float)buttonRect.height));
	frame->SetButtonColor(colorRelease);
	
	font = GetSharedContext()->GetResourceManager()->AcquireFont("OpenSans-SemiBold.ttf");
	this->text.setFont(*font);
	this->text.setCharacterSize(fontSize);
	this->text.setFillColor(colorText);
	//this->text.setStyle(sf::Text::Style::Bold);
	this->text.setString(text);

	textHeightAdjustment = GetTextHeightAdjustment(); // Note!

	int tx = buttonRect.left + buttonRect.width / 2 - ((int)this->text.getLocalBounds().width) / 2 - (int)this->text.getLocalBounds().left - 1;
	int ty = buttonRect.top + buttonRect.height / 2 - textHeightAdjustment;

	this->text.setPosition((float)tx, (float)ty);

	textHomePosition.x = tx;
	textHomePosition.y = ty;
}

Button::~Button()
{
	delete frame;
	frame = nullptr;
}

Button::ButtonAction Button::CheckEvents(sf::Event &event)
{
	int mx = GetSharedContext()->GetMouse()->mouseX;
	int my = GetSharedContext()->GetMouse()->mouseY;

	mouseInside = false;
	if (mx >= buttonRect.left && mx < (buttonRect.left + buttonRect.width))
		if (my >= buttonRect.top && my < (buttonRect.top + buttonRect.height))
			mouseInside = true;

	if (event.type == sf::Event::MouseButtonReleased && mouseInside)
	{
		if (pressedDownInside)
		{
			pressedDownInside = false; // reseting
			return ButtonAction::LeftClicked;
		}
	}
	
	if (event.type == sf::Event::MouseButtonReleased || !mouseInside)
	{
		buttonDown = false;
	}
	if (event.type == sf::Event::MouseButtonPressed && mouseInside)
	{
		buttonDown = true;
	}
	
	if (mouseInside && buttonDown)
	{
		pressedDownInside = true;
		buttonState = ButtonState::Pressed;
		frame->SetButtonColor(colorPressed);
		SetButtonDown(true);
		text.setPosition((float)textHomePosition.x + 2, (float)textHomePosition.y + 2);
	}
	else if (mouseInside)
	{
		buttonState = ButtonState::Hovered;
		frame->SetButtonColor(colorHovered);
		SetButtonDown(false);
		text.setPosition((float)textHomePosition.x, (float)textHomePosition.y);
	}
	else
	{
		buttonState = ButtonState::Released;
		frame->SetButtonColor(colorRelease);
		SetButtonDown(false);
		text.setPosition((float)textHomePosition.x, (float)textHomePosition.y);
	}

	return ButtonAction::Idle;
}

void Button::Render()
{	
	frame->Render();
	renderWindow->draw(text);
}

SharedContext* Button::GetSharedContext()
{
	return sharedContext;
}

void Button::SetButtonColor(sf::Color color)
{
	this->colorRelease = color;
}

void Button::ResetButtonColor()
{
	colorRelease = sf::Color(191, 184, 191); //released
}

/*
void Button::SetPressedDown(bool down)
{
	frame->SetPressedDown(down);
}
*/

void Button::ResetEvent()
{
	buttonDown = false;
	buttonState = ButtonState::Released;
	frame->SetButtonColor(colorRelease);
	SetButtonDown(false);
	text.setPosition((float)textHomePosition.x, (float)textHomePosition.y);

	/*
	buttonDown = false;
	buttonState = ButtonState::Hovered;
	frame->SetButtonColor(colorHovered);
	SetButtonDown(false);
	text.setPosition((float)textHomePosition.x, (float)textHomePosition.y);
	*/
}

//
// NOTE: This function must only be called at setup (before using text dimensions)
//		 Or when text size is changed.
//
int Button::GetTextHeightAdjustment()
{
	int heightAdj = 0;
	std::string tempStr = text.getString();

	text.setString("Ay");
	heightAdj = (int)text.getLocalBounds().height / 2 + (int)text.getLocalBounds().top / 2;
	text.setString(tempStr);

	return heightAdj;
}

void Button::SetButtonDown(bool down)
{
	frame->SetPressedDown(down);
}
