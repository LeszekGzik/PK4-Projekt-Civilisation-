#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>
#include "GameExceptions.h"

class Fonts
{
private:
	static const std::string TEXT;

	static sf::Font * font_text;

public:
	static sf::Font& fontText() { return *font_text; }
	static void init();
	static void end();

	Fonts();
	~Fonts();
};

