#pragma once
#include "Ability.h"
#include "Worker.h"

class TrainWorker :
	public Ability
{
public:
	TrainWorker(InGameObject & owner);
	~TrainWorker();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use(Field * target = nullptr);
	
};

