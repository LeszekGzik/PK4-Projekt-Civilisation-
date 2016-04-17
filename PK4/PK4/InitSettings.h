#pragma once
#include <SFML/Graphics.hpp>

struct MapSettings
{
	sf::Vector2i size;
	MapSettings(sf::Vector2i _size) : size(_size)
	{

	}
	MapSettings()
	{

	}
};

struct InitSettings
{
	MapSettings map_settings;
	
	InitSettings(MapSettings _map_settings)
	{
		map_settings = _map_settings;
	}
};

struct WorldSettings
{

};