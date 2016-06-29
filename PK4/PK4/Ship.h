#pragma once
#include "Unit.h"

class Pearls;
class PearlsDeposit;
class GeneralDepositExtension;

class Ship :
	public Unit
{
public:
	Ship(Field * field, Player & owner);
	~Ship();

	int checkMovement(Field * field);
	virtual CombatResult attacked(float strength, int & counter_damage);
	virtual float getTotalStrength();
	virtual void newTurn();
private:
	int production = 1;
};

#include "PearlsDeposit.h"
