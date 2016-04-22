#pragma once
#include <SFML\Graphics.hpp>
#include "GameMap.h"
#include "InitSettings.h"


class GameState
{
private:
	GameMap * game_map;
	sf::RenderWindow * window;
	sf::View world;
	sf::View gui;

public:
	GameMap * getGameMap();

	void initializeSession(InitSettings settings);
	void draw();
	void moveWorld(sf::Vector2f offset);

	GameState(sf::RenderWindow * target);
	~GameState();
};

