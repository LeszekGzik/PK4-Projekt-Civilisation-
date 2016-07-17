#include "ConstructIronMine.h"

namespace
{
	const uint32_t ID = 11;
}


ConstructIronMine::ConstructIronMine(InGameObject & owner) : Ability(ID, owner, _not_targetable)
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
	vector->emplace_back("PRODUCES IRON", sf::Color::Blue);
	vector->emplace_back("REQUIRES IRON ORE DEPOSIT", sf::Color::Red);
	return vector;
}

void ConstructIronMine::use(Field * target)
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();

	if (field->getImprovement() == nullptr
		&& dynamic_cast<IronDeposit*>(field->getDeposit()) != nullptr
		&& player.getResources().isAvailable(ResourceType::Wood, 10))
	{
		field->newImprovement<IronMine>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -10);
	}
}
