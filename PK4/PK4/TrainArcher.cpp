#include "TrainArcher.h"

namespace
{
	const int ID = 1;
}

TrainArcher::TrainArcher(InGameObject & owner) : Ability(ID, owner)
{
}


TrainArcher::~TrainArcher()
{
}

ContextInfoContent * TrainArcher::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("TRAIN ARCHER", sf::Color::Black);
	vector->emplace_back("3 FOOD, 3 IRON, 2 WOOD", sf::Color::Black);
	vector->emplace_back("COSTS 1 ACTION", sf::Color::Black);
	return vector;
}

void TrainArcher::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	ResourcesHandler & resources = player.getResources();

	if (
		 resources.isAvailable(ResourceType::Food, 3)
		&& resources.isAvailable(ResourceType::Iron, 3)
		&& resources.isAvailable(ResourceType::Wood, 2))
	{
		field->newUnit<Archer>(player);
		unit.spendActionPoints(1);
		resources.add(ResourceType::Food, -3);
		resources.add(ResourceType::Iron, -3);
		resources.add(ResourceType::Wood, -2);
	}
}
