#include "GameMap.h"



Field const & GameMap::getField(int xPos, int yPos)
{
	return field[xPos + yPos / 2][yPos];
}

void GameMap::setField(int xPos, int yPos, Field field)
{
	this->field[xPos + yPos / 2][yPos] = field;

}

void GameMap::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
	
}


GameMap::GameMap(int x_size, int y_size)
{
	field = new Field*[x_size];
	for (int i = 0; i < x_size; i++)
		field[i] = new Field[y_size];
}

GameMap::~GameMap()
{
}
