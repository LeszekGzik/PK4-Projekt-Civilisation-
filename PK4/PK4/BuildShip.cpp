#include "BuildShip.h"


namespace
{
	const uint32_t ID = 15;
}


BuildShip::BuildShip(InGameObject & owner) : Ability(ID, owner, _not_targetable)
{
}

BuildShip::~BuildShip()
{
}

ContextInfoContent * BuildShip::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("BUILD SHIP", sf::Color::Black);
	vector->emplace_back("8 FOOD,  6 WOOD, 4 IRON", sf::Color::Black);
	vector->emplace_back("COSTS 1 ACTION", sf::Color::Black);
	vector->emplace_back("GRANTS GEMS WHILE ON PEARL DEPOSIT", sf::Color::Blue);
	return vector;
}

void BuildShip::use(Field * target)
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	ResourcesHandler & resources = player.getResources();

	if (!field->objects().containsUnitType(UnitType::Naval)
		&& resources.isAvailable(ResourceType::Food, 8)
		&& resources.isAvailable(ResourceType::Iron, 4)
		&& resources.isAvailable(ResourceType::Wood, 4))
	{
		InGameObject * archer = field->newUnit<Ship>(player);
		archer->spendActionPoints();
		unit.spendActionPoints(1);
		resources.add(ResourceType::Food, -8);
		resources.add(ResourceType::Iron, -4);
		resources.add(ResourceType::Wood, -4);
	}
}
