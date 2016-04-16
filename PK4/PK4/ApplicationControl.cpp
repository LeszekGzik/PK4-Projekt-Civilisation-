#include "ApplicationControl.h"



void ApplicationControl::startNewGame()
{
	if (game_state != NULL)
		return;

	game_state = new GameState(&window);
	game_state->initializeSession();
}

void ApplicationControl::Run()
{
	current_vmode = sf::VideoMode::getDesktopMode();
	current_vmode.height = current_vmode.height * 0.75;
	current_vmode.width = current_vmode.width * 0.75;
	window.create(current_vmode, "WORKS!");
	MainMenu menu(sf::IntRect(32, 32, 256, 256));

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
		window.draw(menu);
		window.display();
	}
}

ApplicationControl::ApplicationControl()
{
	
}


ApplicationControl::~ApplicationControl()
{
}
