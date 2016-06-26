#include "TrainSwordsman.h"
#include "Swordsman.h"

namespace
{
	const uint32_t ID = 7;
}

TrainSwordsman::TrainSwordsman(InGameObject & owner) : Ability(ID, owner)
{
}

TrainSwordsman::~TrainSwordsman()
{
}

ContextInfoContent * TrainSwordsman::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("TRAIN SWORDSMAN", sf::Color::Black);
	vector->emplace_back("4 FOOD, 4 IRON", sf::Color::Black);
	vector->emplace_back("COSTS 1 ACTION", sf::Color::Black);
	return vector;
}

void TrainSwordsman::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	ResourcesHandler & resources = player.getResources();

	if (!field->objects().containsUnitType(UnitType::Land)
		&& resources.isAvailable(ResourceType::Food, 4)
		&& resources.isAvailable(ResourceType::Iron, 4))
	{
		InGameObject * archer = field->newUnit<Swordsman>(player);
		archer->spendActionPoints();
		unit.spendActionPoints(1);
		resources.add(ResourceType::Food, -4);
		resources.add(ResourceType::Iron, -4);
	}
}
