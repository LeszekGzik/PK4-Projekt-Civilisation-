#include "Hills.h"



namespace
{
	const FieldType TYPE = FieldType::Land;
	int ID = 3;
	const int MOVEMENT_COST = 2;
}


Hills::Hills(OffsetCoords position) : Field(ID, position, MOVEMENT_COST, TYPE)
{
}

Hills::~Hills()
{
}

void Hills::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(getVertex(), &(tileset().getTileset()));
	if (this->deposit != nullptr)
		target.draw(*this->deposit, states);
	if (getImprovement() != nullptr)
		target.draw(*getImprovement(), states);
	if (!objects().empty())
		target.draw(*objects().top(), states);
}
