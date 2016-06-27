#include "ConstructDragonLair.h"

namespace
{
	const uint32_t ID = 1;
}

ConstructDragonLair::ConstructDragonLair(InGameObject & owner) : Ability(ID, owner)
{
}


ConstructDragonLair::~ConstructDragonLair()
{
}

ContextInfoContent * ConstructDragonLair::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("CONSTRUCT DRAGON LAIR", sf::Color::Black);
	vector->emplace_back("15 WOOD, 15 IRON, GEMS 15", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black);
	return vector;
}

void ConstructDragonLair::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();

	if (field->getImprovement() == nullptr
		&& player.getResources().isAvailable(ResourceType::Wood, 15)
		&& player.getResources().isAvailable(ResourceType::Iron, 15)
		&& player.getResources().isAvailable(ResourceType::Gems, 15))
	{
		field->newImprovement<DragonLair>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -15);
		player.getResources().add(ResourceType::Iron, -15);
		player.getResources().add(ResourceType::Gems, -15);
	}
}
