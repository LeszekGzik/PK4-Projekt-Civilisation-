#include "Unit.h"

TexturedHex Unit::hex_style;

void Unit::managedDraw(sf::RenderTarget & target, sf::RenderStates states)
{
	target.draw(vertex, &unitTileset().getTileset());
}

Unit::Unit(int id, OffsetCoords position) : InGameObject()
{
	this->id = id;
	vertex = hex_style.create(position, unitTileset(), id);
}

Unit::~Unit()
{
}
