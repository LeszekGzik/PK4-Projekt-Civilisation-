#pragma once
#include "Field.h"
#include "Deposit.h"

class Hills :
	public Field
{
private:
	Deposit * deposit = nullptr;

public:
	Hills(OffsetCoords position);
	~Hills();

	Deposit * getDeposit() { return this->deposit; }
	void setDeposit(Deposit * deposit) { this->deposit = deposit; }

	template<typename TDeposit> inline TDeposit * newDeposit();
	
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

template<typename TDeposit>
inline TDeposit * Hills::newDeposit()
{
	static_assert(std::is_base_of<Deposit, TDeposit>::value, "Input type must derive from Deposit class");
	TDeposit * deposit = new TDeposit(this);
	this->deposit = deposit;
	return deposit;
}
