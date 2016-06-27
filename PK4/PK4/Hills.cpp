#include "Hills.h"



namespace
{
	const FieldType TYPE = FieldType::Land;
	int ID = 3;
	const int MOVEMENT_COST = 2;
}


Hills::Hills(OffsetCoords position) : Field(ID, position, MOVEMENT_COST, TYPE), DepositExtension(this)
{
}

Hills::~Hills()
{
}

void Hills::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(getVertex(), &(tileset().getTileset()));
	if (getDeposit() != nullptr)
		target.draw(*getDeposit(), states);
	if (getImprovement() != nullptr)
		target.draw(*getImprovement(), states);
	if (!objects().empty())
		target.draw(*objects().top(), states);
}
