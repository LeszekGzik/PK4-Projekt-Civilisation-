#include "Ship.h"


namespace
{
	const uint32_t ID = 4;
	const std::string NAME = "SHIP";
	const int SPEED = 4;
	const int STRENGTH = 12;
	const UnitType TYPE = UnitType::Naval;
}

Ship::Ship(Field * field, Player & owner) : Unit(ID, field, owner, NAME, SPEED, STRENGTH, TYPE)
{
}

Ship::~Ship()
{
}

int Ship::checkMovement(Field * field)
{
	if (field->getType() != FieldType::Sea)
		return -1;
	else if (checkIfOccupied(field) == Occupied::Full)
		return -1;
	else
		return field->getMovementCost();
}

CombatResult Ship::attacked(float strength, int & counter_damage)
{
	if (getField()->getType() != FieldType::Sea)
	{
		counter_damage = 0;
		return CombatResult::Win;
	}

	int health = getHealth();
	float strength_ratio = strength / getTotalStrength();
	float damage = pow(strength_ratio, 2) * 10 - strength_ratio * 10 + 30;
	float counter = damage / (pow(strength_ratio, 2) * 2 - strength_ratio * 4 + 3);

	if (strength_ratio >= 1)
	{
		health -= damage;
		counter_damage = counter;
	}
	else
	{
		health -= counter;
		counter_damage = damage;
	}

	setHealth(health);
	if (health > 0)
		return CombatResult::Tie;
	else
		return CombatResult::Win;
}

float Ship::getTotalStrength()
{
	if (getField()->getType() != FieldType::Sea)
		return 0;
	else
		return (float)getHealth() * (float)getStrength() / 100;
}

void Ship::newTurn()
{
	if (dynamic_cast<PearlsDeposit*>(getField()->getDeposit()) != nullptr && hasFullAction())
	{
		getOwner().getResources().add(ResourceType::Gems, this->production);
	}
	setActionPoints(getSpeed());
	setIfAttackedThisTurn(false);
}
