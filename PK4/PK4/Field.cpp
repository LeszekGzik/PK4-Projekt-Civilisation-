#include "Field.h"

TexturedHex * Field::hex_style = NULL;


void Field::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(vertex, &(tileset().getTileset()));
	if (improvement != nullptr)
		target.draw(*improvement, states);
	if (!object_stack.empty())
	{
		target.draw(*object_stack.top(), states);
	}
}

void Field::newTurn()
{
	for each (InGameObject * obj in object_stack)
	{
		obj->newTurn();
	}
}

ContextInfoContent * Field::getContextInfoContent()
{
	ContextInfoContent * content = nullptr;

	if (!object_stack.empty())
	{
		content = object_stack.top()->getContextInfoContent();
		if (content == nullptr)
			return content;
		int items = object_stack.size();
		if (items > 1)
		{
			content->push_back(ContextInfoLine::empty());
			content->push_back(ContextInfoLine("+" + std::to_string(--items) + " MORE", sf::Color::Black));
		}
	}

	return content;
}

void Field::deleteImprovement()
{
	delete this->improvement;
	this->improvement = nullptr;
}

Field::Field(int id, OffsetCoords position, int movement_cost, FieldType type) : position(position), movement_cost(movement_cost), type(type)
{
	this->id = id;
	vertex = hex_style->create(position, tileset(), id);
}

Field::~Field()
{
}
