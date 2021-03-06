#pragma once
#include "Hex.h"
#include "Tileset.h"
#include "GameExceptions.h"

const sf::Color DEFAULT_MASK_COLOR = sf::Color(255, 255, 255, 255);

class TexturedHex :
	public Hex
{
private:
	float xs;

public:
	TexturedHex(const Hex & style, sf::Color color = DEFAULT_MASK_COLOR);
	TexturedHex(float edge = Hex::DEFAULT_EDGE, sf::Color color = DEFAULT_MASK_COLOR);
	~TexturedHex();

	DrawableObject create(PixelCoords position, Tileset& tileset, int texture);
	DrawableObject create(OffsetCoords position, Tileset& tileset, int texture);

	DrawableObject create(PixelCoords position, Tileset& tileset, int texture, sf::Color color);
	DrawableObject create(OffsetCoords position, Tileset& tileset, int texture, sf::Color color);
};

