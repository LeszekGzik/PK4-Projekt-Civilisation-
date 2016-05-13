#include "Hex.h"

const float Hex::DEFAULT_EDGE = 60;
const sf::Color Hex::DEFAULT_OUTLINE_COLOR(255, 0, 0, 255);

float Hex::horizontalSize()
{
	return horizontal;
}

float Hex::verticalSize()
{
	return vertical;
}

float Hex::edgeSize()
{
	return edge;
}

sf::VertexArray Hex::create(sf::Vector2i position)
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
		hex[k].color = outline_color;
	}

	return hex;
}

Hex::Hex(float _edge, sf::Color _outline_color)
{
	edge = _edge;
	outline_color = _outline_color;

	horizontal = edge * sqrt(3);
	vertical = edge * 2;
}

Hex::~Hex()
{
}

