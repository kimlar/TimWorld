#pragma once

#include <unordered_map>
#include <vector>

#include "Window.h"

class Settings
{
public:
	void Setup();
	void Load();
	void Save();

	//
	// *** Public service getters ***
	//
	bool GetSkipIntro();
	bool GetToolTip();
	std::string GetLanguage();
	//float GetMouseSensitivity();
	float GetCameraMoveSpeed();
	sf::Event GetMoveCameraLeft();
	sf::Event GetMoveCameraRight();
	sf::Event GetMoveCameraUp();
	sf::Event GetMoveCameraDown();
	int GetWindowWidth();
	int GetWindowHeight();
	bool GetVSync();
	int GetFramerateLimit();
	DisplayMode GetDisplayMode();
	DisplayMode GetDefaultFullscreenMode();
	int GetAntiAliasing();
	bool GetShowFPS();
	int GetMasterVolume();
	int GetMusicVolume();
	int GetSoundFxVolume();
	int GetVoiceVolume();
	
	//
	// *** Special service getter ***
	//
	std::string GetEventString(sf::Event &event);

private:
	void Process(std::string line);

	// Internals - Process()
	std::string RemoveClutter(std::string line);
	bool SkipTooSmallLine(std::string line);
	bool FindKeyword(std::string keyword, std::string line);
	std::string GetKeyvalue(std::string line);

	// Event binding
	sf::Event GetEventBinding(std::string keyword, std::string keyvalue);
	sf::Event ConvertKeyboardKeyToEvent(std::string keyvalue);
	void BuildKeyboardBindDictionary();
	sf::Event ConvertMouseButtonToEvent(std::string keyvalue);
	void BuildMouseBindDictionary();
	
	//
	std::vector<std::string> keywords;
	std::unordered_map<std::string, std::string> umSettings;
	std::vector<std::string> bindKeywords;
	std::unordered_map<std::string, sf::Keyboard::Key> umKeyBindDict;
	std::unordered_map<std::string, sf::Mouse::Button> umMouseBindDict;
};
