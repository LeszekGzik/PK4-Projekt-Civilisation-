#pragma once

#include "Ability.h"

class TrainSwordsman : public Ability
{
public:
	TrainSwordsman(InGameObject& owner);
	~TrainSwordsman();


	virtual ContextInfoContent * getContextInfoContent();
	virtual void use(Field * target = nullptr);

};