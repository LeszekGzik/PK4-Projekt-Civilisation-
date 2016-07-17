#include "LoadUnit.h"

namespace
{
	uint32_t ID = 1;
	int MAX_DISTANCE = 1;
};


LoadUnit::LoadUnit(InGameObject & object) 
	: Ability(ID, object, _targetable), max_distance(MAX_DISTANCE)
{
}

LoadUnit::~LoadUnit()
{
}

ContextInfoContent * LoadUnit::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("LOAD", sf::Color::Black);
	vector->emplace_back("REQUIRES TARGETED UNIT ACTION", sf::Color::Red);
	vector->emplace_back("BOARDS TARGETED UNIT", sf::Color::Blue);
	return vector;
}

void LoadUnit::use(Field * target)
{
	UnitCarrier * carrier = dynamic_cast<UnitCarrier*>(&getOwner());
	if (target == nullptr || carrier == nullptr || !carrier->isEmpty()
			|| max_distance < getOwner().getField()->distanceTo(target))
		return;

	Unit * unit = target->objects().top();
	if (unit == nullptr || unit->getOwner() != this->getOwner().getOwner()
			|| !carrier->isTypeAllowed(unit->getType())
			|| unit->getActionPoints() < 1)
		return;

	unit->setActionPoints(unit->getActionPoints() - 1);
	target->objects().pop();
	carrier->load(unit);
}
