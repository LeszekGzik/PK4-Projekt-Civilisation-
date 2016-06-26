#pragma once
#include <sfml/graphics.hpp>
#include <string>

struct TilesetLoadData
{
	std::string path;
	sf::Vector2i size;

	TilesetLoadData(std::string _path, sf::Vector2i _size) : path(_path), size(_size)
	{
		
	}

	TilesetLoadData()
	{

	}
};