#include "Tileset.h"

void Tileset::countItems()
{
	sf::Vector2u tex_size = texture.getSize();
	items = (tex_size.x / tile_size.x) * (tex_size.y / tile_size.y);
}

sf::IntRect Tileset::getTile(int num)
{
	if (num > 0 && num <= items)
	{
		int row = (num - 1) / items_per_row;
		int col = (num - 1) % items_per_row;
		return sf::IntRect(sf::Vector2i(col * tile_size.x, row * tile_size.y), tile_size);
	}
	else
	{
		throw IndexOutOfRangeException(name, num);
	}
}

Tileset::Tileset(TilesetLoadData tileset_data)
{
	setTexture(tileset_data);
}

Tileset::Tileset()
{
}

Tileset::~Tileset()
{
}

void Tileset::setTexture(TilesetLoadData tileset_data)
{
	sf::Image image;
	if (!image.loadFromFile(tileset_data.path))
		throw FileLoadException(tileset_data.path);
	image.createMaskFromColor(MASK_COLOR);
	texture.loadFromImage(image);
	name = tileset_data.path;
	items_per_row = image.getSize().x / tileset_data.size.x;
	tile_size = tileset_data.size;
	countItems();
}
