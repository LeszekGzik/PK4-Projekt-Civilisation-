#pragma once
#include "Ability.h"

class DragonLair;

class ConstructDragonLair :
	public Ability
{
public:
	ConstructDragonLair(InGameObject & owner);
	~ConstructDragonLair();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use();
};


#include "DragonLair.h";