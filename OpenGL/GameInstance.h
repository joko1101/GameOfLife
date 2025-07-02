#pragma once

#include "GameState.h"
#include "MainMenuState.h"
#include "GraphicsController.h"

class GameInstance
{
private:
	Metadata* md;

	GraphicsController* grph_ctrl;

	std::vector<State*> states;

	float dt;
	
public:

	GameInstance(int wndWidth, int wndHeight) 
		: md(Metadata::getInstance(wndWidth, wndHeight, 1))
		, grph_ctrl(GraphicsController::getInstance())
	{
		this->init(wndWidth, wndHeight);
	};

	~GameInstance()
	{
		md, grph_ctrl = nullptr;
		delete md, grph_ctrl;
	};

	void init(int wndWidth, int wndHeight)
	{
		//states.push_back(new MainMenuState(this->md));
		states.push_back(new GameState(this->md));
	}

	int update()
	{	
		states.back()->update();
		return 0;
	}

	int render()
	{
		states.back()->draw();
		return 0;
	}
};