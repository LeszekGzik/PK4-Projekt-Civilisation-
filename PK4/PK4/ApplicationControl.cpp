#include "ApplicationControl.h"
#include <iostream>

void ApplicationControl::Run()
{
	current_vmode = sf::VideoMode::getDesktopMode();
	current_vmode.height = current_vmode.height * 0.75;
	current_vmode.width = current_vmode.width * 0.75;
	window.create(current_vmode, "WORKS!");
	startNewGame();
}

bool ApplicationControl::movingWorld(sf::Vector2f & offset)
{
	bool moved = false;
	offset = sf::Vector2f(0, 0);
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	if (mouse_pos.x < scroll_distance)
	{
		offset.x = -scroll_speed;
		moved = true;
	}
	else if (window.getSize().x - mouse_pos.x < scroll_distance)
	{
		offset.x = scroll_speed;
		moved = true;
	}
	if (mouse_pos.y < scroll_distance)
	{
		offset.y = -scroll_speed;
		moved = true;
	}
	else if (window.getSize().y - mouse_pos.y < scroll_distance)
	{
		offset.y = scroll_speed;
		moved = true;
	}
	return moved;
}

void ApplicationControl::gameLoop()
{
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		sf::Vector2f move_offset;
		bool moved = movingWorld(move_offset);

		game_state->moveWorld(move_offset);

		window.clear();
		game_state->draw();
		window.display();
	}
}

void ApplicationControl::startNewGame()
{
	if (game_state != NULL)
		return;

	game_state = new GameState(&window);
	game_state->initializeSession(
		InitSettings(MapSettings(sf::Vector2i(12, 6)))
		);
	gameLoop();
}

ApplicationControl::ApplicationControl()
{
	
}


ApplicationControl::~ApplicationControl()
{
}
