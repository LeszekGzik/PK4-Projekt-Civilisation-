#include "GameMap.h"



float GameMap::hexHorizontalSize() const
{
	return hex_edge * sqrt(3);
}

float GameMap::hexVerticalSize() const
{
	return hex_edge * 2;
}

void GameMap::drawGrid(sf::RenderTarget & window, sf::RenderStates states) const
{
	for (int j = 0; j < grid_size.y; j++)
	{
		for (int i = 0; i < grid_size.x; i++)
		{
			sf::CircleShape hex(hex_edge - hex_outline_thickness, 6);
			hex.setPosition(i * hexHorizontalSize() + ((j % 2) * hexHorizontalSize() * 0.5), j * (hex_edge * 1.5));
			hex.setFillColor(sf::Color(0, 0, 0, 0));
			hex.setOutlineColor(hex_outline_color);
			hex.setOutlineThickness(hex_outline_thickness);
			window.draw(hex);
		}
	}
	
}

Field const & GameMap::getField(int xPos, int yPos)
{
	return board[xPos + yPos / 2][yPos];
}

void GameMap::setField(int xPos, int yPos, Field field)
{
	this->board[xPos + yPos / 2][yPos] = field;

}

sf::Vector2f GameMap::getSizeInPixel()
{
	return sf::Vector2f(grid_size.x * hexVerticalSize(), grid_size.y * hexHorizontalSize());
}

void GameMap::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
	if (show_grid)
		drawGrid(window, states);
}


GameMap::GameMap(sf::Vector2i size)
{
	grid_size.x = size.x;
	grid_size.y = size.y;
	board = new Field*[size.x];
	for (int i = 0; i < size.x; i++)
		board[i] = new Field[size.y];
}

GameMap::~GameMap()
{
	for (int i = 0; i < grid_size.x; i++)
	{
		delete board[i];
	}
	delete board;
}
