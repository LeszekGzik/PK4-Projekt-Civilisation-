#include "Barracks.h"

namespace
{
	const int ID = 1;
	const int ACTION_POINTS = 1;
}


Barracks::Barracks(Field * field, Player & owner) : Improvement(field, owner, ID, ACTION_POINTS)
{
	grantAbility<TrainArcher>();
}

Barracks::~Barracks()
{
}

void Barracks::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Wood, 3);
	handler.add(ResourceType::Iron, 2);
}
