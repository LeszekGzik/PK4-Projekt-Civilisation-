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
	virtual void use(Field * target = nullptr);
};

#include "Hills.h"
#include "IronMine.h"
#include "IronDeposit.h"

