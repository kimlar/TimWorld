#pragma once

#include <SFML/Graphics.hpp>

#include "SharedContext.h"

#include "Frame.h"
#include "Label.h"

class EditBox
{
public:
	enum class EditBoxState { Normal, Editing, EditingHideCursor, Disabled };

	EditBox(SharedContext* sharedContext, sf::Vector2f position, std::string text, EditBoxState state = EditBoxState::Normal);
	virtual ~EditBox();

	void CheckEvents(sf::Event &event);
	void Render();

	SharedContext* GetSharedContext();

	void SetEditBoxState(EditBoxState state);
	EditBoxState GetEditBoxState();

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();

	void SetFrameColor(sf::Color color);

	void SetText(std::string text);
	std::string GetText();

	void SetSkipNextEvent(bool skip);

	bool IsMouseInside();
	

private:
	SharedContext* sharedContext;
	sf::RenderWindow* renderWindow;

	Frame* frame;
	Label* label;

	sf::Vector2f position;
	sf::Vector2f size;
	//std::string labelText;
	int fontSize;

	EditBoxState editBoxState = EditBoxState::Normal;

	int editCursorAtChar = 0;

	int currentCursorPosition = 0;

	bool skipEvent;
	//bool hideTextCursor;

	//enum class EditKeys { Unknown = 0, Enter = 13, BackSpace = 8};

	/*
	void toClipboard(const std::string &s){
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size());
	if (!hg){
	CloseClipboard();
	return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
	}
	*/
};
