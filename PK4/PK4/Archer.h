#pragma once
#include "Unit.h"
#include "EngineDefinitions.h"
#include "ConstructFarm.h"
#include "ConstructBarracks.h"
#include "Pillage.h"

class Archer :
	public Unit
{
private:
	static const int ID = 1;

public:
	int checkMovement(Field * field);

	Archer(Field* field, Player & owner);
	~Archer();
};

