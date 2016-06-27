#pragma once
#include "Unit.h"
#include "Pillage.h"

class Horseman :
	public Unit
{
public:
	Horseman(Field * field, Player & owner);
	~Horseman();

	int checkMovement(Field * field);
};

