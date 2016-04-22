#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum Color {Red, Blue, Green};

struct InitSettings
{
	MapSettings map_settings;
	PlayerSettings player_settings;
	
	InitSettings(MapSettings _map_settings, PlayerSettings _player_settings)
	{
		map_settings = _map_settings;
		player_settings = _player_settings;
	}
};

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

struct PlayerSettings
{
	int count;
	std::string * names;
	Color * colors;

	PlayerSettings(int _count, std::string _names[], Color _colors[])
	{
		count = _count;
		colors = _colors;
		names = _names;
	}

	PlayerSettings()
	{

	}
};

struct WorldSettings
{

};