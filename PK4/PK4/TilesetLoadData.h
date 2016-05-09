#pragma once
#include <sfml/graphics.hpp>
#include <string>

struct TilesetLoadData
{
	std::string path;
	sf::Vector2i size;
	int items;

	TilesetLoadData(std::string _path, sf::Vector2i _size, int _items)
	{
		path = _path;
		size = _size;
		items = _items;
	}

	TilesetLoadData()
	{

	}
};