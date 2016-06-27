#include "DragonLair.h"

namespace
{
	const int ID = 2;
	const int ACTION_POINTS = 1;
	const std::string NAME = "BARRACKS";
}


DragonLair::DragonLair(Field * field, Player & owner) : Improvement(field, owner, NAME, ID, ACTION_POINTS)
{
	grantAbility<HireDragon>();
}

DragonLair::~DragonLair()
{
}

void DragonLair::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Gems, 5);
	handler.add(ResourceType::Wood, 5);
	handler.add(ResourceType::Iron, 5);
}
