#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"

const float DEFAULT_HEX_EDGE = 60;
const float DEFAULT_HEX_OUTLINE_THICKNESS = 2;
const sf::Color DEFAULT_HEX_OUTLINE_COLOR(255, 0, 0, 255);

class GameMap : public sf::Drawable
{
private:
	Field ** board;
	bool show_grid;
	float hex_edge = DEFAULT_HEX_EDGE;
	float hex_outline_thickness = DEFAULT_HEX_OUTLINE_THICKNESS;
	sf::Color hex_outline_color = DEFAULT_HEX_OUTLINE_COLOR;
	sf::Vector2i grid_size;

	float hexHorizontalSize() const;
	float hexVerticalSize() const;
	void drawGrid(sf::RenderTarget& window, sf::RenderStates states) const;
public:
	bool showGrid() { return show_grid; }
	void showGrid(bool show) { show_grid = show; }

	Field const& getField(int xPos, int yPos);
	void setField(int xPos, int yPos, Field field);
	sf::Vector2f getSizeInPixel();

	void draw(sf::RenderTarget& window, sf::RenderStates states) const;

	GameMap(sf::Vector2i size);
	~GameMap();
};

