#pragma once
#include "Unit.h"
#include "Pillage.h"

class Dragon :
	public Unit
{
public:
	Dragon(Field * field, Player & owner);
	~Dragon();

	int checkMovement(Field * field);
};

