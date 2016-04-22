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
	sf::IntRect visibility = visibilityCheck(window.getView());
	
	int i_start, j_start, i_stop, j_stop;

	if (visibility.left < 0)
		i_start = 0;
	else
		i_start = visibility.left;

	if (visibility.top < 0)
		j_start = 0;
	else
		j_start = visibility.top;

	if (visibility.width > grid_size.x)
		i_stop = grid_size.x;
	else
		i_stop = visibility.width;

	if (visibility.height + 1 > grid_size.y) // poprawka +1 gdy¿ punkt wskazuje na górny wierzcho³ek hexa??
		j_stop = grid_size.y;
	else
		j_stop = visibility.height + 1;

	for (int j = j_start; j < j_stop; j++)
	{
		for (int i = i_start; i < i_stop; i++)
		{
			float x = i * hexHorizontalSize() + ((j % 2) * hexHorizontalSize() * 0.5);
			float y = j * hex_edge * 1.5;
			float h = hexHorizontalSize();
			sf::VertexArray hex(sf::LinesStrip, 7);
			hex[0].position = sf::Vector2f(x, y + 0.5 * hex_edge);
			hex[1].position = sf::Vector2f(x + 0.5 * h, y);
			hex[2].position = sf::Vector2f(x + h, y + 0.5 * hex_edge);
			hex[3].position = sf::Vector2f(x + h, y + 1.5 * hex_edge);
			hex[4].position = sf::Vector2f(x + 0.5 * h, y + 2 * hex_edge);
			hex[5].position = sf::Vector2f(x, y + 1.5 * hex_edge);
			hex[6].position = sf::Vector2f(x, y + 0.5 * hex_edge);

			for (int k = 0; k < 7; k++)
			{
				hex[k].color = hex_outline_color;
			}

			/*sf::CircleShape hex(hex_edge - hex_outline_thickness, 6);
			hex.setPosition(i * hexHorizontalSize() + ((j % 2) * hexHorizontalSize() * 0.5), j * (hex_edge * 1.5));
			hex.setFillColor(sf::Color(0, 0, 0, 0));
			hex.setOutlineColor(hex_outline_color);
			hex.setOutlineThickness(hex_outline_thickness);*/
			window.draw(hex);
		}
	}
}

sf::IntRect GameMap::visibilityCheck(sf::View view) const
{
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();
	sf::IntRect visibility;

	visibility.left = floorf((center.x - size.x / 2) / hexHorizontalSize());
	visibility.top = floorf((center.y - size.y / 2) / hexVerticalSize());
	visibility.width = ceilf ((center.x + size.x / 2) / hexHorizontalSize());
	visibility.height = ceilf((center.y + size.y / 2) / hexVerticalSize());

	return visibility;
}

Field const & GameMap::getField(int xPos, int yPos)
{
	return *board[xPos + yPos / 2][yPos];
}

void GameMap::setField(int xPos, int yPos, Field * field)
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
	board = new Field**[size.x];
	for (int i = 0; i < size.x; i++)
		board[i] = new Field*[size.y];
}

GameMap::~GameMap()
{
	for (int i = 0; i < grid_size.x; i++)
	{
		delete board[i];
	}
	delete board;
}
