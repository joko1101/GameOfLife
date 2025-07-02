#pragma once
#include "State.h"
#include "MenuButton.h"

class MainMenuState: public State
{
private:
	std::vector<MenuButton*> buttons;

public:
	MainMenuState(Metadata* md);

	void initButtons();

	void update();

	void draw();
};

