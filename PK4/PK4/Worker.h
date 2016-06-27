#pragma once
#include "Unit.h"

class Worker :
	public Unit
{
public:
	Worker(Field * field, Player & owner);
	~Worker();

	virtual int checkMovement(Field * field);
	virtual CombatResult attack(InGameObject * target);
	virtual CombatResult attacked(float strength, int & counter_damage);

};

