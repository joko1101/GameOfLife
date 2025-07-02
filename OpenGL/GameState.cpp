#include "GameState.h"

GameState::GameState(Metadata* md)
	: State(md)
	, grid(md->getWndWidth(), md->getWndHeight(), 10, 5)
{}

GameState::~GameState()
{
}

void GameState::update()
{
	this->grid.update();
}

void GameState::draw()
{
	this->grid.draw();
}