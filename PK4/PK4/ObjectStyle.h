#pragma once
#include <SFML\Graphics.hpp>
#include "EngineDefinitions.h"
#include "GameDefinitions.h"
#include "Hex.h"
#include "Tileset.h"
#include "Player.h"
#include "Textures.h"


class ObjectStyle
{
private:
	Hex& hex_style;
	sf::Vector2f size;
	sf::Vector2f flag_size;

	PixelCoords bannerPosition(OffsetCoords position);
	PixelCoords flagPosition(OffsetCoords position, sf::Vector2i flag_size);
	Tileset& unitTileset;
	Tileset& miscTileset;
	Tileset& impTileset;
	void scaleBanner(sf::Sprite& sprite);
	void scaleToken(sf::Sprite& sprite);
	void scaleFlag(sf::Sprite& sprite);

public:
	sf::Sprite createBanner(OffsetCoords position, int texture_id);
	sf::Sprite createToken(OffsetCoords position, int texture_id, Player &player);
	sf::Sprite createGround(OffsetCoords position, int texture_id);
	sf::Sprite createFlag(OffsetCoords position, int texture_id, Player &player);
	void move(OffsetCoords position, sf::Sprite& sprite);
	void move(PixelCoords to, AxialCoords from, sf::Sprite& sprite);
	Hex const& hex() { return hex_style; }

	ObjectStyle(Hex& hex_style);
	~ObjectStyle();
};

