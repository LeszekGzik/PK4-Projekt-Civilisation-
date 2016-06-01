#pragma once
#include <SFML/Graphics.hpp>

const static struct ENGINE
{
	static const float basic_unit;
	static const float flag_size_factor;
	static const float scroll_speed;
	static const float scroll_distance;
	static const int min_players = 2;
	static const int max_players = 4;
};

typedef sf::Vector2i OffsetCoords;
typedef sf::Vector2i AxialCoords;
typedef sf::Vector2f PixelCoords;
typedef sf::VertexArray DrawableObject;