#include "ComboBox.h"

//ComboBox::ComboBox(SharedContext* sharedContext, sf::Vector2f position, std::string text)
ComboBox::ComboBox(SharedContext * sharedContext, sf::Vector2f position, std::vector<std::string> texts)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;

	this->position = position;
	//this->size = sf::Vector2f(16, 16);
	this->size = sf::Vector2f(160, 24);
	//this->labelText = text;
	this->fontSize = 14;
	//this->checkBoxState = state;

	/*
	// Adding text to ComboBox
	listTexts.push_back("1920x1080");
	listTexts.push_back("1600x900");
	listTexts.push_back("1024x768");
	listTexts.push_back("800x600");
	*/
	listTexts = texts;


	frame = new Frame(GetSharedContext(), sf::Vector2f(position.x, position.y), sf::Vector2f(size.x + 0, size.y + 0));
	frame->SetPressedDown(true);

	if (comboBoxState == ComboBoxState::Disabled)
		frame->SetButtonColor(sf::Color(191, 191, 191));
	else
		frame->SetButtonColor(sf::Color(253, 253, 253));

	frameDropButton = new Frame(GetSharedContext(), sf::Vector2f(position.x + 140 - 2, position.y + 0 + 2), sf::Vector2f(20, 20));
	dropSymbol.setPointCount(3);
	dropSymbol.setPoint(0, sf::Vector2f(position.x + size.x - 20 + 3, position.y + 9));
	dropSymbol.setPoint(1, sf::Vector2f(position.x + size.x - 20 + 13, position.y + 9));
	dropSymbol.setPoint(2, sf::Vector2f(position.x + size.x - 20 + 8, position.y + 15));
	dropSymbol.setFillColor(sf::Color::Black);

	//label = new Label(GetSharedContext(), sf::Vector2f(position.x + 4, position.y - 1 + 4), text, fontSize);
	label = new Label(GetSharedContext(), sf::Vector2f(position.x + 4, position.y - 1 + 4), listTexts[0], fontSize);
	label->SetColor(sf::Color::Black);

	//frameList = new Frame(GetSharedContext(), sf::Vector2f(position.x, position.y + 24), sf::Vector2f(size.x + 0, size.y + 100));
	rectList.setPosition(sf::Vector2f(position.x, position.y + 24 + 1));
	rectList.setSize(sf::Vector2f(size.x, 100));
	rectList.setFillColor(sf::Color::White);
	rectList.setOutlineColor(sf::Color::Black);
	rectList.setOutlineThickness(1.0f);

	/*
	// Adding text to ComboBox
	listTexts.push_back("1920x1080");
	listTexts.push_back("1600x900");
	listTexts.push_back("1024x768");
	listTexts.push_back("800x600");
	*/

	rectList.setSize(sf::Vector2f(size.x, 20 * (float)listTexts.size()));

	for (int i = 0; i < listTexts.size(); i++)
	{
		sf::Vector2f pos = rectList.getPosition();
		pos.x += 4;
		pos.y += i * 20 + 1;
		listLabels.push_back(new Label(GetSharedContext(), pos, listTexts[i], fontSize));
		listLabels[i]->SetColor(sf::Color::Black);
	}
}

ComboBox::~ComboBox()
{
	delete label;
	label = nullptr;

	delete frame;
	frame = nullptr;

	delete frameDropButton;
	frameDropButton = nullptr;

	//delete frameList;
	//frameList = nullptr;

	listTexts.clear();

	for (int i = 0; i < listLabels.size(); i++)
	{
		delete listLabels[i];
		listLabels[i] = nullptr;
	}
	listLabels.clear();

}

bool ComboBox::CheckEvents(sf::Event &event)
{
	if (comboBoxState == ComboBoxState::Disabled)
		return false;

	int mx = GetSharedContext()->GetMouse()->mouseX;
	int my = GetSharedContext()->GetMouse()->mouseY;

	bool mouseInside = false;
	if (mx >= position.x && mx < (position.x + size.x))
		if (my >= position.y && my < (position.y + size.y))
			mouseInside = true;

	if (event.type == sf::Event::MouseButtonPressed && mouseInside)
	{
		if (comboBoxState == ComboBoxState::ShowList)
			comboBoxState = ComboBoxState::Normal;
		else
			comboBoxState = ComboBoxState::ShowList;
	}

	if (comboBoxState == ComboBoxState::ShowList)
	{
		frameDropButton->SetPressedDown(true);
		dropSymbol.setPoint(0, sf::Vector2f(position.x + size.x - 20 + 3 + 1, position.y + 9 + 1));
		dropSymbol.setPoint(1, sf::Vector2f(position.x + size.x - 20 + 13 + 1, position.y + 9 + 1));
		dropSymbol.setPoint(2, sf::Vector2f(position.x + size.x - 20 + 8 + 1, position.y + 15 + 1));
	}
	else
	{
		frameDropButton->SetPressedDown(false);
		dropSymbol.setPoint(0, sf::Vector2f(position.x + size.x - 20 + 3, position.y + 9));
		dropSymbol.setPoint(1, sf::Vector2f(position.x + size.x - 20 + 13, position.y + 9));
		dropSymbol.setPoint(2, sf::Vector2f(position.x + size.x - 20 + 8, position.y + 15));
	}

	if (comboBoxState == ComboBoxState::ShowList)
	{
		sf::Vector2f pos = rectList.getPosition();
		pos.x += 4;
		pos.y += 1; //pos.y += i * 20 + 1;
		
		bool mouseInsideList = false;
		if (mx >= rectList.getPosition().x && mx < (rectList.getPosition().x + rectList.getSize().x))
			if (my >= rectList.getPosition().y && my < (rectList.getPosition().y + rectList.getSize().y))
				mouseInsideList = true;

		if (event.type == sf::Event::MouseButtonPressed && !mouseInsideList && !mouseInside)
		{
			comboBoxState = ComboBoxState::Normal;

			frameDropButton->SetPressedDown(false);
			dropSymbol.setPoint(0, sf::Vector2f(position.x + size.x - 20 + 3, position.y + 9));
			dropSymbol.setPoint(1, sf::Vector2f(position.x + size.x - 20 + 13, position.y + 9));
			dropSymbol.setPoint(2, sf::Vector2f(position.x + size.x - 20 + 8, position.y + 15));
		}

		if(mouseInsideList)
			listSelectIndex = (my - (int)rectList.getPosition().y) / 20;

		if (event.type == sf::Event::MouseButtonPressed && mouseInsideList)
		{
			//labelText = listTexts[listSelectIndex];
			//label->SetText(labelText);
			label->SetText(listTexts[listSelectIndex]);
			comboBoxState = ComboBoxState::Normal;

			frameDropButton->SetPressedDown(false);
			dropSymbol.setPoint(0, sf::Vector2f(position.x + size.x - 20 + 3, position.y + 9));
			dropSymbol.setPoint(1, sf::Vector2f(position.x + size.x - 20 + 13, position.y + 9));
			dropSymbol.setPoint(2, sf::Vector2f(position.x + size.x - 20 + 8, position.y + 15));

			return true; // event handled
		}
	}

	return false;
}

void ComboBox::Render()
{
	frame->Render();
	label->Render();
	frameDropButton->Render();
	renderWindow->draw(dropSymbol);
}

void ComboBox::RenderPost()
{
	if (comboBoxState == ComboBoxState::ShowList)
	{
		//frameList->Render();
		renderWindow->draw(rectList);

		for (int i = 0; i < listLabels.size(); i++)
		{
			if (listSelectIndex == i)
			{
				sf::Vector2f pos = rectList.getPosition();
				pos.x += 0; //4;
				pos.y += i * 20;

				sf::RectangleShape selectShape;
				selectShape.setPosition(pos);
				selectShape.setSize(sf::Vector2f(160, 20));
				selectShape.setFillColor(sf::Color(30, 66, 130));
				renderWindow->draw(selectShape);

				listLabels[i]->SetColor(sf::Color::White);
				listLabels[i]->Render();
				listLabels[i]->SetColor(sf::Color::Black);
			}
			else
			{
				listLabels[i]->Render();
			}
		}
	}
}

SharedContext* ComboBox::GetSharedContext()
{
	return sharedContext;
}

void ComboBox::SetSelectedIndex(int index)
{
	if (index >= 0 && index < listTexts.size())
	{
		listSelectIndex = index;
		label->SetText(listTexts[index]);
	}
}

int ComboBox::GetSelectedIndex()
{
	return listSelectIndex;
}

std::string ComboBox::GetSelectedText()
{
	return label->GetText();
}

int ComboBox::GetIndexByText(std::string text)
{
	for (int i = 0; i < listTexts.size(); i++)
	{
		if (listTexts[i] == text)
			return i;
	}
	return -1; // Not found
}

/*
void ComboBox::SetCheckBoxState(ComboBoxState state)
{
	this->comboBoxState = state;
}
*/
