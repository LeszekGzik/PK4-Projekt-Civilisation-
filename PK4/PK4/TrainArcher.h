#pragma once
#include "Ability.h"
#include "Archer.h"

class TrainArcher :
	public Ability
{
public:
	TrainArcher(InGameObject & owner);
	~TrainArcher();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use();
};

