#pragma once
#include "Ability.h"

class UnitCarrier;

class UnloadUnit :
	public Ability
{
public:
	UnloadUnit(InGameObject & object);
	~UnloadUnit();
	virtual ContextInfoContent * getContextInfoContent();
	virtual void use(Field * target = nullptr);

private:
	int max_distance;
};

#include "UnitCarrier.h"