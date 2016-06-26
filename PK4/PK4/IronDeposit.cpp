#include "IronDeposit.h"

namespace
{
	const uint32_t ID = 3;
}

IronDeposit::IronDeposit(Field * field) : Deposit(field, ID)
{
}

IronDeposit::~IronDeposit()
{
}
