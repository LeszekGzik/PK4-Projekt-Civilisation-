#pragma once
#include "Ability.h"

class Archer;

class TrainArcher :
	public Ability
{
public:
	TrainArcher(InGameObject & owner);
	~TrainArcher();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use();
};

#include "Archer.h"
