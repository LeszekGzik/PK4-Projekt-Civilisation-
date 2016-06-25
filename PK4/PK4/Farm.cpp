#include "Farm.h"

namespace
{
	const int ID = 1;
	const int ACTION_POINTS = 1;
}


Farm::Farm(Field* field, Player& owner) : Improvement(field, owner, ID, ACTION_POINTS)
{
}


Farm::~Farm()
{
}

void Farm::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Wood, 2);
	handler.add(ResourceType::Food, 2);
}
