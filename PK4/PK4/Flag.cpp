#include "Flag.h"

const sf::Vector2f Flag::DEFAULT_SIZE = sf::Vector2f(_ENGINE::default_unit / 2, _ENGINE::default_unit / 2);

PixelCoords Flag::getPosition(Hex & hex_style, OffsetCoords position)
{
	PixelCoords position_px = hex_style.coords(position);
	position_px.x += (hex_style.horizontalSize() - size.x) / 2;
	position_px.y += (hex_style.verticalSize() - size.y) / 2;

	return position_px;
}

sf::Vector2f Flag::getScale()
{
	sf::Vector2i tile = Textures::tilesetUnits().getTileSize();
	return sf::Vector2f(size.x / tile.x, size.y / tile.y);
}

Flag::Flag(sf::Vector2f size) : size(size)
{
}


Flag::~Flag()
{
}
