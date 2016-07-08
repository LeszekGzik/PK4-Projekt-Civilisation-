#pragma once
#include <list>
#include "GameDefinitions.h"

class Unit;

class UnitCarrier
{
public:
	typedef std::list<UnitType> AvailableTypes;

	UnitCarrier(const AvailableTypes & types);
	~UnitCarrier();

	bool isEmpty() { return unit == nullptr; }
	bool isTypeAllowed(UnitType type);
	void load(Unit * unit);
	Unit * unload();
	Unit * getUnit() { return unit; }

private:
	AvailableTypes types;
	Unit * unit = nullptr;
};

#include "Unit.h"