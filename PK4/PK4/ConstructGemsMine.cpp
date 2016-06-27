#include "ConstructGemsMine.h"

namespace
{
	const uint32_t ID = 12;
}

ConstructGemsMine::ConstructGemsMine(InGameObject & owner) : Ability(ID, owner)
{
}

ConstructGemsMine::~ConstructGemsMine()
{
}

ContextInfoContent * ConstructGemsMine::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("CONSTRUCT GEMS MINE", sf::Color::Black);
	vector->emplace_back("16 WOOD, 8 IRON", sf::Color::Black);
	vector->emplace_back("COSTS REMAINING ACTIONS", sf::Color::Black);
	vector->emplace_back("REQUIRES GEMS DEPOSIT", sf::Color::Red);
	return vector;
}

void ConstructGemsMine::use()
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	Hills * test_field = dynamic_cast<Hills*>(field);

	if (field->getImprovement() == nullptr && test_field != nullptr
		&& dynamic_cast<GemsDeposit*>(test_field->getDeposit()) != nullptr
		&& player.getResources().isAvailable(ResourceType::Wood, 16)
		&& player.getResources().isAvailable(ResourceType::Iron, 8))
	{
		field->newImprovement<GemsMine>(player);
		unit.spendActionPoints();
		player.getResources().add(ResourceType::Wood, -16);
		player.getResources().add(ResourceType::Iron, -8);
	}
}
