#include "Ship.h"


namespace
{
	const uint32_t ID = 4;
	const std::string NAME = "SHIP";
	const int SPEED = 4;
	const int STRENGTH = 12;
	const UnitType TYPE = UnitType::Naval;
	const UnitCarrier::AvailableTypes CARRIED_TYPES = { UnitType::Land, UnitType::Worker };
}

Ship::Ship(Field * field, Player & owner) : 
	Unit(ID, field, owner, NAME, SPEED, STRENGTH, TYPE),
	UnitCarrier(CARRIED_TYPES)
{
	grantAbility<LoadUnit>();
	grantAbility<UnloadUnit>();
}

Ship::~Ship()
{
}

int Ship::checkMovement(Field * field)
{
	if (field->getType() != FieldType::Sea)
	{
		Unit * unit = field->objects().top();
		if (unit != nullptr && unit->getOwner() != this->getOwner())
			return 1;
		else
			return _unreachable;
	}	
	else if (checkIfOccupied(field) == Occupied::Full)
		return _unreachable;
	else
		return field->getMovementCost();
}

ManagmentStatus Ship::initCombat(Field * target)
{
	ObjectStack & stack = target->objects();
	ObjectStack::iterator foe = std::max_element(stack.begin(), stack.end(), [](Unit * arg1, Unit * arg2) { return (arg1->getTotalStrength() < arg2->getTotalStrength()); });
	CombatResult result = this->attack(*foe);
	ManagmentStatus return_status;

	switch (result)
	{
	case Lose:
		return_status = ManagmentStatus::Delete;
		break;
	case Tie:
		return_status = ManagmentStatus::NoAction;
		break;
	case Win:
		return_status = ManagmentStatus::NoAction;
		delete *foe;
		target->objects().erase(foe);
		if (target->getType() == FieldType::Sea)
			this->move(target);
		break;
	}

	return return_status;
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
	Unit * carried = getUnit();
	if (carried != nullptr)
		carried->newTurn();
}

ContextInfoContent * Ship::getContextInfoContent(ContextInfoContent * content)
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->push_back(ContextInfoLine(getOwner().getName(), ColorUtils::sfColor(getOwner().getColor())));
	vector->push_back(ContextInfoLine("HP: " + std::to_string(getHealth()), sf::Color::Black));
	vector->push_back(ContextInfoLine("STR: " + std::to_string(getStrength()), sf::Color::Black));
	vector->push_back(ContextInfoLine("MOVE: " + std::to_string(getActionPoints()) + "/" + std::to_string(getSpeed()), sf::Color(sf::Color::Black)));
	if (!isEmpty())
		vector->push_back(ContextInfoLine("CARRIES " + getUnit()->getName(), sf::Color::Black));
	return vector;
}
