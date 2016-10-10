#pragma once
#include "Unit.h"
#include "UnitCarrier.h"
#include "LoadUnit.h"
#include "UnloadUnit.h"

class PearlsDeposit;

class Ship :
	public Unit, public UnitCarrier
{
public:
	Ship(Field * field, Player & owner);
	~Ship();

	int checkMovement(Field * field);
	virtual ManagmentStatus initCombat(Field * target);
	virtual CombatResult attacked(float strength, int & counter_damage);
	virtual float getTotalStrength();
	virtual void newTurn();
	virtual ContextInfoContent * getContextInfoContent(ContextInfoContent * content);
private:
	int production = 1;
};

#include "PearlsDeposit.h"
