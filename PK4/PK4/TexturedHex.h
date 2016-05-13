#pragma once
#include "Hex.h"
#include "Tileset.h"
#include "GameExceptions.h"

class TexturedHex :
	public Hex
{
public:
	TexturedHex(float _edge = Hex::DEFAULT_EDGE, sf::Color _outline_color = Hex::DEFAULT_OUTLINE_COLOR);
	~TexturedHex();

	sf::VertexArray create(sf::Vector2i _position, Tileset& tileset, int texture);
};

