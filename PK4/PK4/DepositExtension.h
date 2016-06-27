#pragma once
#include "Deposit.h"
#include "Field.h"

template<typename... TAllowed>
class DepositExtension
{
public:
	DepositExtension(Field * field);
	~DepositExtension();

	Deposit * getDeposit() const { return this->deposit; }
	void setDeposit(Deposit * deposit) { this->deposit = deposit; }

	template<typename TDeposit> inline TDeposit * newDeposit();

private:
	Deposit * deposit = nullptr;
	Field * field;
};

template<typename TDeposit>
inline TDeposit * DepositExtension::newDeposit()
{
	static_assert(std::is_base_of<Deposit, TDeposit>::value, "Input type must derive from Deposit class");
	TDeposit * deposit = new TDeposit(this->field);
	this->deposit = deposit;
	return deposit;
}
