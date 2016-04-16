#include "GameState.h"


GameMap * GameState::getGameMap()
{
	return game_map; 
}

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
