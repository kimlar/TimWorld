#include "EditBox.h"

EditBox::EditBox(SharedContext* sharedContext, sf::Vector2f position, std::string text, EditBoxState state)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;

	this->position = position;
	//this->size = sf::Vector2f(16, 16);
	this->size = sf::Vector2f(160, 24);
	//this->labelText = text;
	this->fontSize = 14;
	this->editBoxState = state;

	frame = new Frame(GetSharedContext(), sf::Vector2f(position.x, position.y), sf::Vector2f(size.x + 0, size.y + 0));
	frame->SetPressedDown(true);

	if (editBoxState == EditBoxState::Disabled)
		frame->SetButtonColor(sf::Color(191, 191, 191));
	else
		frame->SetButtonColor(sf::Color(253, 253, 253));

	label = new Label(GetSharedContext(), sf::Vector2f(position.x + 4, position.y - 1 + 4), text, fontSize);
	label->SetColor(sf::Color::Black);

	editCursorAtChar = (int)text.size();
	currentCursorPosition = label->GetWidthOfPartText((int)text.size());
}

EditBox::~EditBox()
{
	delete label;
	label = nullptr;

	delete frame;
	frame = nullptr;
}

void EditBox::CheckEvents(sf::Event &event)
{
	if (editBoxState == EditBoxState::Disabled)
		return;

	if (skipEvent)
	{
		skipEvent = false;
		return;
	}

	int mx = GetSharedContext()->GetMouse()->mouseX;
	bool mouseInside = IsMouseInside();

	if (event.type == sf::Event::MouseButtonPressed && mouseInside)
	{
		editBoxState = EditBoxState::Editing;

		for (int i = (int)label->GetText().size(); i > -1; i--)
		{
			if ((mx - position.x -2) > label->GetWidthOfPartText(i))
			{
				editCursorAtChar = i;
				currentCursorPosition = label->GetWidthOfPartText(i);
				break;
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed && !mouseInside)
	{
		editBoxState = EditBoxState::Normal;
		editCursorAtChar = (int)label->GetText().size();
		currentCursorPosition = label->GetWidthOfPartText((int)label->GetText().size());
	}

	if (editBoxState == EditBoxState::Editing)
	{
		// * Check if text has more than MAX chars when typing. (make it scroll right wise)
		if (event.type == sf::Event::TextEntered)
		{
			if (event.key.code == 8) // BackSpace
			{
				if (editCursorAtChar <= 0)
					return;

				std::string strTemp = label->GetText();
				std::string strTemp2 = strTemp.substr(editCursorAtChar);

				strTemp = strTemp.substr(0, editCursorAtChar);
				strTemp.pop_back();
				editCursorAtChar--;
				if (editCursorAtChar < 0)
					editCursorAtChar = 0;
				strTemp += strTemp2;

				label->SetText(strTemp);
				currentCursorPosition = label->GetWidthOfPartText(editCursorAtChar);
			}
			else if (event.key.code == 13) // Return
			{
				// Do nothing for single line EditBox.
			}
			else
			{
				std::string strTemp = label->GetText();
				std::string strTemp2 = strTemp.substr(editCursorAtChar);
				
				strTemp = strTemp.substr(0, editCursorAtChar);
				strTemp.push_back(event.text.unicode);
				editCursorAtChar++;
				strTemp += strTemp2;
				
				label->SetText(strTemp);
				currentCursorPosition = label->GetWidthOfPartText(editCursorAtChar);
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				editCursorAtChar--;
				if (editCursorAtChar < 0)
					editCursorAtChar = 0;
				currentCursorPosition = label->GetWidthOfPartText(editCursorAtChar);
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				if(editCursorAtChar < label->GetText().size())
					editCursorAtChar++;
				currentCursorPosition = label->GetWidthOfPartText(editCursorAtChar);
			}
			else if (event.key.code == sf::Keyboard::Delete)
			{
				std::string strTemp = label->GetText();
				if (editCursorAtChar >= strTemp.size())
					return;

				std::string strTemp2 = strTemp.substr(editCursorAtChar);
				strTemp = strTemp.substr(0, editCursorAtChar);
				strTemp2 = strTemp2.substr(1);
				strTemp += strTemp2;

				label->SetText(strTemp);
				currentCursorPosition = label->GetWidthOfPartText(editCursorAtChar);
			}
		}
	}
}

void EditBox::Render()
{
	frame->Render();
	if (editBoxState == EditBoxState::Editing)
	{
		sf::Vector2f pos;
		pos.x = position.x + 2 + 3 + currentCursorPosition;
		pos.y = position.y + 2 + 2;

		sf::RectangleShape cursorShape;
		cursorShape.setPosition(pos);
		cursorShape.setSize(sf::Vector2f(2, size.y - 8));
		cursorShape.setFillColor(sf::Color::Black);
		renderWindow->draw(cursorShape);
	}

	label->Render();
}

SharedContext* EditBox::GetSharedContext()
{
	return sharedContext;
}

void EditBox::SetEditBoxState(EditBoxState state)
{
	if (state == EditBoxState::Disabled)
		frame->SetButtonColor(sf::Color(191, 191, 191));
	else
		frame->SetButtonColor(sf::Color(253, 253, 253));

	this->editBoxState = state;
}

EditBox::EditBoxState EditBox::GetEditBoxState()
{
	return editBoxState;
}

sf::Vector2f EditBox::GetPosition()
{
	return position;
}

sf::Vector2f EditBox::GetSize()
{
	return size;
}

void EditBox::SetFrameColor(sf::Color color)
{
	this->frame->SetButtonColor(color);
}

void EditBox::SetText(std::string text)
{
	editCursorAtChar = (int)text.size();
	currentCursorPosition = label->GetWidthOfPartText((int)text.size());
	this->label->SetText(text);
}

std::string EditBox::GetText()
{
	return label->GetText();
}

void EditBox::SetSkipNextEvent(bool skip)
{
	skipEvent = skip;
}

bool EditBox::IsMouseInside()
{
	int mx = GetSharedContext()->GetMouse()->mouseX;
	int my = GetSharedContext()->GetMouse()->mouseY;
	
	if (mx >= position.x && mx < (position.x + size.x))
	{
		if (my >= position.y && my < (position.y + size.y))
		{
			return true; // is inside
		}
	}
	return false; // not inside
}

/*
void EditBox::SetHideTextCursor(bool hide)
{
	this->hideTextCursor = hide;
}
*/

/*
void EditBox::SetCheckBoxState(EditBoxState state)
{
	this->editBoxState = state;
}
*/