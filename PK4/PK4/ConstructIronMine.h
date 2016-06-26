#pragma once
#include "Ability.h"

class Hills;
class IronMine;
class IronDeposit;

class ConstructIronMine : public Ability
{
public:
	ConstructIronMine(InGameObject & owner);
	~ConstructIronMine();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use();
};

#include "Hills.h"
#include "IronMine.h"
#include "IronDeposit.h"

