#include "UnitCarrier.h"


UnitCarrier::UnitCarrier(const AvailableTypes & types) 
	: types(types)
{
}

UnitCarrier::~UnitCarrier()
{
	if (unit != nullptr)
		delete unit;
}

bool UnitCarrier::isTypeAllowed(UnitType type)
{
	return std::find(types.begin(), types.end(), type) != types.end();
}

void UnitCarrier::load(Unit * unit)
{
	this->unit = unit;
}

Unit * UnitCarrier::unload()
{
	Unit * temp = this->unit;
	this->unit = nullptr;
	return temp;
}
