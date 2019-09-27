#include "Slider.h"

Slider::Slider(SharedContext* sharedContext, sf::Vector2f position, int value, SliderState state)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;

	this->position = position;
	this->size = sf::Vector2f(160, 24);
	//this->labelText = std::to_string(value);
	this->fontSize = 14;
	this->sliderState = state;

	//frame = new Frame(GetSharedContext(), sf::Vector2f(position.x, position.y), sf::Vector2f(size.x + 0, size.y + 0));
	frame = new Frame(GetSharedContext(), sf::Vector2f(position.x, position.y), sf::Vector2f(10, size.y + 0));
	//frame->SetPressedDown(true);

	if (sliderState == SliderState::Disabled)
		frame->SetButtonColor(sf::Color(100, 100, 100));
	else
		frame->SetButtonColor(sf::Color(191, 184, 191));

	label = new Label(GetSharedContext(), sf::Vector2f(position.x + 4 + 160, position.y - 1 + 4), std::to_string(value), fontSize);
	label->SetColor(sf::Color::Black);

	frameRail = new Frame(GetSharedContext(), sf::Vector2f(position.x, position.y + 12-2), sf::Vector2f(size.x + 0, 4));
	frameRail->SetPressedDown(true);

	SetValue(value);
}

Slider::~Slider()
{
	delete label;
	label = nullptr;

	delete frame;
	frame = nullptr;

	delete frameRail;
	frameRail = nullptr;
}

void Slider::CheckEvents(sf::Event &event)
{
	if (sliderState == SliderState::Disabled)
		return;

	int mx = GetSharedContext()->GetMouse()->mouseX;
	int my = GetSharedContext()->GetMouse()->mouseY;

	bool mouseInside = false;
	if (mx >= position.x && mx < (position.x + size.x))
		if (my >= position.y && my < (position.y + size.y))
			mouseInside = true;

	if (mouseInside && GetSharedContext()->GetMouse()->IsLeftDown())
		CalculateValue(mx - (int)position.x);
}

void Slider::Render()
{
	frameRail->Render();
	frame->Render();
	label->Render();

}

SharedContext* Slider::GetSharedContext()
{
	return sharedContext;
}

void Slider::SetValue(int value)
{
	this->sliderValue = value;

	if (value < sliderMin)
		value = sliderMin;
	else if (value > sliderMax)
		value = sliderMax;

	sliderValue = value;

	if(showAsPercent)
		label->SetText(std::to_string(value) + "%");
	else
		label->SetText(std::to_string(value));

	int sx = ((int)size.x * (sliderValue - sliderMin)) / (sliderMax - sliderMin + 1);
	frame->SetPosition(sf::Vector2f(sx + position.x - 5 + 1, position.y));
}

int Slider::GetValue()
{
	return sliderValue;
}

void Slider::SetMinValue(int value)
{
	this->sliderMin = value;
}

void Slider::SetMaxValue(int value)
{
	this->sliderMax = value;
}

void Slider::SetShowAsPercent(bool show)
{
	this->showAsPercent = show;
	SetValue(sliderValue);
}

void Slider::CalculateValue(int input)
{
	frame->SetPosition(sf::Vector2f(input + position.x - 5, position.y));

	sliderValue = (input) * (sliderMax - sliderMin + 1) / ((int)size.x) + sliderMin;

	if (showAsPercent)
		label->SetText(std::to_string(sliderValue) + "%");
	else
		label->SetText(std::to_string(sliderValue));
}

/*
void Slider::SetCheckBoxState(SliderState state)
{
this->sliderState = state;
}
*/
