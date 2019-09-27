#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"

#include "Frame.h"
#include "Label.h"

class Slider
{
public:
	enum class SliderState { Normal, Disabled };

	Slider(SharedContext* sharedContext, sf::Vector2f position, int value, SliderState state = SliderState::Normal);
	virtual ~Slider();

	void CheckEvents(sf::Event &event);
	void Render();

	SharedContext* GetSharedContext();

	//void SetSliderState(SliderState state);
	void SetValue(int value);
	int GetValue();
	void SetMinValue(int value);
	void SetMaxValue(int value);

	void SetShowAsPercent(bool show);

private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;

	Frame* frame;
	Label* label;

	Frame* frameRail;

	sf::Vector2f position;
	sf::Vector2f size;
	//std::string labelText;
	int fontSize;

	SliderState sliderState = SliderState::Normal;

	int sliderValue = 0;
	int sliderMin = 0;
	int sliderMax = 100;

	bool showAsPercent;

	void CalculateValue(int input);
};
