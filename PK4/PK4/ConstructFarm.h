#pragma once
#include "Ability.h"

class Grass;

class ConstructFarm :
	public Ability
{
public:
	ConstructFarm(InGameObject& owner);
	~ConstructFarm();
	virtual void use();
	virtual ContextInfoContent * getContextInfoContent();
};

#include "Grass.h"