#include "Field.h"

TexturedHex * Field::hex_style = NULL;


void Field::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(vertex, &(tileset().getTileset()));
	if (!object_stack.empty())
	{
		target.draw(*object_stack.top(), states);
	}
}

ContextInfoContent * Field::getContextInfoContent()
{
	if (object_stack.empty())
		return nullptr;
	else
		return object_stack.top()->getContextInfoContent();
}

Field::Field(int id, OffsetCoords position)
{
	this->id = id;
	vertex = hex_style->create(position, tileset(), id);
}

Field::~Field()
{
}
