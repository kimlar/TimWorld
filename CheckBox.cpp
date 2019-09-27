#include "CheckBox.h"

CheckBox::CheckBox(SharedContext* sharedContext, sf::Vector2f position, std::string text, CheckBoxState state)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;

	position.y += 4; // Correction
	this->position = position;
	this->size = sf::Vector2f(16, 16);
	this->labelText = text;
	this->fontSize = 14;
	this->checkBoxState = state;

	frame = new Frame(GetSharedContext(), sf::Vector2f(position.x, position.y), sf::Vector2f(size.x + 0, size.y + 0));
	frame->SetPressedDown(true);

	if(checkBoxState == CheckBoxState::Disabled)
		frame->SetButtonColor(sf::Color(191, 191, 191));
	else
		frame->SetButtonColor(sf::Color(253, 253, 253));
	
	label = new Label(GetSharedContext(), sf::Vector2f(position.x + 20, position.y - 1), text, fontSize);
	label->SetColor(sf::Color::Black);


	// Check mark line
	markLine1.setSize(sf::Vector2f(6, 3));
	markLine1.setPosition(position.x + 5, position.y + 6);
	markLine1.setRotation(45);
	markLine1.setFillColor(sf::Color::Black);
	//
	markLine2.setSize(sf::Vector2f(6, 3));
	markLine2.setPosition(position.x + 7, position.y + 8);
	markLine2.setRotation(-45);
	markLine2.setFillColor(sf::Color::Black);
}

CheckBox::~CheckBox()
{
	delete label;
	label = nullptr;

	delete frame;
	frame = nullptr;
}

void CheckBox::CheckEvents(sf::Event &event)
{
	if (checkBoxState == CheckBoxState::Disabled)
		return;

	int mx = GetSharedContext()->GetMouse()->mouseX;
	int my = GetSharedContext()->GetMouse()->mouseY;

	bool mouseInside = false;
	if (mx >= position.x && mx < (position.x + size.x))
		if (my >= position.y && my < (position.y + size.y))
			mouseInside = true;

	if (event.type == sf::Event::MouseButtonPressed && mouseInside)
	{
		if (checkBoxState == CheckBoxState::Checked)
			checkBoxState = CheckBoxState::Unchecked;
		else
			checkBoxState = CheckBoxState::Checked;
	}
}

void CheckBox::Render()
{
	frame->Render();
	label->Render();

	if (checkBoxState == CheckBoxState::Checked)
	{
		renderWindow->draw(markLine1);
		renderWindow->draw(markLine2);		
	}
}

SharedContext* CheckBox::GetSharedContext()
{
	return sharedContext;
}

void CheckBox::SetCheckBoxState(CheckBoxState state)
{
	this->checkBoxState = state;
}

bool CheckBox::IsChecked()
{
	if (checkBoxState == CheckBoxState::Checked)
		return true;

	return false;
}
