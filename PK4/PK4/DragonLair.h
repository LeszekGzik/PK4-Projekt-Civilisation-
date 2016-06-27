#pragma once
#include "Improvement.h"
#include "HireDragon.h"

class DragonLair :
	public Improvement
{
public:
	DragonLair(Field * field, Player & owner);
	~DragonLair();

	virtual void grantLoot(ResourcesHandler & handler);
};

