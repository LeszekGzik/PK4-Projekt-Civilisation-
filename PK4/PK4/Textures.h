#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Tileset.h"
#include "TextureLoadException.h"
#include "TilesetLoadData.h"

class Textures
{
private:
	static const TilesetLoadData FIELDS;
	static const TilesetLoadData UNITS;
	static const TilesetLoadData MISC;

	static Tileset* fields;
	static Tileset* units;
	static Tileset* misc;
public:
	static void init();
	static void end();

	static Tileset& tilesetFields() { return *fields; }
	static Tileset& tilesetUnits() { return *units; }
	static Tileset& tilesetMisc() { return *misc; }

	Textures();
	~Textures();
};

