#pragma once
#include <SFML/Graphics.hpp>
#include "InGameObject.h"
#include "GameDefinitions.h"
#include "EngineDefinitions.h"
#include "Textures.h"
#include "TexturedHex.h"
#include "Player.h"
#include "Flag.h"

class Unit : public InGameObject
{
private:
	static const sf::Vector2f DEfAULT_FLAG_SIZE;
	static const int DEFAULT_MISC_ID = 1;

	int id;
	int misc_id;
	Player& owner;
	DrawableObject vertex;
	sf::Sprite flag;

	static TexturedHex hex_style;
	static Flag flag_style;

	void initFlag(OffsetCoords position);

public:
	static Tileset& unitTileset() { return Textures::tilesetUnits(); }
	static Tileset& miscTileset() { return Textures::tilesetMisc(); }

	Player& getOwner() { return owner; }

	Unit(int id, OffsetCoords position, Player& owner);
	~Unit();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

