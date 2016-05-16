#pragma once
#include <SFML/Graphics.hpp>
#include "InGameObject.h"
#include "GameDefinitions.h"
#include "EngineDefinitions.h"
#include "Textures.h"
#include "TexturedHex.h"

class Unit : public InGameObject
{
private:
	int id;
	int misc_id;
	Color owner;
	DrawableObject vertex;

	static TexturedHex hex_style;

public:
	static Tileset unitTileset() { return Textures::tilesetUnits(); }
	static Tileset miscTileset() { return Textures::tilesetMisc(); }

	Color getOwner() { return owner; }

	Unit(int id, OffsetCoords position);
	~Unit();

	virtual void managedDraw(sf::RenderTarget & target, sf::RenderStates states);
};

