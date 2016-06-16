#pragma once
#include "Improvement.h"

class Farm : public Improvement
{
private:
	static const int ID;

public:
	Farm(OffsetCoords position, Player& owner);
	~Farm();
};

