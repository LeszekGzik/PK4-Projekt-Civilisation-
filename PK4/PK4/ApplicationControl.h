#pragma once
#include "GameState.h"
#include "MainMenu.h"
#include <vector>
#include "Event.h"
#include "Event.cpp"

class ApplicationControl
{
private:
	GameState * game_state;
	sf::VideoMode current_vmode;
	sf::RenderWindow window;
public:
	void startNewGame();
	sf::VideoMode const & getCurrentVideoMode() { return current_vmode; }

	void Run();
	ApplicationControl();
	~ApplicationControl();
};

