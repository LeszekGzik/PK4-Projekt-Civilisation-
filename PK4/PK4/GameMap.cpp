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
			getField(OffsetCoords(i, j))->draw(window, states);
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

	if (visibility_px.height + 1 > grid_size.y) // poprawka +1 gdy¿ punkt wskazuje na górny wierzcho³ek hexa??
		visibility_hex.height = grid_size.y;
	else
		visibility_hex.height = visibility_px.height + 1;

	return visibility_hex;
}

Field * GameMap::getField(OffsetCoords pos) const
{
	if (OffsetCoords(grid_size) > pos && pos > OffsetCoords(-1,-1))
		return board[pos.x][pos.y];
	else
		return nullptr;
}


Field * GameMap::getField(PixelCoords pos) const
{
	return getField(hex_style.toAxial(pos));
}

void GameMap::setField(OffsetCoords pos, Field * field)
{
	this->board[pos.x][pos.y] = field;
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
	//implementowaæ w konstruktorze z argumentem
}

GameMap::GameMap(sf::Vector2i size) : grid_size(size)
{
	Field::setStyle(&tex_hex_style);
	Unit::setStyle(&tex_hex_style);

	board = new Field**[size.x];
	for (int i = 0; i < size.x; i++)
	{
		board[i] = new Field*[size.y];
		for (int j = 0; j < size.y; j++)
		{
			setField(OffsetCoords(i, j), new Grass(OffsetCoords(i, j)));
		}
	}
}

GameMap::~GameMap()
{
	for (int i = 0; i < grid_size.x; i++)
	{
		delete board[i];
	}
	delete board;
}
