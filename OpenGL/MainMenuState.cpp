#include "MainMenuState.h"
#include "GraphicsController.h"

MainMenuState::MainMenuState(Metadata* md)
	: State(md)
{
	this->initButtons();
}

void MainMenuState::initButtons()
{
	this->buttons.push_back(new MenuButton(0, 200, 200, 50, "Start New"));
	this->buttons.push_back(new MenuButton(0, 100, 200, 50, "Settings"));
	this->buttons.push_back(new MenuButton(0, -100, 200, 50, "[No Function]"));
	this->buttons.push_back(new MenuButton(0, -200, 200, 50, "Quit"));
}

void MainMenuState::update()
{
	for (auto& button : buttons)
	{
		button->update();
	}
}

void MainMenuState::draw()
{
	GraphicsController::getShader("menu_button")->use();
	for (auto& button : buttons)
	{
		button->draw();
	}
}