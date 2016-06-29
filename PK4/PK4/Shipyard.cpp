#include "Shipyard.h"


namespace
{
	const uint32_t ID = 7;
	const std::string NAME = "SHIPYARD";
	const int ACTION_POINTS = 1;
}

Shipyard::Shipyard(Field * field, Player & owner) : Improvement(field, owner, NAME, ID, ACTION_POINTS)
{
	grantAbility<BuildShip>();
}

Shipyard::~Shipyard()
{
}

void Shipyard::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Wood, 5);
	handler.add(ResourceType::Iron, 2);
}
