#include "InGameObject.h"

ObjectStyle * InGameObject::object_style = nullptr;

void InGameObject::setStyle(Hex * style)
{
	Hex * hex = style;
	object_style = new ObjectStyle(*style);
}

void InGameObject::clear()
{
	if (object_style != nullptr)
		delete object_style;
}

InGameObject::InGameObject(AxialCoords position, Player& owner) : position(position), owner(owner)
{
}

InGameObject::~InGameObject()
{
}
