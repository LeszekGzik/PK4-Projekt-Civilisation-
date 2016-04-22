#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "GameMap.h"
#include "GameDefinitions.h"
#include "PlayerState.h"


class GameState
{
private:
	GameMap * game_map;
	sf::RenderWindow * window;
	sf::View world;
	sf::View gui;
	std::vector<PlayerState> players;

public:
	GameMap * getGameMap();

	void initializeSession(InitSettings settings);
	void draw();
	void moveWorld(sf::Vector2f offset);

	GameState(sf::RenderWindow * target);
	~GameState();
};

