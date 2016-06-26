#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "Hex.h"

class Field;

class Deposit : public sf::Drawable
{
private:
	static Hex * style;
	Field * field;

	uint32_t id;
	sf::Sprite sprite;

	void init();

public:
	static void setStyle(Hex * hex) { style = hex; }

	Deposit(Field * field, uint32_t id);
	~Deposit();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

#include "Field.h"