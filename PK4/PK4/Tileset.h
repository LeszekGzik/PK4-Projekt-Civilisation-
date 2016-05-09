#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureLoadException.h"
#include "TextureOutOfRangeException.h"
#include "TilesetLoadData.h"


class Tileset
{
private:
	sf::Texture texture;
	sf::Vector2i tile_size;
	int items_per_row;
	int items;
	std::string name;

	void countItems();
		
public:
	sf::IntRect getTile(int num);
	sf::Texture const& getTileset() { return texture; }
	Tileset(TilesetLoadData tileset_data);
	Tileset();
	~Tileset();

	void setTexture(TilesetLoadData tileset_data);
};


