#include "Stable.h"

namespace
{
	const int ID = 1;
	const int ACTION_POINTS = 1;
	const std::string NAME = "STABLES";
}

Stable::Stable(Field * field, Player & owner) : Improvement(field, owner, NAME, ID, ACTION_POINTS)
{
}

Stable::~Stable()
{
}

void Stable::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Wood, 5);
	handler.add(ResourceType::Iron, 2);
}
