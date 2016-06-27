#pragma once
#include "Ability.h"

class Horseman;

class TrainHorseman :
	public Ability
{
public:
	TrainHorseman(InGameObject & owner);
	~TrainHorseman();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use();
};

#include "Horseman.h"
