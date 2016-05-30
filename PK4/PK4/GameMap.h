#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Fields.h"
#include "Hex.h"
#include "TexturedHex.h"
#include "Textures.h"
#include "Units.h"

class GameMap : public sf::Drawable
{
private:
	bool show_grid;
	Field *** board;
	Hex hex_style;
	TexturedHex tex_hex_style;
	sf::Vector2i grid_size;

	sf::IntRect visibilityCheck(sf::View view) const;
	void drawGrid(sf::RenderTarget& window, sf::RenderStates states, sf::IntRect visibility) const;
	void drawMap(sf::RenderTarget& window, sf::RenderStates states, sf::IntRect visibility) const;

public:
	bool showGrid() { return show_grid; }
	void showGrid(bool show) { show_grid = show; }
	void setFieldOffset(int xPos, int yPos, Field * field);
	Field& getFieldOffset(int xPos, int yPos) const;
	sf::Vector2f getSizeInPixel();
	void draw(sf::RenderTarget& window, sf::RenderStates states) const;

	GameMap();
	GameMap(sf::Vector2i size);
	~GameMap();
};

