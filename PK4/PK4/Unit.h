#pragma once
#include <SFML/Graphics.hpp>
#include "InGameObject.h"
#include "GameDefinitions.h"
#include "EngineDefinitions.h"
#include "Textures.h"
#include "TexturedHex.h"
#include "ObjectStyle.h"
#include "Player.h"
#include <algorithm>
#include <list>

class Unit : public InGameObject
{
private:

	int id;
	int misc_id;
	Player& owner;
	sf::Sprite flag;
	sf::Sprite token;

	static ObjectStyle * object_style;
public:
	static Tileset& unitTileset() { return Textures::tilesetUnits(); }
	static Tileset& miscTileset() { return Textures::tilesetMisc(); }
	static void setStyle(TexturedHex * style);

	Player& getOwner() { return owner; }

	Unit(int id, OffsetCoords position, Player& owner);
	~Unit();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

