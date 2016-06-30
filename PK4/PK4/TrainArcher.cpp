#include "TrainArcher.h"

namespace
{
	const int ID = 6;
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
	vector->emplace_back("3 FOOD, 2 IRON, 3 WOOD", sf::Color::Black);
	vector->emplace_back("COSTS 1 ACTION", sf::Color::Black);
	vector->emplace_back("DOUBLE STRENGTH ON HILLS", sf::Color::Blue);
	return vector;
}

void TrainArcher::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	ResourcesHandler & resources = player.getResources();

	if ( !field->objects().containsUnitType(UnitType::Land)
		&& resources.isAvailable(ResourceType::Food, 3)
		&& resources.isAvailable(ResourceType::Iron, 2)
		&& resources.isAvailable(ResourceType::Wood, 3))
	{
		InGameObject * archer = field->newUnit<Archer>(player);
		archer->spendActionPoints();
		unit.spendActionPoints(1);
		resources.add(ResourceType::Food, -3);
		resources.add(ResourceType::Iron, -2);
		resources.add(ResourceType::Wood, -3);
	}
}
