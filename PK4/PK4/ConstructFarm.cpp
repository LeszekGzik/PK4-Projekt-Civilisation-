#include "ConstructFarm.h"

class Farm;

namespace
{
	const uint32_t ID = 1;
}

ConstructFarm::ConstructFarm(InGameObject & owner) : Ability(ID, owner)
{
	
}


ConstructFarm::~ConstructFarm()
{
}

void ConstructFarm::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();

	if (field->getImprovement() == nullptr && player.getResources().isAvailable(ResourceType::Wood, 5))
	{
		field->newImprovement<Farm>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -5);
	}
}

ContextInfoContent * ConstructFarm::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("CONSTRUCT FARM", sf::Color::Black);
	vector->emplace_back("5 WOOD", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black);
	return vector;
}

#include "Farm.h"