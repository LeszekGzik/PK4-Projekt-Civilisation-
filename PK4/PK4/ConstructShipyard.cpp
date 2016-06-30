#include "ConstructShipyard.h"

namespace
{
	const uint32_t ID = 14;
}


ConstructShipyard::ConstructShipyard(InGameObject & owner) : Ability(ID, owner)
{
}

ConstructShipyard::~ConstructShipyard()
{
}

ContextInfoContent * ConstructShipyard::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("CONSTRUCT SHIPYARD", sf::Color::Black);
	vector->emplace_back("10 WOOD, 5 IRON", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black);
	vector->emplace_back("PRODUCES SHIPS", sf::Color::Blue);
	return vector;
}

void ConstructShipyard::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();

	if (field->getImprovement() == nullptr
		&& player.getResources().isAvailable(ResourceType::Wood, 10)
		&& player.getResources().isAvailable(ResourceType::Iron, 5))
	{
		field->newImprovement<Shipyard>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -10);
		player.getResources().add(ResourceType::Iron, -5);
	}
}
