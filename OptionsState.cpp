#include "OptionsState.h"

#include "Controls.h"
#include "Engine.h"

#include "MainMenuState.h" //TEMP!


OptionsState::OptionsState(SharedContext* sharedContext) : State(sharedContext)
{
	Log("OptionsState: Constructor");
}

OptionsState::~OptionsState()
{
	Log("OptionsState: Destructor");
}

void OptionsState::Enter()
{
	Log("OptionsState: Enter");

	int menuW = 600;
	int menuH = 300;
	int menuX = GetSharedContext()->GetRenderWindow()->getSize().x / 2 - menuW / 2;
	int menuY = GetSharedContext()->GetRenderWindow()->getSize().y / 2 - menuH / 2;

	optionsDialog = new Dialog(GetSharedContext(), sf::Vector2f((float)menuX, (float)menuY),
		sf::Vector2f((float)menuW, (float)menuH), "OPTIONS", 50, sf::Color(127, 127, 127, 140));

	int frameX = menuX - 40;
	int frameY = menuY + 25;
	int frameW = menuW + 80;
	int frameH = menuH - 20;
	int frameMarginX = frameX + 25;
	int frameMarginY = frameY + 25;

	optionsFrame = new Frame(GetSharedContext(), sf::Vector2f((float)frameX, (float)frameY),
		sf::Vector2f((float)frameW, (float)frameH));
	optionsFrame->SetButtonColor(sf::Color(161, 161, 161));

	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(menuX + 200 - 240, menuY + 80 - 100, 160, 45), "Gameplay", 28));
	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(menuX + 200 - 70, menuY + 80 - 100, 160, 45), "Controls", 28));
	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(menuX + 200 + 100, menuY + 80 - 100, 160, 45), "Video", 28));
	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(menuX + 200 + 270, menuY + 80 - 100, 160, 45), "Sound", 28));
	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(menuX + 200 - 240, menuY + 80 + 250, 160, 45), "Defaults", 28));
	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(menuX + 200 + 100, menuY + 80 + 250, 160, 45), "Back", 28));
	buttons.push_back(new Button(GetSharedContext(), sf::Rect<int>(menuX + 200 + 270, menuY + 80 + 250, 160, 45), "Apply", 28));

	// NOTE: This is a special case for when user changes video settings and need to remember that after recreating the window.
	if (GetSharedContext()->GetEngine()->restartVideo)
	{
		GetSharedContext()->GetEngine()->restartVideo = false;
		selectedTab = OptionsTab::Video;
	}

	//
	// Gameplay
	//
	checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY), "Skip Intro"));
	if (GetSharedContext()->GetSettings()->GetSkipIntro())
		checkBoxes[0]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);

	checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 30), "Show tooltip"));
	if (GetSharedContext()->GetSettings()->GetToolTip())
		checkBoxes[1]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);
	

	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 60 + 3), "Languages", 14));
	std::vector<std::string> languages;
	languages.push_back("English");
	languages.push_back("German");
	languages.push_back("French");
	languages.push_back("Spanish");
	comboBoxes.push_back(new ComboBox(GetSharedContext(), sf::Vector2f((float)frameMarginX + 100, (float)frameMarginY + 60), languages));
	int resultLanguage = comboBoxes[0]->GetIndexByText(GetSharedContext()->GetSettings()->GetLanguage());
	if (resultLanguage != -1)
		comboBoxes[0]->SetSelectedIndex(resultLanguage);
	else
		LogError("OptionsState.cpp: Could not find choosen language from comboBox");
	
	//comboBoxes.push_back(new ComboBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 60), "1920x1080"));

	//checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 90), "Just another test"));

	//editBoxes.push_back(new EditBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 120), "Edit this text"));

	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 90 + 3), "Camera move speed", 14));
	sliders.push_back(new Slider(GetSharedContext(), sf::Vector2f((float)frameMarginX + 160, (float)frameMarginY + 90), (int)GetSharedContext()->GetSettings()->GetCameraMoveSpeed()));
	sliders[0]->SetMinValue(100);
	sliders[0]->SetMaxValue(1200);
	sliders[0]->SetValue((int)GetSharedContext()->GetSettings()->GetCameraMoveSpeed());
	
	//
	// Controls
	//

	//checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY), "Testing A"));
	//checkBoxes[2]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);

	//checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 30), "Testing B"));
	//checkBoxes[3]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);

	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 0 + 3), "MoveCameraLeft", 14));
	editBoxes.push_back(new EditBox(GetSharedContext(), sf::Vector2f((float)frameMarginX + 140, (float)frameMarginY + 0), GetSharedContext()->GetSettings()->GetEventString(GetSharedContext()->GetSettings()->GetMoveCameraLeft())));

	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 30 + 3), "MoveCameraRight", 14));
	editBoxes.push_back(new EditBox(GetSharedContext(), sf::Vector2f((float)frameMarginX + 140, (float)frameMarginY + 30), GetSharedContext()->GetSettings()->GetEventString(GetSharedContext()->GetSettings()->GetMoveCameraRight())));

	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 60 + 3), "MoveCameraUp", 14));
	editBoxes.push_back(new EditBox(GetSharedContext(), sf::Vector2f((float)frameMarginX + 140, (float)frameMarginY + 60), GetSharedContext()->GetSettings()->GetEventString(GetSharedContext()->GetSettings()->GetMoveCameraUp())));

	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 90 + 3), "MoveCameraDown", 14));
	editBoxes.push_back(new EditBox(GetSharedContext(), sf::Vector2f((float)frameMarginX + 140, (float)frameMarginY + 90), GetSharedContext()->GetSettings()->GetEventString(GetSharedContext()->GetSettings()->GetMoveCameraDown())));

	//
	// Video
	//
	
	//checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY), "Testing C"));
	//checkBoxes[4]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);
	
	//checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 30), "Testing D"));
	//checkBoxes[5]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);

	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 0 + 3), "Video resolution", 14));
	std::vector<std::string> resolutions;
	resolutions.push_back("1920x1080");
	resolutions.push_back("1600x900");
	resolutions.push_back("1024x768");
	resolutions.push_back("800x600");
	comboBoxes.push_back(new ComboBox(GetSharedContext(), sf::Vector2f((float)frameMarginX + 140, (float)frameMarginY + 0), resolutions));
	int resultVideoResolution = comboBoxes[1]->GetIndexByText(std::to_string(GetSharedContext()->GetSettings()->GetWindowWidth()) + "x" + std::to_string(GetSharedContext()->GetSettings()->GetWindowHeight()));
	if (resultVideoResolution != -1)
		comboBoxes[1]->SetSelectedIndex(resultVideoResolution);
	else
		LogError("OptionsState.cpp: Could not find choosen resolution from comboBox");


	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 30 + 3), "Display mode", 14));
	std::vector<std::string> displayModes;
	displayModes.push_back("Fullscreen");
	displayModes.push_back("Borderless");
	displayModes.push_back("Windowed");
	comboBoxes.push_back(new ComboBox(GetSharedContext(), sf::Vector2f((float)frameMarginX + 140, (float)frameMarginY + 30), displayModes));
	int dispMode=0;
	switch (GetSharedContext()->GetSettings()->GetDisplayMode())
	{
	case sf::Style::Fullscreen:
		dispMode = 0;
		break;
	case sf::Style::None:
		dispMode = 1;
		break;
	case sf::Style::Titlebar | sf::Style::Close:
		dispMode = 2;
		break;
	}
	comboBoxes[2]->SetSelectedIndex(dispMode);

	checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 60), "VSync"));
	if (GetSharedContext()->GetSettings()->GetVSync())
		checkBoxes[2]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);
	//checkBoxes[6]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);

	checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 90), "Use frame limit"));
	if (GetSharedContext()->GetSettings()->GetFramerateLimit() != 0)
		checkBoxes[3]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);
	editBoxes.push_back(new EditBox(GetSharedContext(), sf::Vector2f((float)frameMarginX + 140, (float)frameMarginY + 90), std::to_string(GetSharedContext()->GetSettings()->GetFramerateLimit())));
	if (GetSharedContext()->GetSettings()->GetFramerateLimit() == 0)
		editBoxes[4]->SetEditBoxState(EditBox::EditBoxState::Disabled);


	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 120 + 3), "Anti-aliasing", 14));
	std::vector<std::string> antiAlising;
	antiAlising.push_back("Off");
	antiAlising.push_back("1x");
	antiAlising.push_back("2x");
	antiAlising.push_back("4x");
	antiAlising.push_back("8x");
	antiAlising.push_back("16x");
	comboBoxes.push_back(new ComboBox(GetSharedContext(), sf::Vector2f((float)frameMarginX + 140, (float)frameMarginY + 120), antiAlising));
	int antialias = GetSharedContext()->GetSettings()->GetAntiAliasing();
	switch (antialias)
	{
	case 0: // Off
		comboBoxes[3]->SetSelectedIndex(0);
		break;
	case 1: // 1x
		comboBoxes[3]->SetSelectedIndex(1);
		break;
	case 2: // 2x
		comboBoxes[3]->SetSelectedIndex(2);
		break;
	case 4: // 4x
		comboBoxes[3]->SetSelectedIndex(3);
		break;
	case 8: // 8x
		comboBoxes[3]->SetSelectedIndex(4);
		break;
	case 16: // 16x
		comboBoxes[3]->SetSelectedIndex(5);
		break;
	}

	checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 150), "Show FPS"));
	checkBoxes[4]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);


	//
	// Sound
	//
	
	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 0 + 3), "Master volume", 14));
	sliders.push_back(new Slider(GetSharedContext(), sf::Vector2f((float)frameMarginX + 160, (float)frameMarginY + 0), (int)GetSharedContext()->GetSettings()->GetMasterVolume()));
	//sliders[1]->SetShowAsPercent(true);

	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 30 + 3), "Music volume", 14));
	sliders.push_back(new Slider(GetSharedContext(), sf::Vector2f((float)frameMarginX + 160, (float)frameMarginY + 30), (int)GetSharedContext()->GetSettings()->GetMusicVolume()));
	//sliders[2]->SetShowAsPercent(true);

	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 60 + 3), "Sound FX volume", 14));
	sliders.push_back(new Slider(GetSharedContext(), sf::Vector2f((float)frameMarginX + 160, (float)frameMarginY + 60), (int)GetSharedContext()->GetSettings()->GetSoundFxVolume()));
	//sliders[3]->SetShowAsPercent(true);

	labels.push_back(new Label(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 90 + 3), "Voice volume", 14));
	sliders.push_back(new Slider(GetSharedContext(), sf::Vector2f((float)frameMarginX + 160, (float)frameMarginY + 90), (int)GetSharedContext()->GetSettings()->GetVoiceVolume()));
	//sliders[4]->SetShowAsPercent(true);


	//checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY), "Testing E"));
	//checkBoxes[5]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);
	
	//checkBoxes.push_back(new CheckBox(GetSharedContext(), sf::Vector2f((float)frameMarginX, (float)frameMarginY + 30), "Testing F"));
	//checkBoxes[6]->SetCheckBoxState(CheckBox::CheckBoxState::Checked);
}

void OptionsState::Exit()
{
	Log("OptionsState: Exit");

	delete optionsDialog;
	optionsDialog = nullptr;

	delete optionsFrame;
	optionsFrame = nullptr;

	for (int i = 0; i < labels.size(); i++)
	{
		delete labels[i];
		labels[i] = nullptr;
	}

	for (int i = 0; i < checkBoxes.size(); i++)
	{
		delete checkBoxes[i];
		checkBoxes[i] = nullptr;
	}
	checkBoxes.clear();

	for (int i = 0; i < comboBoxes.size(); i++)
	{
		delete comboBoxes[i];
		comboBoxes[i] = nullptr;
	}
	comboBoxes.clear();

	for (int i = 0; i < editBoxes.size(); i++)
	{
		delete editBoxes[i];
		editBoxes[i] = nullptr;
	}
	editBoxes.clear();
		
	for (int i = 0; i < sliders.size(); i++)
	{
		delete sliders[i];
		sliders[i] = nullptr;
	}
	sliders.clear();

	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
		buttons[i] = nullptr;
	}
	buttons.clear();
}

void OptionsState::Event(sf::Event &event)
{
	//Log("OptionsState: Event");

	/*
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
	{
		GetStateManager()->PopState();
		GetStateManager()->PushState(new MainMenuState(GetSharedContext()));
	}
	*/

	////////////////////////

	if (buttons[0]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		buttons[0]->ResetEvent();
		selectedTab = OptionsTab::Gameplay;
		return;
	}
	if (buttons[1]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		buttons[1]->ResetEvent();
		selectedTab = OptionsTab::Controls;
		return;
	}
	if (buttons[2]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		buttons[2]->ResetEvent();
		selectedTab = OptionsTab::Video;
		return;
	}
	if (buttons[3]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		buttons[3]->ResetEvent();
		selectedTab = OptionsTab::Sound;
		return;
	}
	if (buttons[4]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		buttons[4]->ResetEvent();

		//
		// Restore to default
		//

		// Gameplay
		checkBoxes[0]->SetCheckBoxState(CheckBox::CheckBoxState::Unchecked); // SkipIntro
		checkBoxes[1]->SetCheckBoxState(CheckBox::CheckBoxState::Checked); // ToolTip
		comboBoxes[0]->SetSelectedIndex(0); // Language
		sliders[0]->SetValue(600); // CameraMoveSpeed

		// Controls
		editBoxes[0]->SetText("A"); // MoveCameraLeft
		editBoxes[1]->SetText("D"); // MoveCameraRight
		editBoxes[2]->SetText("W"); // MoveCameraUp
		editBoxes[3]->SetText("S"); // MoveCameraDown

		// Video
		comboBoxes[1]->SetSelectedIndex(3); // VideoResolution
		comboBoxes[2]->SetSelectedIndex(2); // DisplayMode
		checkBoxes[2]->SetCheckBoxState(CheckBox::CheckBoxState::Unchecked); // VSync
		checkBoxes[3]->SetCheckBoxState(CheckBox::CheckBoxState::Unchecked); // FramerateLimit (part 1/3)
		editBoxes[4]->SetText("0"); // FramerateLimit (part 2/3)
		editBoxes[4]->SetEditBoxState(EditBox::EditBoxState::Disabled); // FramerateLimit (part 3/3)
		comboBoxes[3]->SetSelectedIndex(0); // Anti-aliasing (off)
		checkBoxes[4]->SetCheckBoxState(CheckBox::CheckBoxState::Unchecked); // ShowFPS

		// Sound
		sliders[1]->SetValue(100); // MasterVolume
		sliders[2]->SetValue(100); // MusicVolume
		sliders[3]->SetValue(100); // SoundFxVolume
		sliders[4]->SetValue(100); // VoiceVolume

		return;
	}
	if (buttons[5]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		buttons[5]->ResetEvent();
		GetStateManager()->PopState(); // Should I pop it or not ????
		GetStateManager()->PushState(new MainMenuState(GetSharedContext()));
		return;
	}
	if (buttons[6]->CheckEvents(event) == Button::ButtonAction::LeftClicked)
	{
		buttons[6]->ResetEvent();
		SaveSettings();
		bool restartVideo = RestartWindowRequired();
				
		GetSharedContext()->GetSettings()->Load();
		GetSharedContext()->GetEngine()->BindControls();

		if (restartVideo)
		{
			// Recreate window
			GetSharedContext()->GetEngine()->GetWindow().Setup(GetSharedContext()->GetSettings());
			
			// Replace the current state. Needs an update anyway.
			GetStateManager()->PopState();
			GetStateManager()->PushState(new OptionsState(GetSharedContext()));
			GetStateManager()->GetSharedContext()->GetEngine()->restartVideo = true; // Remember which tab
		}

		return;
	}

	
	////////////////////////

	if (selectedTab == OptionsTab::Gameplay)
	{
		checkBoxes[0]->CheckEvents(event);
		checkBoxes[1]->CheckEvents(event);
		comboBoxes[0]->CheckEvents(event);
		//editBoxes[0]->CheckEvents(event);
		sliders[0]->CheckEvents(event);
	}
	if (selectedTab == OptionsTab::Controls)
	{
		//checkBoxes[2]->CheckEvents(event);
		//checkBoxes[3]->CheckEvents(event);

		// MoveCameraLeft
		editBoxes[0]->CheckEvents(event);
		ChangeBinding(0, event);
		
		// MoveCameraRight
		editBoxes[1]->CheckEvents(event);
		ChangeBinding(1, event);

		// MoveCameraUp
		editBoxes[2]->CheckEvents(event);
		ChangeBinding(2, event);

		// MoveCameraDown
		editBoxes[3]->CheckEvents(event);
		ChangeBinding(3, event);

	}
	if (selectedTab == OptionsTab::Video)
	{
		//checkBoxes[4]->CheckEvents(event);
		//checkBoxes[5]->CheckEvents(event);
		if (comboBoxes[1]->CheckEvents(event))
			return;
		if (comboBoxes[2]->CheckEvents(event))
			return;
		checkBoxes[2]->CheckEvents(event);

		checkBoxes[3]->CheckEvents(event);
		if (checkBoxes[3]->IsChecked() && editBoxes[4]->GetEditBoxState() == EditBox::EditBoxState::Disabled)
			editBoxes[4]->SetEditBoxState(EditBox::EditBoxState::Normal);
		else if (!checkBoxes[3]->IsChecked())
		{
			editBoxes[4]->SetText("0");
			editBoxes[4]->SetEditBoxState(EditBox::EditBoxState::Disabled);
		}
		editBoxes[4]->CheckEvents(event);

		comboBoxes[3]->CheckEvents(event);
		// Off
		// 1x
		// 2x
		// 4x
		// 8x
		// 16x
		//int antialiasing = GetAntiAliasingFromComboBox();

		checkBoxes[4]->CheckEvents(event);
	}
	if (selectedTab == OptionsTab::Sound)
	{
		//checkBoxes[5]->CheckEvents(event);
		//checkBoxes[6]->CheckEvents(event);
		sliders[1]->CheckEvents(event);
		sliders[2]->CheckEvents(event);
		sliders[3]->CheckEvents(event);
		sliders[4]->CheckEvents(event);
	}
}

void OptionsState::Update(float delta)
{
	//Log("OptionsState: Update");

	//terrain->Update(delta);
}

void OptionsState::Render()
{
	//Log("OptionsState: Render");

	optionsDialog->Render();

	optionsFrame->Render();

	//
	// Gameplay
	//
	if (selectedTab == OptionsTab::Gameplay)
	{
		checkBoxes[0]->Render();

		checkBoxes[1]->Render();

		labels[0]->Render();
		comboBoxes[0]->Render();
		
		//checkBoxes[2]->Render();

		//editBoxes[0]->Render();

		labels[1]->Render();
		sliders[0]->Render();
	}
	//
	// Controls
	//
	if (selectedTab == OptionsTab::Controls)
	{
		//checkBoxes[2]->Render();
		//checkBoxes[3]->Render();
		labels[2]->Render();
		editBoxes[0]->Render();
		labels[3]->Render();
		editBoxes[1]->Render();
		labels[4]->Render();
		editBoxes[2]->Render();
		labels[5]->Render();
		editBoxes[3]->Render();
	}
	//
	// Video
	//
	if (selectedTab == OptionsTab::Video)
	{
		//checkBoxes[4]->Render();
		//checkBoxes[5]->Render();

		labels[6]->Render();
		comboBoxes[1]->Render();

		labels[7]->Render();
		comboBoxes[2]->Render();

		checkBoxes[2]->Render();

		checkBoxes[3]->Render();
		editBoxes[4]->Render();

		labels[8]->Render();
		comboBoxes[3]->Render();

		checkBoxes[4]->Render();
	}
	//
	// Sound
	//
	if (selectedTab == OptionsTab::Sound)
	{
		//checkBoxes[5]->Render();
		//checkBoxes[6]->Render();

		labels[9]->Render();
		sliders[1]->Render();
		labels[10]->Render();
		sliders[2]->Render();
		labels[11]->Render();
		sliders[3]->Render();
		labels[12]->Render();
		sliders[4]->Render();

	}



	//optionsLabel->Render();

	for (int i = 0; i < buttons.size(); i++)
	{
		if (i == (int)selectedTab)
			buttons[i]->SetButtonColor(sf::Color(63, 248, 63));
		else
			buttons[i]->ResetButtonColor();

		buttons[i]->Render();
	}

	//
	// Post rendering
	//
	RenderPost();
}

void OptionsState::RenderPost()
{
	//
	// Gameplay
	//
	if (selectedTab == OptionsTab::Gameplay)
	{
		comboBoxes[0]->RenderPost();
	}
	//
	// Controls
	//
	if (selectedTab == OptionsTab::Controls)
	{
	}
	//
	// Video
	//
	if (selectedTab == OptionsTab::Video)
	{
		comboBoxes[1]->RenderPost();
		comboBoxes[2]->RenderPost();
		comboBoxes[3]->RenderPost();
	}
	//
	// Sound
	//
	if (selectedTab == OptionsTab::Sound)
	{
	}
}

void OptionsState::ChangeBinding(int editId, sf::Event &event)
{
	if (editBinding[editId])
	{
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
		{
			editBinding[editId] = false;
			editBoxes[editId]->SetText(GetSharedContext()->GetSettings()->GetEventString(event));
			editBoxes[editId]->SetSkipNextEvent(true);
			editBoxes[editId]->SetEditBoxState(EditBox::EditBoxState::Normal);
			editBoxes[editId]->SetFrameColor(sf::Color::White);
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (editBoxes[editId]->IsMouseInside())
		{
			editBinding[editId] = true;
			editBoxes[editId]->SetText("<Press any button>");
			editBoxes[editId]->SetEditBoxState(EditBox::EditBoxState::EditingHideCursor);
			editBoxes[editId]->SetFrameColor(sf::Color(191, 191, 191));
		}
	}
}

int OptionsState::GetAntiAliasingFromComboBox()
{
	switch (comboBoxes[3]->GetSelectedIndex())
	{
	case 0: // Off
		return 0;
	case 1: // 1x
		return 1;
	case 2: // 2x
		return 2;
	case 3: // 4x
		return 4;
	case 4: // 8x
		return 8;
	case 5: // 16x
		return 16;
	}

	return 0;
}

void OptionsState::SaveSettings()
{
	/////////////////////////////////////////////////////////////////////////////////////////////////

	//
	// Read save file into memory to be able to reconstruct new save file. (not removing comments)
	//
	saveLines.clear();
	std::string line;
	std::ifstream settingsFile("Settings.txt");
	if (settingsFile.is_open())
	{
		while (std::getline(settingsFile, line))
		{
			saveLines.push_back(line);
		}
		settingsFile.close();
	}
	else
	{
		LogError("Settings.cpp: Could not read file. Settings.txt");
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////

	//
	// Now start the process by finding what line and then replace ONLY the value.
	// Keep comments and such.
	//

	std::string tempLine;
	std::string workLine;
	std::string comments;
	std::string keyword;

	// Find: SkipIntro
	for (int i = 0; i < saveLines.size(); i++)
	{
		tempLine = saveLines[i];
		workLine = tempLine;
		comments = "";
		//workLine = StringUtils::RemoveWhiteSpaces(saveLines[i]);

		if (workLine.size() > 2)
		{
			// Get keyword and save comments
			for (int j = 0; j < workLine.size() - 1; j++)
			{
				if (workLine[j] == '/' && workLine[j + 1] == '/')
				{
					comments = workLine.substr(j);
					workLine = StringUtils::RemoveWhiteSpaces(workLine.substr(0, j));
					break;
				}
			}

			// SkipIntro
			keyword = "SkipIntro";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				std::string workSetStr = (checkBoxes[0]->IsChecked() ? "y" : "n");
				saveLines[i] = keyword + "=" + workSetStr;
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// ToolTip
			keyword = "ToolTip";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				std::string workSetStr = (checkBoxes[1]->IsChecked() ? "y" : "n");
				saveLines[i] = keyword + "=" + workSetStr;
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// Language
			keyword = "Language";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + comboBoxes[0]->GetSelectedText();
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// CameraMoveSpeed
			keyword = "CameraMoveSpeed";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + std::to_string(sliders[0]->GetValue());
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// MoveCameraLeft
			keyword = "MoveCameraLeft";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + editBoxes[0]->GetText();
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// MoveCameraRight
			keyword = "MoveCameraRight";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + editBoxes[1]->GetText();
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// MoveCameraUp
			keyword = "MoveCameraUp";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + editBoxes[2]->GetText();
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// MoveCameraDown
			keyword = "MoveCameraDown";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + editBoxes[3]->GetText();
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// VideoResolution
			keyword = "VideoResolution";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + comboBoxes[1]->GetSelectedText();
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// DisplayMode
			keyword = "DisplayMode";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + std::to_string(comboBoxes[2]->GetSelectedIndex()) + ",0"; // TODO: Reimplement for default fullscreen
				
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// VSync
			keyword = "VSync";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				std::string workSetStr = (checkBoxes[2]->IsChecked() ? "y" : "n");
				saveLines[i] = keyword + "=" + workSetStr;
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// FramerateLimit
			keyword = "FramerateLimit";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + editBoxes[4]->GetText();
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// AntiAliasing
			keyword = "AntiAliasing";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + std::to_string(GetAntiAliasingFromComboBox());
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// ShowFPS
			keyword = "ShowFPS";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				std::string workSetStr = (checkBoxes[4]->IsChecked() ? "y" : "n");
				saveLines[i] = keyword + "=" + workSetStr;
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// MasterVolume
			keyword = "MasterVolume";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + std::to_string(sliders[1]->GetValue());
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// MusicVolume
			keyword = "MusicVolume";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + std::to_string(sliders[2]->GetValue());
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// SoundFxVolume
			keyword = "SoundFxVolume";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + std::to_string(sliders[3]->GetValue());
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}

			// VoiceVolume
			keyword = "VoiceVolume";
			if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), StringUtils::ToUpperCase(workLine)))
			{
				saveLines[i] = keyword + "=" + std::to_string(sliders[4]->GetValue());
				if (comments != "")
					saveLines[i] += " " + comments;
				comments = "";
				//Debug("#" + saveLines[i] + "#");
				continue;
			}


		}


	}

	


	/////////////////////////////////////////////////////////////////////////////////////////////////

	//
	// Finally we can actually save the file (with comments)
	//
	std::ofstream saveFile("Settings.txt");
	if (saveFile.is_open())
	{
		for (int i = 0; i < saveLines.size(); i++)
		{
			saveFile << saveLines[i] << "\n";
		}

		saveFile.close();
	}
	else
	{
		LogError("OptionsState.cpp: Failed to save the settings. Settings.txt");
	}
}

bool OptionsState::RestartWindowRequired()
{
	// Check video resolution
	std::string temp = std::to_string( GetSharedContext()->GetSettings()->GetWindowWidth()) + "x" + std::to_string( GetSharedContext()->GetSettings()->GetWindowHeight());
	if (temp != comboBoxes[1]->GetSelectedText())
		return true;

	// Check video mode
	int dispmode = 0;
	switch (GetSharedContext()->GetSettings()->GetDisplayMode())
	{
	case DisplayMode::FULLSCREEN:
		dispmode = 0;
		break;
	case DisplayMode::BORDERLESS:
		dispmode = 1;
		break;
	case DisplayMode::WINDOWED:
		dispmode = 2;
		break;
	}
	std::string temp2 =  std::to_string(dispmode) + ",0";
	std::string temp3 = std::to_string(comboBoxes[2]->GetSelectedIndex()) + ",0";
	if (temp2 != temp3)
		return true;

	// Check VSync
	if (GetSharedContext()->GetSettings()->GetVSync() != checkBoxes[2]->IsChecked())
		return true;

	// Check FramerateLimit
	if (std::to_string(GetSharedContext()->GetSettings()->GetFramerateLimit()) != editBoxes[4]->GetText())
		return true;

	// Check AntiAliasing
	if (GetSharedContext()->GetSettings()->GetAntiAliasing() != GetAntiAliasingFromComboBox())
		return true;

	return false; // No restart needed
}
