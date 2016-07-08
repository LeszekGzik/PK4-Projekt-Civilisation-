#pragma once
#include "Ability.h"
#include "UnitCarrier.h"

class LoadUnit :
	public Ability
{
public:
	LoadUnit(InGameObject & object);
	~LoadUnit();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use(Field * target = nullptr);

private:
	int max_distance;
};

