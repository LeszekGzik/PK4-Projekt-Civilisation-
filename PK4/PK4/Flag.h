#pragma once
#include "EngineDefinitions.h"
#include "Textures.h"
#include "Hex.h"

class Flag
{
private:
	static const sf::Vector2f DEFAULT_SIZE;
	sf::Vector2f size;

public:
	PixelCoords getPosition(Hex& hex_style, OffsetCoords position);
	sf::Vector2f getScale();

	Flag(sf::Vector2f size = Flag::DEFAULT_SIZE);
	~Flag();
};

