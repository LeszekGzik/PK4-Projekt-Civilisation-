#include "Hex.h"

const float Hex::DEFAULT_EDGE = ENGINE::basic_unit / 2;
const sf::Color Hex::DEFAULT_COLOR(255, 0, 0, 255);

PixelCoords Hex::coords(OffsetCoords position) const
{
	float x = position.x * horizontal + ((position.y % 2) * horizontal * 0.5);
	float y = position.y * edge * 1.5;
	return sf::Vector2f(x, y);
}

sf::VertexArray Hex::create(OffsetCoords position) const
{
	PixelCoords position_px = coords(position);
	return create(position_px);
}


sf::VertexArray Hex::create(PixelCoords position) const
{
	sf::VertexArray hex(sf::LinesStrip, 7);

	hex[0].position = sf::Vector2f(position.x, position.y + 0.5 * edge);
	hex[1].position = sf::Vector2f(position.x + 0.5 * horizontal, position.y);
	hex[2].position = sf::Vector2f(position.x + horizontal, position.y + 0.5 * edge);
	hex[3].position = sf::Vector2f(position.x + horizontal, position.y + 1.5 * edge);
	hex[4].position = sf::Vector2f(position.x + 0.5 * horizontal, position.y + 2 * edge);
	hex[5].position = sf::Vector2f(position.x, position.y + 1.5 * edge);
	hex[6].position = sf::Vector2f(position.x, position.y + 0.5 * edge);

	for (int k = 0; k < 7; k++)
	{
		hex[k].color = color;
	}

	return hex;
}

Hex::Hex(float edge, sf::Color color) : edge(edge), color(color)
{
	horizontal = edge * sqrt(3);
	vertical = edge * 2;
}

Hex::~Hex()
{
}

