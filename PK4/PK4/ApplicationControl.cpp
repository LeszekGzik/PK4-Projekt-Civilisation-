#include "ApplicationControl.h"

void ApplicationControl::Run()
{
	current_vmode = sf::VideoMode::getDesktopMode();
	current_vmode.height = current_vmode.height * 0.75;
	current_vmode.width = current_vmode.width * 0.75;
	window.create(current_vmode, "WORKS!");
	startNewGame();
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
