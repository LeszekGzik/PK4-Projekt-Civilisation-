#include "Fonts.h"

const std::string Fonts::TEXT = "/Fonts/arial.ttf";

sf::Font * Fonts::font_text = NULL;

void Fonts::init()
{
	char windir[MAX_PATH];
	GetWindowsDirectory(windir, MAX_PATH);
	std::string path(windir);

	path += TEXT;
	font_text = new sf::Font;
	if (!font_text->loadFromFile(path))
		throw FileLoadException(path);
}

void Fonts::end()
{
	delete font_text;
}

Fonts::Fonts()
{
}


Fonts::~Fonts()
{
	
}
