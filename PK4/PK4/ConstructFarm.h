#pragma once
#include "Ability.h"

class ConstructFarm :
	public Ability
{
public:
	ConstructFarm(InGameObject& owner);
	~ConstructFarm();
	virtual void use();
	virtual ContextInfoContent * getContextInfoContent();
};

