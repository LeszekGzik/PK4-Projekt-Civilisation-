#include "IronMine.h"

namespace
{
	const uint32_t ID = 4;
	const std::string NAME = "IRON ORE MINE";
	const int ACTION_POINTS = 1;
}


IronMine::IronMine(Field * field, Player & owner) : Improvement(field, owner, NAME, ID, ACTION_POINTS)
{
	grantAbility<TrainWorker>();
}

IronMine::~IronMine()
{
}

void IronMine::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Wood, 3);
	handler.add(ResourceType::Iron, 2);
}

void IronMine::newTurn()
{
	setActionPoints(getActionPoints());
	getOwner().getResources().add(ResourceType::Iron, production);
}
