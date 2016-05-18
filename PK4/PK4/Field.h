#pragma once
#include <SFML/Graphics.hpp>
#include "EngineDefinitions.h"
#include "ObjectStack.h"
#include "TexturedHex.h"
#include "Textures.h"
#include "Improvement.h"

class Field : public sf::Drawable
{
private:
	int id;
	ObjectStack object_stack;
	Improvement improvement;
	DrawableObject vertex;

	static TexturedHex hex_style;

public:
	static Tileset tileset() { return Textures::tilesetFields(); }
	void addObject(InGameObject * object) { object_stack.add(object); }
	static TexturedHex& hex() { return hex_style; }

	Field(int id, OffsetCoords position);
	~Field();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

