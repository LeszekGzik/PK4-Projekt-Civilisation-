#include "GameState.h"


void GameState::draw()
{
	//window->setView(world);
	window->draw(*game_map);
}

GameMap * GameState::getGameMap()
{
	return game_map; 
}

void GameState::initializeSession(InitSettings settings)
{
	gui = window->getDefaultView();
	game_map = new GameMap(settings.map_settings.size);
	world.setSize(game_map->getSizeInPixel());
	game_map->showGrid(true);
}

GameState::GameState(sf::RenderWindow * target)
{
	window = target;
}

GameState::~GameState()
{
}
