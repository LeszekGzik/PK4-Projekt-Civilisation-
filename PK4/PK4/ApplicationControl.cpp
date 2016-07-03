#include "ApplicationControl.h"


void ApplicationControl::run()
{
	try
	{
		createWindow(false);

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

void ApplicationControl::createWindow(bool fullscreen)
{
	sf::ContextSettings context_settings;
	context_settings.antialiasingLevel = 8;

	current_vmode = sf::VideoMode::getFullscreenModes()[0];
	if (!fullscreen) 
		current_vmode.height *= 0.9;
	window.create(current_vmode, "Unforgotten Realms", fullscreen ? sf::Style::Fullscreen : sf::Style::Close, context_settings);
	window.setVerticalSyncEnabled(true);
}

LoopExitCode ApplicationControl::gameLoop(InitSettings * settings)
{
	if (settings->fullscreen)
		createWindow(true);

	GameState game(window, current_vmode);
	LoopExitCode exit;
	try
	{
		game.init(settings);
		exit = game.loop();
	}
	catch (std::exception & ex)
	{
		MessageBoxA(nullptr, ex.what(), "Run-time error", MB_ICONERROR | MB_OK);
		exit = LoopExitCode::Exit;
	}
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
	Textures::end();
}


ApplicationControl::~ApplicationControl()
{
}
