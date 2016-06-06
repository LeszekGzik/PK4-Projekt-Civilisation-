#pragma once
#include "Unit.h"
#include "EngineDefinitions.h"

class Archer :
	public Unit
{
private:
	static const int ID = 1;

public:
	Archer(AxialCoords position, Player & owner);
	~Archer();
};

