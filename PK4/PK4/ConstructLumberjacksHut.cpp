#include "ConstructLumberjacksHut.h"

namespace
{
	const uint32_t ID = 10;
}

ConstructLumberjacksHut::ConstructLumberjacksHut(InGameObject & owner) : Ability(ID, owner, _not_targetable)
{
}


ConstructLumberjacksHut::~ConstructLumberjacksHut()
{
}

ContextInfoContent * ConstructLumberjacksHut::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("CONSTRUCT LUMBERJACK'S HUT", sf::Color::Black);
	vector->emplace_back("4 WOOD", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black);
	vector->emplace_back("PRODUCES WOOD", sf::Color::Blue);
	vector->emplace_back("REQUIRES FOREST", sf::Color::Red);
	return vector;
}

void ConstructLumberjacksHut::use(Field * target)
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	Forest * test_ptr = dynamic_cast<Forest*>(field);

	if (field->getImprovement() == nullptr && test_ptr != nullptr
		&& player.getResources().isAvailable(ResourceType::Wood, 4))
	{
		field->newImprovement<LumberjacksHut>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -4);
	}
}
