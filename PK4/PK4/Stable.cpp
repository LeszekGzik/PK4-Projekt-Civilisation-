#include "Stable.h"
#include "TrainHorseman.h"

namespace
{
	const int ID = 6;
	const int ACTION_POINTS = 1;
	const std::string NAME = "STABLES";
}

Stable::Stable(Field * field, Player & owner) : Improvement(field, owner, NAME, ID, ACTION_POINTS)
{
	grantAbility<TrainHorseman>();
}

Stable::~Stable()
{
}

void Stable::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Wood, 8);
	handler.add(ResourceType::Iron, 2);
}
