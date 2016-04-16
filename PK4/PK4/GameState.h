#pragma once
#include <SFML\Graphics.hpp>
#include "GameMap.h"

class GameState
{
private:
	GameMap * game_map;
	sf::RenderWindow * window;
	sf::View game_view;

public:
	GameMap * getGameMap() { return game_map; } 

	void initializeSession();

	GameState(sf::RenderWindow * target);
	~GameState();
};

