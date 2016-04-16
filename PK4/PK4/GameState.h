#pragma once
#include <SFML\Graphics.hpp>
#include "GameMap.h"
#include "ApplicationControl.h"

class GameState
{
private:
	GameMap * game_map;
	sf::RenderWindow * window;
	sf::View game_view;

public:
	GameMap * getGameMap();

	void initializeSession();

	GameState(sf::RenderWindow * target);
	~GameState();
};

