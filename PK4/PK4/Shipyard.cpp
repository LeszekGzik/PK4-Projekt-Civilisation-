#include "Shipyard.h"


namespace
{
	const uint32_t ID = 1;
	const std::string NAME = "SHIPYARD";
	const int ACTION_POINTS = 1;
}

Shipyard::Shipyard(Field * field, Player & owner) : Improvement(field, owner, NAME, ID, ACTION_POINTS)
{
}

Shipyard::~Shipyard()
{
}
