#include "Unit.h"

ObjectStyle * Unit::object_style = NULL;

void Unit::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(token);
	target.draw(flag);
}


void Unit::setStyle(TexturedHex * style)
{
	Hex * hex = style;
	object_style = new ObjectStyle(*hex);
}

Unit::Unit(int id, OffsetCoords position, Player& owner) : owner(owner), id(id), InGameObject()
{
	flag = object_style->createFlag(position, id);
	token = object_style->createToken(position, id, owner);
}

Unit::~Unit()
{
}
