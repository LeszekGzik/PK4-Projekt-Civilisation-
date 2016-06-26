#pragma once
#include "Unit.h"

class Worker :
	public Unit
{
public:
	Worker(Field * field, Player & owner);
	~Worker();

	virtual int checkMovement(Field * field);

};

