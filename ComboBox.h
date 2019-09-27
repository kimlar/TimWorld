#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"

#include "Frame.h"
#include "Label.h"

class ComboBox
{
public:
	enum class ComboBoxState { Normal, ShowList, Disabled };

	//ComboBox(SharedContext* sharedContext, sf::Vector2f position, std::string text);
	ComboBox(SharedContext* sharedContext, sf::Vector2f position, std::vector<std::string> texts);
	virtual ~ComboBox();

	bool CheckEvents(sf::Event &event);
	void Render();
	void RenderPost();

	SharedContext* GetSharedContext();

	//void SetComboBoxState(ComboBoxState state);

	void SetSelectedIndex(int index);
	int GetSelectedIndex();
	std::string GetSelectedText();

	int GetIndexByText(std::string text);
	
private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;

	Frame* frame;
	Label* label;

	Frame* frameDropButton;
	sf::ConvexShape dropSymbol;

	sf::RectangleShape rectList;
	//Frame* frameList;

	sf::Vector2f position;
	sf::Vector2f size;
//	std::string labelText;
	int fontSize;

	ComboBoxState comboBoxState = ComboBoxState::Normal;

	std::vector<std::string> listTexts;
	std::vector<Label*> listLabels;

	int listSelectIndex = 0;
};
