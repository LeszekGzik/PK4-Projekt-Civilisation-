#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Tileset.h"
#include "GameExceptions.h"

class Textures
{
private:
	static const TilesetLoadData BUTTONS;
	static const TilesetLoadData IMPROVEMENTS;
	static const TilesetLoadData FIELDS;
	static const TilesetLoadData UNITS;
	static const TilesetLoadData MISC;
	static const TilesetLoadData CHECKBOX;

	static Tileset* buttons;
	static Tileset* improvements;
	static Tileset* fields;
	static Tileset* units;
	static Tileset* misc;
	static Tileset* checkbox;

	static void free(Tileset*&);

public:
	static void init();
	static void end();

	static Tileset& tilesetButtons() { return *buttons; }
	static Tileset& tilesetImprovements() { return *improvements; }
	static Tileset& tilesetFields() { return *fields; }
	static Tileset& tilesetUnits() { return *units; }
	static Tileset& tilesetMisc() { return *misc; }
	static Tileset& tilesetCheckbox() { return *checkbox; }

	Textures();
	Textures(Textures&) = delete;
	Textures(Textures&&) = delete;
	~Textures();
};

