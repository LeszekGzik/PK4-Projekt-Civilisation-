#include "ConstructIronMine.h"

namespace
{
	const uint32_t ID = 11;
}


ConstructIronMine::ConstructIronMine(InGameObject & owner) : Ability(ID, owner)
{

}

ConstructIronMine::~ConstructIronMine()
{
}

ContextInfoContent * ConstructIronMine::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("CONSTRUCT IRON ORE MINE", sf::Color::Black);
	vector->emplace_back("10 WOOD", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black);
	return vector;
}

void ConstructIronMine::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	Hills * test_field = dynamic_cast<Hills*>(field);

	if (field->getImprovement() == nullptr && test_field != nullptr 
		&& dynamic_cast<IronDeposit*>(test_field->getDeposit()) != nullptr
		&& player.getResources().isAvailable(ResourceType::Wood, 10))
	{
		field->newImprovement<IronMine>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -10);
	}
}
