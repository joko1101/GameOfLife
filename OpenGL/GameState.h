#pragma once
#include "State.h"
class GameState: public State
{
private:

	Grid grid;

public: 
	GameState(Metadata* md);

	~GameState();

	void update();

	void draw();
};

