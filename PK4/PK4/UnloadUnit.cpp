#include "UnloadUnit.h"

namespace
{
	uint32_t ID = 19;
	int MAX_DISTANCE = 1;
}

UnloadUnit::UnloadUnit(InGameObject & object) 
	: Ability(ID, object, _targetable), max_distance(MAX_DISTANCE)
{
}

UnloadUnit::~UnloadUnit()
{
}

ContextInfoContent * UnloadUnit::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("UNLOAD", sf::Color::Black);
	vector->emplace_back("REQUIRES CARRIED UNIT ACTION", sf::Color::Red);
	vector->emplace_back("UNBOARDS UNIT ONTO TARGETED FIELD", sf::Color::Blue);
	return vector;
}

void UnloadUnit::use(Field * target)
{
	UnitCarrier * carrier = dynamic_cast<UnitCarrier*>(&getOwner());
	if (target == nullptr || carrier == nullptr || carrier->isEmpty()
			|| max_distance < getOwner().getField()->distanceTo(target))
		return;

	Unit * unit = target->objects().top();
	Unit * carried = carrier->getUnit();
	if ((unit != nullptr && unit->getOwner() != carried->getOwner())
			|| target->objects().containsUnitType(carried->getType())
			|| carried->checkMovement(target) < 0
			|| carried->getActionPoints() < 1)
		return;

	carrier->unload();
	carried->spendActionPoints(carried->checkMovement(target));
	carried->move(target);
}
