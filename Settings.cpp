#include "Settings.h"

#include <fstream>
#include <string>
#include <iostream> // TODO: REMOVE this and cout

#include "StringUtils.h"

void Settings::Setup()
{
	////////////////////////////////////////////////////////////////////////////////////

	// Bindable keywords
	bindKeywords.clear();
	bindKeywords.push_back("MoveCameraLeft");
	bindKeywords.push_back("MoveCameraRight");
	bindKeywords.push_back("MoveCameraUp");
	bindKeywords.push_back("MoveCameraDown");

	////////////////////////////////////////////////////////////////////////////////////

	keywords.clear();
	
	// *** GAMEPLAY ***
	keywords.push_back("SkipIntro");
	keywords.push_back("ToolTip");
	keywords.push_back("Language");
	keywords.push_back("CameraMoveSpeed");

	// *** CONTROLS ***
	for (auto &i : bindKeywords)
		keywords.push_back(i);

	// *** VIDEO ***
	keywords.push_back("VideoResolution");
	keywords.push_back("VSync");
	keywords.push_back("FramerateLimit");
	keywords.push_back("DisplayMode");
	keywords.push_back("AntiAliasing");
	keywords.push_back("ShowFPS");

	// *** SOUND ***
	keywords.push_back("MasterVolume");
	keywords.push_back("MusicVolume");
	keywords.push_back("SoundFxVolume");
	keywords.push_back("VoiceVolume");
	
	////////////////////////////////////////////////////////////////////////////////////
}

void Settings::Load()
{
	umSettings.clear();

	std::string line;
	std::ifstream settingsFile("Settings.txt");
	if (settingsFile.is_open())
	{
		while (std::getline(settingsFile, line))
		{
			Process(line);
		}
		settingsFile.close();		
	}
	else
	{
		LogError("Settings.cpp: Could not read file. Settings.txt");
	}

	/*
	// debug listing
	for (auto &i : umSettings)
		std::cout << i.first << ": " << i.second << std::endl;
	*/
}

void Settings::Save()
{
	/*
	ofstream myfile ("example.txt");
	if (myfile.is_open())
	{
	myfile << "This is a line.\n";
	myfile << "This is another line.\n";
	myfile.close();
	}
	else cout << "Unable to open file";
	*/
}

bool Settings::GetSkipIntro()
{
	return StringUtils::ConvertToBool(umSettings["SkipIntro"]);
}

bool Settings::GetToolTip()
{
	return StringUtils::ConvertToBool(umSettings["ToolTip"]);
}

std::string Settings::GetLanguage()
{
	std::string lang = umSettings["Language"];
	if (lang == "ENGLISH")
		return "English";
	else if (lang == "SPANISH")
		return "Spanish";
	else if (lang == "GERMAN")
		return "German";
	else if (lang == "FRENCH")
		return "French";
	else if (lang == "ITALIAN")
		return "ITALIAN";
	else
		return "English"; // Default language
}

float Settings::GetCameraMoveSpeed()
{
	return std::stof(umSettings["CameraMoveSpeed"]);
}

sf::Event Settings::GetMoveCameraLeft()
{
	std::string keyword = "MoveCameraLeft";
	return GetEventBinding(keyword, umSettings[keyword]);
}

sf::Event Settings::GetMoveCameraRight()
{
	std::string keyword = "MoveCameraRight";
	return GetEventBinding(keyword, umSettings[keyword]);
}

sf::Event Settings::GetMoveCameraUp()
{
	std::string keyword = "MoveCameraUp";
	return GetEventBinding(keyword, umSettings[keyword]);
}

sf::Event Settings::GetMoveCameraDown()
{
	std::string keyword = "MoveCameraDown";
	return GetEventBinding(keyword, umSettings[keyword]);
}

int Settings::GetWindowWidth()
{
	std::string keyvalue = umSettings["VideoResolution"];
	
	for (int i = 0; i < keyvalue.length(); i++)
	{
		if (keyvalue[i] == 'x')
			return std::stoi(keyvalue.substr(0, i));
	}

	LogError("Settings.cpp: No width found from Settings.txt");
	return 0;
}

int Settings::GetWindowHeight()
{
	std::string keyvalue = umSettings["VideoResolution"];

	for (int i = 0; i < keyvalue.length() - 1; i++)
	{
		if (keyvalue[i] == 'x')
			return std::stoi(keyvalue.substr(i + 1));
	}

	LogError("Settings.cpp: No height found from Settings.txt");
	return 0;
}

bool Settings::GetVSync()
{
	return StringUtils::ConvertToBool(umSettings["VSync"]);
}

int Settings::GetFramerateLimit()
{
	return std::stoi(umSettings["FramerateLimit"]);
}

DisplayMode Settings::GetDisplayMode()
{
	std::string keyvalue = umSettings["DisplayMode"];

	for (int i = 0; i < keyvalue.length(); i++)
	{
		if (keyvalue[i] == ',')
		{
			int displaymode = std::stoi(keyvalue.substr(0, i));
			switch (displaymode)
			{
			case 0: // Fullscreen
				return DisplayMode::FULLSCREEN;
			case 1: // Borderless
				return DisplayMode::BORDERLESS;
			case 2: // Windowed
				return DisplayMode::WINDOWED;
			}
		}
	}

	return DisplayMode::FULLSCREEN; // Default display mode
}

DisplayMode Settings::GetDefaultFullscreenMode()
{
	std::string keyvalue = umSettings["DisplayMode"];

	for (int i = 0; i < keyvalue.length() - 1; i++)
	{
		if (keyvalue[i] == ',')
		{
			int defaultFullscreenMode = std::stoi(keyvalue.substr(i + 1));
			switch (defaultFullscreenMode)
			{
			case 0: // Fullscreen
				return DisplayMode::FULLSCREEN;
			case 1: // Borderless
				return DisplayMode::BORDERLESS;
			}
		}
	}

	return DisplayMode::FULLSCREEN; // Default fullscreen mode
}

int Settings::GetAntiAliasing()
{
	return std::stoi(umSettings["AntiAliasing"]);
}

bool Settings::GetShowFPS()
{
	return StringUtils::ConvertToBool(umSettings["ShowFPS"]);
}

int Settings::GetMasterVolume()
{
	return std::stoi(umSettings["MasterVolume"]);
}

int Settings::GetMusicVolume()
{
	return std::stoi(umSettings["MusicVolume"]);
}

int Settings::GetSoundFxVolume()
{
	return std::stoi(umSettings["SoundFxVolume"]);
}

int Settings::GetVoiceVolume()
{
	return std::stoi(umSettings["VoiceVolume"]);
}

std::string Settings::GetEventString(sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (umKeyBindDict.empty())
			BuildKeyboardBindDictionary();

		for (auto it = umKeyBindDict.begin(); it != umKeyBindDict.end(); ++it)
		{
			if (it->second == event.key.code)
			{
				return it->first;
			}
		}
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (umMouseBindDict.empty())
			BuildMouseBindDictionary();

		for (auto it = umMouseBindDict.begin(); it != umMouseBindDict.end(); ++it)
		{
			if (it->second == event.mouseButton.button)
			{
				return it->first;
			}
		}
	}

	return "";
}

void Settings::Process(std::string line)
{
	std::string upline = StringUtils::ToUpperCase(RemoveClutter(line));

	if (SkipTooSmallLine(upline))
		return;

	std::string keyvalue = GetKeyvalue(line);
	
	for (int i = 0; i < keywords.size(); i++)
	{
		if (FindKeyword(keywords[i], upline))
		{
			umSettings[keywords[i]] = keyvalue;
			return;
		}
	}
}

std::string Settings::RemoveClutter(std::string line)
{
	if (SkipTooSmallLine(line))
		return "";

	for (int i = 0; i < line.length() - 1; i++)
	{
		if (line[i] == '/' && line[i + 1] == '/')
		{
			line = StringUtils::RemoveWhiteSpaces(line.substr(0, i));
			break;
		}
	}

	return line;
}

bool Settings::SkipTooSmallLine(std::string line)
{
	if (line.length() < 2)
		return true;

	return false;
}

bool Settings::FindKeyword(std::string keyword, std::string line)
{
	if (StringUtils::FindKeyword(StringUtils::ToUpperCase(keyword), line))
		return true; // Found it

	return false;
}

std::string Settings::GetKeyvalue(std::string line)
{
	line = RemoveClutter(line);

	for (int i = 0; i < line.size()-1; i++)
	{
		if (line[i] == '=')
			return line.substr(i+1);
	}

	return "";
}

sf::Event Settings::GetEventBinding(std::string keyword, std::string keyvalue)
{
	for (auto &i : bindKeywords)
	{
		if (keyword == i)
		{
			sf::Event eventBind = {};

			// Keyboard binding
			eventBind = ConvertKeyboardKeyToEvent(keyvalue);
			if (eventBind.type == sf::Event::KeyPressed)
				return eventBind;

			// Mouse binding
			eventBind = ConvertMouseButtonToEvent(keyvalue);
			if (eventBind.type == sf::Event::MouseButtonPressed)
				return eventBind;
		}
	}

	return {};
}

sf::Event Settings::ConvertKeyboardKeyToEvent(std::string keyvalue)
{
	if (umKeyBindDict.empty())
		BuildKeyboardBindDictionary();

	std::unordered_map<std::string, sf::Keyboard::Key>::const_iterator it = umKeyBindDict.find(keyvalue);
	if (it != umKeyBindDict.end())
	{
		sf::Event eventBind = {};
		eventBind.type = sf::Event::KeyPressed;
		eventBind.key.code = it->second;
		return eventBind;
	}

	return {}; // Not a keyboard binding
}

void Settings::BuildKeyboardBindDictionary()
{
	umKeyBindDict.clear();

	umKeyBindDict["A"] = sf::Keyboard::A;
	umKeyBindDict["B"] = sf::Keyboard::B;
	umKeyBindDict["C"] = sf::Keyboard::C;
	umKeyBindDict["D"] = sf::Keyboard::D;
	umKeyBindDict["E"] = sf::Keyboard::E;
	umKeyBindDict["F"] = sf::Keyboard::F;
	umKeyBindDict["G"] = sf::Keyboard::G;
	umKeyBindDict["H"] = sf::Keyboard::H;
	umKeyBindDict["I"] = sf::Keyboard::I;
	umKeyBindDict["J"] = sf::Keyboard::J;
	umKeyBindDict["K"] = sf::Keyboard::K;
	umKeyBindDict["L"] = sf::Keyboard::L;
	umKeyBindDict["M"] = sf::Keyboard::M;
	umKeyBindDict["N"] = sf::Keyboard::N;
	umKeyBindDict["O"] = sf::Keyboard::O;
	umKeyBindDict["P"] = sf::Keyboard::P;
	umKeyBindDict["Q"] = sf::Keyboard::Q;
	umKeyBindDict["R"] = sf::Keyboard::R;
	umKeyBindDict["S"] = sf::Keyboard::S;
	umKeyBindDict["T"] = sf::Keyboard::T;
	umKeyBindDict["U"] = sf::Keyboard::U;
	umKeyBindDict["V"] = sf::Keyboard::V;
	umKeyBindDict["W"] = sf::Keyboard::W;
	umKeyBindDict["X"] = sf::Keyboard::X;
	umKeyBindDict["Y"] = sf::Keyboard::Y;
	umKeyBindDict["Z"] = sf::Keyboard::Z;
	umKeyBindDict["Num0"] = sf::Keyboard::Num0;
	umKeyBindDict["Num1"] = sf::Keyboard::Num1;
	umKeyBindDict["Num2"] = sf::Keyboard::Num2;
	umKeyBindDict["Num3"] = sf::Keyboard::Num3;
	umKeyBindDict["Num4"] = sf::Keyboard::Num4;
	umKeyBindDict["Num5"] = sf::Keyboard::Num5;
	umKeyBindDict["Num6"] = sf::Keyboard::Num6;
	umKeyBindDict["Num7"] = sf::Keyboard::Num7;
	umKeyBindDict["Num8"] = sf::Keyboard::Num8;
	umKeyBindDict["Num9"] = sf::Keyboard::Num9;
	umKeyBindDict["Escape"] = sf::Keyboard::Escape;
	umKeyBindDict["LControl"] = sf::Keyboard::LControl;
	umKeyBindDict["LShift"] = sf::Keyboard::LShift;
	umKeyBindDict["LAlt"] = sf::Keyboard::LAlt;
	umKeyBindDict["LSystem"] = sf::Keyboard::LSystem;
	umKeyBindDict["RControl"] = sf::Keyboard::RControl;
	umKeyBindDict["RShift"] = sf::Keyboard::RShift;
	umKeyBindDict["RSystem"] = sf::Keyboard::RSystem;
	umKeyBindDict["Menu"] = sf::Keyboard::Menu;
	umKeyBindDict["LBracket"] = sf::Keyboard::LBracket;
	umKeyBindDict["RBracket"] = sf::Keyboard::RBracket;
	umKeyBindDict["SemiColon"] = sf::Keyboard::SemiColon;
	umKeyBindDict["Comma"] = sf::Keyboard::Comma;
	umKeyBindDict["Period"] = sf::Keyboard::Period;
	umKeyBindDict["Quote"] = sf::Keyboard::Quote;
	umKeyBindDict["Slash"] = sf::Keyboard::Slash;
	umKeyBindDict["BackSlash"] = sf::Keyboard::BackSlash;
	umKeyBindDict["Tilde"] = sf::Keyboard::Tilde;
	umKeyBindDict["Equal"] = sf::Keyboard::Equal;
	umKeyBindDict["Dash"] = sf::Keyboard::Dash;
	umKeyBindDict["Space"] = sf::Keyboard::Space;
	umKeyBindDict["Return"] = sf::Keyboard::Return;
	umKeyBindDict["BackSpace"] = sf::Keyboard::BackSpace;
	umKeyBindDict["Tab"] = sf::Keyboard::Tab;
	umKeyBindDict["PageUp"] = sf::Keyboard::PageUp;
	umKeyBindDict["PageDown"] = sf::Keyboard::PageDown;
	umKeyBindDict["End"] = sf::Keyboard::End;
	umKeyBindDict["Home"] = sf::Keyboard::Home;
	umKeyBindDict["Insert"] = sf::Keyboard::Insert;
	umKeyBindDict["Delete"] = sf::Keyboard::Delete;
	umKeyBindDict["Add"] = sf::Keyboard::Add;
	umKeyBindDict["Subtract"] = sf::Keyboard::Subtract;
	umKeyBindDict["Multiply"] = sf::Keyboard::Multiply;
	umKeyBindDict["Divide"] = sf::Keyboard::Divide;
	umKeyBindDict["Left"] = sf::Keyboard::Left;
	umKeyBindDict["Right"] = sf::Keyboard::Right;
	umKeyBindDict["Up"] = sf::Keyboard::Up;
	umKeyBindDict["Down"] = sf::Keyboard::Down;
	umKeyBindDict["Numpad0"] = sf::Keyboard::Numpad0;
	umKeyBindDict["Numpad1"] = sf::Keyboard::Numpad1;
	umKeyBindDict["Numpad2"] = sf::Keyboard::Numpad2;
	umKeyBindDict["Numpad3"] = sf::Keyboard::Numpad3;
	umKeyBindDict["Numpad4"] = sf::Keyboard::Numpad4;
	umKeyBindDict["Numpad5"] = sf::Keyboard::Numpad5;
	umKeyBindDict["Numpad6"] = sf::Keyboard::Numpad6;
	umKeyBindDict["Numpad7"] = sf::Keyboard::Numpad7;
	umKeyBindDict["Numpad8"] = sf::Keyboard::Numpad8;
	umKeyBindDict["Numpad9"] = sf::Keyboard::Numpad9;
	umKeyBindDict["F1"] = sf::Keyboard::F1;
	umKeyBindDict["F2"] = sf::Keyboard::F2;
	umKeyBindDict["F3"] = sf::Keyboard::F3;
	umKeyBindDict["F4"] = sf::Keyboard::F4;
	umKeyBindDict["F5"] = sf::Keyboard::F5;
	umKeyBindDict["F6"] = sf::Keyboard::F6;
	umKeyBindDict["F7"] = sf::Keyboard::F7;
	umKeyBindDict["F8"] = sf::Keyboard::F8;
	umKeyBindDict["F9"] = sf::Keyboard::F9;
	umKeyBindDict["F10"] = sf::Keyboard::F10;
	umKeyBindDict["F11"] = sf::Keyboard::F11;
	umKeyBindDict["F12"] = sf::Keyboard::F12;
	umKeyBindDict["F13"] = sf::Keyboard::F13;
	umKeyBindDict["F14"] = sf::Keyboard::F14;
	umKeyBindDict["F15"] = sf::Keyboard::F15;
	umKeyBindDict["Pause"] = sf::Keyboard::Pause;
}

sf::Event Settings::ConvertMouseButtonToEvent(std::string keyvalue)
{
	if (umMouseBindDict.empty())
		BuildMouseBindDictionary();

	std::unordered_map<std::string, sf::Mouse::Button>::const_iterator it = umMouseBindDict.find(keyvalue);
	if (it != umMouseBindDict.end())
	{
		sf::Event eventBind = {};
		eventBind.type = sf::Event::MouseButtonPressed;
		eventBind.mouseButton.button = it->second;
		return eventBind;
	}

	return {}; // Not a mouse binding
}

void Settings::BuildMouseBindDictionary()
{
	umMouseBindDict.clear();

	umMouseBindDict["MouseButtonLeft"] = sf::Mouse::Left;
	umMouseBindDict["MouseButtonRight"] = sf::Mouse::Right;
	umMouseBindDict["MouseButtonMiddle"] = sf::Mouse::Middle;
	umMouseBindDict["MouseButtonXButton1"] = sf::Mouse::XButton1;
	umMouseBindDict["MouseButtonXButton2"] = sf::Mouse::XButton2;
}
