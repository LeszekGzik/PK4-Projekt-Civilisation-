#include "ConstructDragonLair.h"

namespace
{
	const uint32_t ID = 18;
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
	vector->emplace_back("10 WOOD, 10 IRON, 10 GEMS", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black); 
	vector->emplace_back("TRAINS DRAGONS", sf::Color::Blue);
	return vector;
}

void ConstructDragonLair::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();

	if (field->getImprovement() == nullptr
		&& player.getResources().isAvailable(ResourceType::Wood, 10)
		&& player.getResources().isAvailable(ResourceType::Iron, 10)
		&& player.getResources().isAvailable(ResourceType::Gems, 10))
	{
		field->newImprovement<DragonLair>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -10);
		player.getResources().add(ResourceType::Iron, -10);
		player.getResources().add(ResourceType::Gems, -10);
	}
}
