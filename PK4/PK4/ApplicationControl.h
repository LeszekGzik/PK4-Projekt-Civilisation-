#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "GameState.h"
#include "MainMenu.h"
#include "GameDefinitions.h"
#include "EngineDefinitions.h"
#include "GameExceptions.h"
#include "Textures.h"
#include "TexturedHex.h"
#include "Fonts.h"
#include "PageControl.h"
#include "Button.h"

class ApplicationControl
{
private:
	sf::VideoMode current_vmode;
	sf::RenderWindow window;

	LoopExitCode gameLoop(InitSettings * settings);
	LoopExitCode menuLoop(InitSettings *& settings);
public:
	void run();
	void loop();
	sf::VideoMode const & getCurrentVideoMode() { return current_vmode; }

	ApplicationControl();
	~ApplicationControl();
};

