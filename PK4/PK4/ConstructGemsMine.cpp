#include "ConstructGemsMine.h"

namespace
{
	const uint32_t ID = 12;
}

ConstructGemsMine::ConstructGemsMine(InGameObject & owner) : Ability(ID, owner, _not_targetable)
{
}

ConstructGemsMine::~ConstructGemsMine()
{
}

ContextInfoContent * ConstructGemsMine::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("CONSTRUCT GEMS MINE", sf::Color::Black);
	vector->emplace_back("10 WOOD, 5 IRON", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black);
	vector->emplace_back("PRODUCES GEMS", sf::Color::Blue);
	vector->emplace_back("REQUIRES GEMS DEPOSIT", sf::Color::Red);
	return vector;
}

void ConstructGemsMine::use(Field * target)
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();

	if (field->getImprovement() == nullptr
		&& dynamic_cast<GemsDeposit*>(field->getDeposit()) != nullptr
		&& player.getResources().isAvailable(ResourceType::Wood, 10)
		&& player.getResources().isAvailable(ResourceType::Iron, 5))
	{
		field->newImprovement<GemsMine>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -10);
		player.getResources().add(ResourceType::Iron, -5);
	}
}
