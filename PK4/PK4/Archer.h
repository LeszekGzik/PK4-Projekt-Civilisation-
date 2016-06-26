#pragma once
#include "Unit.h"

class Archer :
	public Unit
{
private:

public:
	int checkMovement(Field * field);

	Archer(Field* field, Player & owner);
	~Archer();
};

