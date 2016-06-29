#include "LumberjacksHut.h"

namespace
{
	const int ID = 3;
	const int ACTION_POINTS = 1;
	const std::string NAME = "LUMBERJACK'S HUT";
}


LumberjacksHut::LumberjacksHut(Field * field, Player & owner) : Improvement(field, owner, NAME, ID, ACTION_POINTS)
{
	grantAbility<TrainWorker>();
}

LumberjacksHut::~LumberjacksHut()
{
}

void LumberjacksHut::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Wood, 3);
}

void LumberjacksHut::newTurn()
{
	setActionPoints(getMaxActionPoints());
	getOwner().getResources().add(ResourceType::Wood, production);
}
