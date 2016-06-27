#pragma once
#include "Improvement.h"

class Shipyard :
	public Improvement
{
public:
	Shipyard(Field * field, Player & owner);
	~Shipyard();

	void grantLoot();
};

