#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "MainMenu.h"
#include "GameDefinitions.h"

const float DEFAULT_SCROLL_SPEED = 0.3f;
const float DEFAULT_SCROLL_DISTANCE = 30.f;

class ApplicationControl
{
private:
	GameState * game_state;
	sf::VideoMode current_vmode;
	sf::RenderWindow window;

	float scroll_speed = DEFAULT_SCROLL_SPEED;
	float scroll_distance = DEFAULT_SCROLL_DISTANCE;

	bool movingWorld(sf::Vector2f& offset);
	void gameLoop();
public:
	void startNewGame();

	sf::VideoMode const & getCurrentVideoMode() { return current_vmode; }

	void Run();
	ApplicationControl();
	~ApplicationControl();
};

