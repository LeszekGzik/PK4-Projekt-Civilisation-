#pragma once
#include <SFML/Graphics.hpp>
#include "ObjectStack.h"

class Field : public sf::Drawable
{
private:
	int id;
	ObjectStack object_stack;

protected:

public:
	void draw(sf::RenderTarget & window, sf::RenderStates states) const;

	Field();
	~Field();
};

