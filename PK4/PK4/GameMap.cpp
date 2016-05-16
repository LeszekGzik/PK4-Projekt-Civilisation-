#include "GameMap.h"
#include "Textures.h"




void GameMap::drawGrid(sf::RenderTarget & window, sf::RenderStates states, sf::IntRect visibility) const
{
	for (int j = visibility.top; j < visibility.height; j++)
	{
		for (int i = visibility.left; i < visibility.width; i++)
		{
			sf::VertexArray hex = hex_style.create(OffsetCoords(i, j));
			window.draw(hex);
		}
	}
}

void GameMap::drawMap(sf::RenderTarget & window, sf::RenderStates states, sf::IntRect visibility) const
{
	for (int j = visibility.top; j < visibility.height; j++)
	{
		for (int i = visibility.left; i < visibility.width; i++)
		{
			getFieldOffset(i, j).draw(window, states);
		}
	}
}

sf::IntRect GameMap::visibilityCheck(sf::View view) const
{
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();
	sf::IntRect visibility_px;
	sf::IntRect visibility_hex;

	visibility_px.left = floorf((center.x - size.x / 2) / hex_style.horizontalSize());
	visibility_px.top = floorf((center.y - size.y / 2) / hex_style.verticalSize());
	visibility_px.width = ceilf((center.x + size.x / 2) / hex_style.horizontalSize());
	visibility_px.height = ceilf((center.y + size.y / 2) / hex_style.verticalSize());

	if (visibility_px.left < 0)
		visibility_hex.left = 0;
	else
		visibility_hex.left = visibility_px.left;

	if (visibility_px.top < 0)
		visibility_hex.top = 0;
	else
		visibility_hex.top = visibility_px.top;

	if (visibility_px.width > grid_size.x)
		visibility_hex.width = grid_size.x;
	else
		visibility_hex.width = visibility_px.width;

	if (visibility_px.height + 1 > grid_size.y) // poprawka +1 gdy� punkt wskazuje na g�rny wierzcho�ek hexa??
		visibility_hex.height = grid_size.y;
	else
		visibility_hex.height = visibility_px.height + 1;

	return visibility_hex;
}

Field & GameMap::getFieldOffset(int xPos, int yPos) const
{
	return *board[xPos][yPos];
}

void GameMap::setFieldOffset(int xPos, int yPos, Field * field)
{
	this->board[xPos][yPos] = field;
}

sf::Vector2f GameMap::getSizeInPixel()
{
	return sf::Vector2f(grid_size.x * hex_style.verticalSize(), grid_size.y * hex_style.horizontalSize());
}

void GameMap::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
	sf::IntRect visibility = visibilityCheck(window.getView());

	drawMap(window, states, visibility);
	if (show_grid)
		drawGrid(window, states, visibility);
}


GameMap::GameMap()
{
	
}

GameMap::GameMap(sf::Vector2i size)
{
	grid_size.x = size.x;
	grid_size.y = size.y;
	board = new Field**[size.x];
	for (int i = 0; i < size.x; i++)
	{
		board[i] = new Field*[size.y];
		for (int j = 0; j < size.y; j++)
		{
			setFieldOffset(i, j, new Grass(sf::Vector2i(i, j)));
		}
	}
	Player * p = new Player();
	getFieldOffset(5, 5).addObject(new Archer(OffsetCoords(5, 5), *p));
}

GameMap::~GameMap()
{
	for (int i = 0; i < grid_size.x; i++)
	{
		delete board[i];
	}
	delete board;
}
