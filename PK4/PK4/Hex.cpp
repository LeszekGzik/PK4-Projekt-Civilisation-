#include "Hex.h"

const float Hex::DEFAULT_EDGE = ENGINE::basic_unit / 2;
const sf::Color Hex::DEFAULT_COLOR(255, 0, 0, 255);

PixelCoords Hex::toPixel(OffsetCoords position) const
{
	//float x = position.x * horizontal + ((position.y & 1) * horizontal * 0.5);
	float x = (position.x + 0.5 * (position.y & 1)) * horizontal;
	float y = position.y * edge * 1.5;
	return sf::Vector2f(x, y);
}

AxialCoords Hex::toAxial(PixelCoords pos) const
{
	pos.x -= horizontal * 0.5;
	pos.y -= edge;
	sf::Vector2f hex;
	float size = edge;
	hex.x = (pos.x * sqrt(3) / 3 - pos.y / 3) / size;
	hex.y = pos.y * 2 / 3 / size;
	return round(hex);
}

AxialCoords Hex::round(sf::Vector2f pos) const
{
	sf::Vector3i r(roundf(pos.x), roundf(-pos.x - pos.y), roundf(pos.y));
	sf::Vector3f diff(fabsf(r.x - pos.x), fabsf(r.y + pos.x + pos.y), fabsf(r.z - pos.y));

	if (diff.x > diff.y && diff.x > diff.z)
		r.x = -r.y - r.z;
	else if (diff.y > diff.z)
		r.y = -r.x - r.z;
	else
		r.z = -r.x - r.y;

	AxialCoords c(r.x, r.z);
	OffsetCoords ff = c;
	return AxialCoords(r.x, r.z);
}


sf::VertexArray Hex::create(OffsetCoords position) const
{
	PixelCoords position_px = toPixel(position);
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

