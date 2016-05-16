#include "TexturedHex.h"


TexturedHex::TexturedHex(float _edge, sf::Color _outline_color) : Hex(_edge, _outline_color)
{
}

TexturedHex::~TexturedHex()
{
}

sf::VertexArray TexturedHex::create(OffsetCoords position, Tileset& tileset, int texture)
{
	return create(coords(position), tileset, texture);
}

sf::VertexArray TexturedHex::create(PixelCoords position, Tileset& tileset, int texture)
{
	float edge = edgeSize();
	float horizontal = horizontalSize();

	sf::IntRect tex_rect = tileset.getTile(texture);
	sf::VertexArray hex(sf::TrianglesFan, 8);

	hex[0].position = sf::Vector2f(position.x + 0.5 * horizontal, position.y + edge);
	hex[1].position = sf::Vector2f(position.x, position.y + 0.5 * edge);
	hex[2].position = sf::Vector2f(position.x + 0.5 * horizontal, position.y);
	hex[3].position = sf::Vector2f(position.x + horizontal, position.y + 0.5 * edge);
	hex[4].position = sf::Vector2f(position.x + horizontal, position.y + 1.5 * edge);
	hex[5].position = sf::Vector2f(position.x + 0.5 * horizontal, position.y + 2 * edge);
	hex[6].position = sf::Vector2f(position.x, position.y + 1.5 * edge);
	hex[7].position = sf::Vector2f(position.x, position.y + 0.5 * edge);

	position.x = tex_rect.left;
	position.y = tex_rect.top;

	edge = 20;
	horizontal = 20 * sqrt(3);

	hex[0].texCoords = sf::Vector2f(position.x + 0.5 * horizontal, position.y + edge);
	hex[1].texCoords = sf::Vector2f(position.x, position.y + 0.5 * edge);
	hex[2].texCoords = sf::Vector2f(position.x + 0.5 * horizontal, position.y);
	hex[3].texCoords = sf::Vector2f(position.x + horizontal, position.y + 0.5 * edge);
	hex[4].texCoords = sf::Vector2f(position.x + horizontal, position.y + 1.5 * edge);
	hex[5].texCoords = sf::Vector2f(position.x + 0.5 * horizontal, position.y + 2 * edge);
	hex[6].texCoords = sf::Vector2f(position.x, position.y + 1.5 * edge);
	hex[7].texCoords = sf::Vector2f(position.x, position.y + 0.5 * edge);

	return hex;
}
