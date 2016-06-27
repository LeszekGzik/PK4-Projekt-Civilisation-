#include "TrainHorseman.h"


namespace
{
	const uint32_t ID = 1;
}


TrainHorseman::TrainHorseman(InGameObject & owner) : Ability(ID, owner)
{
}

TrainHorseman::~TrainHorseman()
{
}

ContextInfoContent * TrainHorseman::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("TRAIN HORSEMAN", sf::Color::Black);
	vector->emplace_back("8 FOOD, 4 IRON, 1 WOOD", sf::Color::Black);
	vector->emplace_back("COSTS 1 ACTION", sf::Color::Black);
	return vector;
}

void TrainHorseman::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	ResourcesHandler & resources = player.getResources();

	if (!field->objects().containsUnitType(UnitType::Land)
		&& resources.isAvailable(ResourceType::Food, 8)
		&& resources.isAvailable(ResourceType::Iron, 4)
		&& resources.isAvailable(ResourceType::Wood, 1))
	{
		InGameObject * archer = field->newUnit<Horseman>(player);
		archer->spendActionPoints();
		unit.spendActionPoints(1);
		resources.add(ResourceType::Food, -8);
		resources.add(ResourceType::Iron, -4);
		resources.add(ResourceType::Wood, -1);
	}
}
