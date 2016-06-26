#pragma once
#include "Deposit.h"

class IronDeposit :
	public Deposit
{
public:
	IronDeposit(Field * field);
	~IronDeposit();
};

