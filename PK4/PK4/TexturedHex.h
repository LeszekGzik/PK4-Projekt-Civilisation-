#pragma once
#include "Hex.h"
#include "Tileset.h"
#include "GameExceptions.h"

class TexturedHex :
	public Hex
{
private:
	static const sf::Color DEFAULT_MASK_COLOR;

public:
	TexturedHex(float edge = Hex::DEFAULT_EDGE, sf::Color color = TexturedHex::DEFAULT_MASK_COLOR);
	~TexturedHex();

	DrawableObject create(PixelCoords position, Tileset& tileset, int texture);
	DrawableObject create(OffsetCoords position, Tileset& tileset, int texture);
};

