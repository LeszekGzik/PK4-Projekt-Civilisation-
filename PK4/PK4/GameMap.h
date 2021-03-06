#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <unordered_map>
#include <typeinfo>
#include "Fields.h"
#include "Hex.h"
#include "TexturedHex.h"
#include "Textures.h"
#include "Units.h"
#include "Deposits.h"
#include "MapFileReader.h"

class GameMap : public sf::Drawable
{
private:
	typedef std::pair<OffsetCoords, int> NodePriorityPair;
	typedef Field*** FieldMap;

	int pathfinding_max_iterations = 100;
	int pathfinding_hash_bucket = 30;

	bool show_grid;
	FieldMap board;
	Hex& hex_style;
	TexturedHex tex_hex_style = TexturedHex(hex_style);
	sf::Vector2u grid_size;

	sf::IntRect visibilityCheck(sf::View view) const;
	void drawGrid(sf::RenderTarget& window, sf::RenderStates states, sf::IntRect visibility) const;
	void drawMap(sf::RenderTarget& window, sf::RenderStates states, sf::IntRect visibility) const;

public:

	void loadFromFile(std::string & file_path, std::vector<Player> & players);

	bool showGrid() { return show_grid; }
	void showGrid(bool show) { show_grid = show; }
	void setField(OffsetCoords pos, Field * field);
	template<typename TField> TField * newField(OffsetCoords position);
	int getDistance(const AxialCoords& from, const AxialCoords& to) const;
	Field * getField(OffsetCoords pos) const;
	Field * getField(PixelCoords pos) const;
	FieldMap const& getFields() const { return this->board; }
	Field * neighbour(OffsetCoords position, int32_t direction) const;
	sf::Vector2f getSizeInPixel();

	void moveUnit(OffsetCoords from, OffsetCoords to);
	void newTurn();
	void resetMap(sf::Vector2u new_size);
	void draw(sf::RenderTarget& window, sf::RenderStates states) const;

	GameMap(Hex& style);
	~GameMap();
};

template<typename TField>
inline TField * GameMap::newField(OffsetCoords position)
{
	static_assert(std::is_base_of<Field, TField>::value, "Input type must derive from Field type");
	TField * field = new TField(position);
	if (this->grid_size.x > position.x && this->grid_size.y > position.y && position.x >= 0 && position.y >= 0)
		this->board[position.x][position.y] = field;
	else
		throw IndexOutOfRangeException("Game Map", 0);
	return field;
}
