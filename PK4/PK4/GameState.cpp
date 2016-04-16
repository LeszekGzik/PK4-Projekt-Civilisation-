#include "GameState.h"


void GameState::initializeSession()
{
	game_view = window->getDefaultView();
	window->setView(game_view);
}

GameState::GameState(sf::RenderWindow * target)
{
	window = target;
}

GameState::~GameState()
{
}
