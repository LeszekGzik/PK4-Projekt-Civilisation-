#include "ConstructStable.h"



namespace
{
	const uint32_t ID = 13;
}


ConstructStable::ConstructStable(InGameObject & owner) : Ability(ID, owner)
{

}

ConstructStable::~ConstructStable()
{
}

ContextInfoContent * ConstructStable::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("CONSTRUCT STABLE", sf::Color::Black);
	vector->emplace_back("10 WOOD, 3 IRON", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black);
	return vector;
}

void ConstructStable::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();

	if (field->getImprovement() == nullptr
		&& player.getResources().isAvailable(ResourceType::Wood, 10)
		&& player.getResources().isAvailable(ResourceType::Iron, 3))
	{
		field->newImprovement<Stable>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -10);
		player.getResources().add(ResourceType::Iron, -3);
	}
}
