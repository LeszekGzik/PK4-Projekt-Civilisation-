#include "Barracks.h"
#include "TrainArcher.h"
#include "TrainSwordsman.h"

namespace
{
	const int ID = 2;
	const int ACTION_POINTS = 1;
	const std::string NAME = "BARRACKS";
}


Barracks::Barracks(Field * field, Player & owner) : Improvement(field, owner, NAME, ID, ACTION_POINTS)
{
	grantAbility<TrainArcher>();
	grantAbility<TrainSwordsman>();
}

Barracks::~Barracks()
{
}

void Barracks::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Wood, 3);
	handler.add(ResourceType::Iron, 2);
}
