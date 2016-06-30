#include "ConstructFarm.h"

class Farm;

namespace
{
	const uint32_t ID = 5;
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
	Grass * test_ptr = dynamic_cast<Grass*>(field);

	if (field->getImprovement() == nullptr && test_ptr != nullptr
		&& player.getResources().isAvailable(ResourceType::Wood, 4))
	{
		field->newImprovement<Farm>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -4);
	}
}

ContextInfoContent * ConstructFarm::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("CONSTRUCT FARM", sf::Color::Black);
	vector->emplace_back("4 WOOD", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black);
	vector->emplace_back("PRODUCES FOOD", sf::Color::Blue);
	vector->emplace_back("REQUIRES GRASS", sf::Color::Red);
	return vector;
}

#include "Farm.h"