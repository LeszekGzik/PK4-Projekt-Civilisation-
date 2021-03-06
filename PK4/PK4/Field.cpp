#include "Field.h"

TexturedHex * Field::hex_style = NULL;


void Field::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(vertex, &(tileset().getTileset()));
	if (deposit != nullptr)
		target.draw(*deposit, states);
	if (improvement != nullptr)
		target.draw(*improvement, states);
	if (!object_stack.empty())
		target.draw(*object_stack.top(), states);
}

void Field::newTurn()
{
	for each (InGameObject * obj in object_stack)
	{
		obj->newTurn();
	}
	if (this->improvement != nullptr)
		this->improvement->newTurn();
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

	if (this->improvement != nullptr)
	{
		if (content != nullptr)
		{
			content->push_back(ContextInfoLine::empty());
			this->improvement->getContextInfoContent(content);
		}
		else
			content = this->improvement->getContextInfoContent();
	}

	return content;
}

void Field::deleteImprovement()
{
	delete this->improvement;
	this->improvement = nullptr;
}

int Field::distanceTo(Field * field)
{
	CubeCoords a = (AxialCoords)field->getPosition();
	CubeCoords b = (AxialCoords)this->getPosition();
	return (abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z)) / 2;
}

Field::Field(int id, OffsetCoords position, int movement_cost, FieldType type) : position(position), movement_cost(movement_cost), type(type)
{
	this->id = id;
	vertex = hex_style->create(position, tileset(), id);
}

Field::~Field()
{
}
