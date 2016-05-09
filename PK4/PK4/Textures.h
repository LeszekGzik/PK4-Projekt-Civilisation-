#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Tileset.h"
#include "TextureLoadException.h"
#include "TilesetLoadData.h"

static class Textures
{
private:
	static const TilesetLoadData FIELDS;

	static Tileset * fields;
	static Tileset * units;
public:
	static void init();
	static void end();

	static Tileset& tilesetFields() { return *fields; }
	static Tileset& tilesetUnits() { return *units; }

	Textures();
	~Textures();
};

