#include "HireDragon.h"

namespace
{
	const uint32_t ID = 17;
}

HireDragon::HireDragon(InGameObject & owner) : Ability(ID, owner, _not_targetable)
{
}


HireDragon::~HireDragon()
{
}

ContextInfoContent * HireDragon::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("HIRE DRAGON", sf::Color::Black);
	vector->emplace_back("30 FOOD, 15 GEMS", sf::Color::Black);
	vector->emplace_back("COSTS 1 ACTION", sf::Color::Black);
	vector->emplace_back("FLYING UNIT", sf::Color::Blue);
	return vector;
}

void HireDragon::use(Field * target)
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	ResourcesHandler & resources = player.getResources();

	if (!field->objects().containsUnitType(UnitType::Air)
		&& resources.isAvailable(ResourceType::Food, 30)
		&& resources.isAvailable(ResourceType::Gems, 20))
	{
		InGameObject * new_unit = field->newUnit<Dragon>(player);
		new_unit->spendActionPoints();
		unit.spendActionPoints(1);
		resources.add(ResourceType::Food, -30);
		resources.add(ResourceType::Gems, -20);
	}
}
