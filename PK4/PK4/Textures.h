#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Tileset.h"
#include "TextureLoadException.h"
#include "TilesetLoadData.h"

const TilesetLoadData Textures::FIELDS = TilesetLoadData("gfx\\fields.png", sf::Vector2i(40, 40), 40);

static class Textures
{
private:
	static const TilesetLoadData FIELDS;

	static Tileset fields;
	static Tileset units;
public:
	static void init()
	{
		fields.setTexture(FIELDS);
	}

	static Tileset& tilesetFields() { return fields; }
	static Tileset& tilesetUnits() { return units; }

	Textures();
	~Textures();
};

