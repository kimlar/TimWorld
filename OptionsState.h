#pragma once

#include "State.h"
#include "SharedContext.h"

#include "Dialog.h"
#include "Frame.h"
#include "CheckBox.h"
#include "ComboBox.h"
#include "EditBox.h"
#include "Slider.h"
#include "Button.h"
//#include "Label.h"

class OptionsState : public State
{
public:
	OptionsState(SharedContext* sharedContext);
	~OptionsState();

	void Enter();
	void Exit();

	void Event(sf::Event &event);
	void Update(float delta);
	void Render();
	void RenderPost();

private:
	Dialog* optionsDialog;
	Frame* optionsFrame;
	std::vector<Label*> labels;
	std::vector<CheckBox*> checkBoxes;
	std::vector<ComboBox*> comboBoxes;
	std::vector<EditBox*> editBoxes;
	std::vector<Slider*> sliders;
	std::vector<Button*> buttons;
	enum class OptionsTab { Gameplay = 0, Controls, Video, Sound };
	OptionsTab selectedTab = OptionsTab::Gameplay;

	bool editBinding[4];
	void ChangeBinding(int editId, sf::Event &event);
	
	int GetAntiAliasingFromComboBox();

	void SaveSettings();
	std::vector<std::string> saveLines;
	bool RestartWindowRequired();
};
