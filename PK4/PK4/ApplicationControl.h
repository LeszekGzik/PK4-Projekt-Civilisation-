#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "MainMenu.h"


class ApplicationControl
{
private:
	GameState * game_state;
	sf::VideoMode current_vmode;
	sf::RenderWindow window;

	void gameLoop();
public:
	void startNewGame();

	sf::VideoMode const & getCurrentVideoMode() { return current_vmode; }

	void Run();
	ApplicationControl();
	~ApplicationControl();
};

