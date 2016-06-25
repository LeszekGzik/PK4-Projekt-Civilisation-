#pragma once
#include "Ability.h"
#include "Barracks.h"

class ConstructBarracks :
	public Ability

{
public:
	ConstructBarracks(InGameObject & owner);
	~ConstructBarracks();
	virtual void use();
	virtual ContextInfoContent * getContextInfoContent();
};

