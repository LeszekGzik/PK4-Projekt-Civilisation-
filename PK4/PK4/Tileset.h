#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "GameExceptions.h"
#include "TilesetLoadData.h"


class Tileset
{
private:
	const sf::Color MASK_COLOR = sf::Color(255, 0, 144);

	sf::Texture texture;
	sf::Vector2i tile_size;
	int items_per_row;
	int items;
	std::string name;

	void countItems();
		
public:
	sf::IntRect getTile(int num);
	sf::Texture& getTileset() { return texture; }
	sf::Vector2i getTileSize() { return tile_size; }
	Tileset(TilesetLoadData tileset_data);
	Tileset();
	~Tileset();

	void setTexture(TilesetLoadData tileset_data);
};


