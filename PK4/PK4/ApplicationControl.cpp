#include "ApplicationControl.h"


void ApplicationControl::run()
{
	try
	{
		sf::ContextSettings context_settings;
		context_settings.antialiasingLevel = 8;

		current_vmode = sf::VideoMode::getDesktopMode();
		current_vmode.height = current_vmode.height * 0.75;
		current_vmode.width = current_vmode.width * 0.75;
		window.create(current_vmode, "WORKS!", sf::Style::Default, context_settings);
		window.setVerticalSyncEnabled(true);

		Textures::init();
		Fonts::init();
	}
	catch(std::exception const& ex)
	{
		std::cout << ex.what() << std::endl;
		std::cin.get();
		return;
	}

	loop();

	Textures::end();
	Fonts::end();
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

LoopExitCode ApplicationControl::gameLoop(InitSettings * settings)
{
	if (game_state != NULL)
		return LoopExitCode::Exit;

	settings = new InitSettings(MapSettings(sf::Vector2i(12, 6)), PlayerSettings(0, NULL, NULL));

	game_state = new GameState(&window);
	game_state->initializeSession(*settings);

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

	return LoopExitCode::Exit;
}

LoopExitCode ApplicationControl::menuLoop(InitSettings *& settings)
{
	MainMenu menu(window, current_vmode);
	LoopExitCode exit = menu.loop();
	settings = menu.getInitSettings();
	return exit;
}

void ApplicationControl::loop()
{
	InitSettings * settings = NULL;

	LoopExitCode loop = LoopExitCode::Menu;
	while (loop != LoopExitCode::Exit)
	{
		switch (loop)
		{
		case Menu:
			loop = menuLoop(settings);
			break;
		case Play:
			loop = gameLoop(settings);
			break;
		default:
			loop = LoopExitCode::Exit;
			break;
		}

		if (settings != NULL)
			delete settings;
	}
}

ApplicationControl::ApplicationControl()
{
	
}


ApplicationControl::~ApplicationControl()
{
	Textures::end();
	delete game_state;
}
