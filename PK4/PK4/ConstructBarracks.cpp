#include "ConstructBarracks.h"

namespace
{
	const int ID = 9;
}

ConstructBarracks::ConstructBarracks(InGameObject & owner) : Ability(ID, owner)
{
}


ConstructBarracks::~ConstructBarracks()
{
}

void ConstructBarracks::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();

	if (field->getImprovement() == nullptr 
		&& player.getResources().isAvailable(ResourceType::Wood, 5) 
		&& player.getResources().isAvailable(ResourceType::Iron, 3))
	{
		field->newImprovement<Barracks>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -5);
		player.getResources().add(ResourceType::Iron, -3);
	}
}

ContextInfoContent * ConstructBarracks::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("CONSTRUCT BARRACKS", sf::Color::Black);
	vector->emplace_back("5 WOOD, 3 IRON", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black);
	return vector;
}