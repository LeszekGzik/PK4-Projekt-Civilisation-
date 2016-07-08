#include "TrainHorseman.h"


namespace
{
	const uint32_t ID = 16;
}


TrainHorseman::TrainHorseman(InGameObject & owner) : Ability(ID, owner, _not_targetable)
{
}

TrainHorseman::~TrainHorseman()
{
}

ContextInfoContent * TrainHorseman::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("TRAIN HORSEMAN", sf::Color::Black);
	vector->emplace_back("8 FOOD, 1 IRON, 4 WOOD", sf::Color::Black);
	vector->emplace_back("COSTS 1 ACTION", sf::Color::Black);
	return vector;
}

void TrainHorseman::use(Field * target)
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	ResourcesHandler & resources = player.getResources();

	if (!field->objects().containsUnitType(UnitType::Land)
		&& resources.isAvailable(ResourceType::Food, 8)
		&& resources.isAvailable(ResourceType::Iron, 1)
		&& resources.isAvailable(ResourceType::Wood, 4))
	{
		InGameObject * archer = field->newUnit<Horseman>(player);
		archer->spendActionPoints();
		unit.spendActionPoints(1);
		resources.add(ResourceType::Food, -8);
		resources.add(ResourceType::Iron, -1);
		resources.add(ResourceType::Wood, -4);
	}
}
