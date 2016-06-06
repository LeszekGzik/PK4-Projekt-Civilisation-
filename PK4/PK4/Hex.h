#pragma once
#include <SFML/Graphics.hpp>
#include "EngineDefinitions.h"
#include "GameDefinitions.h"
#include <math.h>

class Hex
{
public:
	static const float DEFAULT_EDGE;
	static const sf::Color DEFAULT_COLOR;

	float horizontalSize() const { return horizontal; }
	float verticalSize() const { return vertical; }
	float edgeSize() const { return edge; }
	sf::Color getColor() const { return color; }
	PixelCoords toPixel(OffsetCoords position) const;
	AxialCoords toAxial(PixelCoords position) const;
	AxialCoords round(sf::Vector2f pos) const;

	virtual DrawableObject create(PixelCoords position) const sealed;
	virtual DrawableObject create(OffsetCoords position) const sealed;

	Hex(float edge = DEFAULT_EDGE, sf::Color color = DEFAULT_COLOR);
	~Hex();

private:

	float edge;
	float horizontal;
	float vertical;
	sf::Color color;
};

