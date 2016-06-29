#pragma once
#include "Unit.h"

class Hills;

class Archer :
	public Unit
{
private:
	static const float HILL_STR_FACTOR;

public:
	int checkMovement(Field * field);
	virtual float getTotalStrength();

	Archer(Field* field, Player & owner);
	~Archer();
};

#include "Hills.h"