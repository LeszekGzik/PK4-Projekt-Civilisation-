#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "ApplicationControl.h"

class GameMap : public sf::Drawable
{
private:
	Field ** field;
	bool show_grid;

public:
	bool showGrid() { return show_grid; }
	void showGrid(bool show) { show_grid = show; }

	Field const& getField(int xPos, int yPos);
	void setField(int xPos, int yPos, Field field);

	void draw(sf::RenderTarget& window, sf::RenderStates states) const;

	GameMap(int x_size, int y_size);
	~GameMap();
};

