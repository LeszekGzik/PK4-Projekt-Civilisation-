#include "GemsMine.h"



namespace
{
	const uint32_t ID = 5;
	const std::string NAME = "GEMS' MINE";
	const int ACTION_POINTS = 1;
}


GemsMine::GemsMine(Field * field, Player & owner) : Improvement(field, owner, NAME, ID, ACTION_POINTS)
{
	grantAbility<TrainWorker>();
}

GemsMine::~GemsMine()
{
}

void GemsMine::grantLoot(ResourcesHandler & handler)
{
	handler.add(ResourceType::Wood, 4);
	handler.add(ResourceType::Gems, 2);
	handler.add(ResourceType::Iron, 2);
}

void GemsMine::newTurn()
{
	setActionPoints(getMaxActionPoints());
	getOwner().getResources().add(ResourceType::Gems, production);
}
