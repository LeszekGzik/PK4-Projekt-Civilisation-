#pragma once
#include <SFML/Graphics.hpp>
#include "EngineDefinitions.h"

class Hex
{
public:
	static const float DEFAULT_EDGE;
	static const sf::Color DEFAULT_OUTLINE_COLOR;

	float horizontalSize() const;
	float verticalSize() const;
	float edgeSize() const;
	PixelCoords coords(OffsetCoords position) const;

	virtual DrawableObject create(PixelCoords position) const sealed;
	virtual DrawableObject create(OffsetCoords position) const sealed;

	Hex(float _edge = DEFAULT_EDGE, sf::Color _outline_color = DEFAULT_OUTLINE_COLOR);
	~Hex();

private:

	float edge;
	float horizontal;
	float vertical;
	sf::Color outline_color;
};

