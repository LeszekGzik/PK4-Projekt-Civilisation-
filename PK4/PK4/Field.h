#pragma once
#include <SFML/Graphics.hpp>

class Field : public sf::Drawable
{
private:

protected:
	virtual int posInTileset() = 0;

public:
	void draw(sf::RenderTarget & window, sf::RenderStates states) const;

	Field();
	~Field();
};

