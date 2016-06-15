#include "InGameObject.h"


InGameObject::InGameObject(AxialCoords position, Player& owner) : position(position), owner(owner)
{
}

InGameObject::~InGameObject()
{
}
