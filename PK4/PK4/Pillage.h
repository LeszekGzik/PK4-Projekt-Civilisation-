#pragma once
#include "Ability.h"
class Pillage :
	public Ability
{
public:
	Pillage(InGameObject & owner);
	~Pillage();

	virtual void use();
	virtual ContextInfoContent * getContextInfoContent();

private:
	static int cost;
};

