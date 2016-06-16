#include "ApplicationControl.h"


void ApplicationControl::run()
{
	try
	{
		sf::ContextSettings context_settings;
		context_settings.antialiasingLevel = 8;

		current_vmode = sf::VideoMode::getFullscreenModes()[0];
		window.create(current_vmode, "WORKS!", sf::Style::Fullscreen, context_settings);
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

LoopExitCode ApplicationControl::gameLoop(InitSettings * settings)
{
	GameState game(window, current_vmode, settings);
	LoopExitCode exit = game.loop();
	return exit;
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

		if (settings != NULL && loop != LoopExitCode::Play)
			delete settings;
	}
}

ApplicationControl::ApplicationControl()
{
	
}


ApplicationControl::~ApplicationControl()
{
	Textures::end();
}
