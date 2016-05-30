#pragma once
#include <SFML/Graphics.hpp>

const static struct ENGINE
{
	static const float basic_unit;
	static const float flag_size_factor;
	static const float scroll_speed;
	static const float scroll_distance;
};

typedef sf::Vector2i OffsetCoords;
typedef sf::Vector2i AxialCoords;
typedef sf::Vector2f PixelCoords;
typedef sf::VertexArray DrawableObject;