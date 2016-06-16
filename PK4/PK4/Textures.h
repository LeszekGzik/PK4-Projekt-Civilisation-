#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Tileset.h"
#include "GameExceptions.h"

class Textures
{
private:
	static const TilesetLoadData IMPROVEMENTS;
	static const TilesetLoadData FIELDS;
	static const TilesetLoadData UNITS;
	static const TilesetLoadData MISC;

	static Tileset* improvements;
	static Tileset* fields;
	static Tileset* units;
	static Tileset* misc;

public:
	static void init();
	static void end();

	static Tileset& tilesetImprovements() { return *improvements; }
	static Tileset& tilesetFields() { return *fields; }
	static Tileset& tilesetUnits() { return *units; }
	static Tileset& tilesetMisc() { return *misc; }

	Textures();
	~Textures();
};

