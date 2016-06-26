#include "Farm.h"
#include "TrainWorker.h"

namespace
{
	const int ID = 1;
	const int ACTION_POINTS = 1;
	const std::string NAME = "FARM";
}


Farm::Farm(Field* field, Player& owner) : Improvement(field, owner, NAME, ID, ACTION_POINTS)
{
	grantAbility<TrainWorker>();
}


Farm::~Farm()
{
}

void Farm::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Wood, 2);
	handler.add(ResourceType::Food, 2);
}

void Farm::newTurn()
{
	setActionPoints(getMaxActionPoints());
	getOwner().getResources().add(ResourceType::Food, production);
}
