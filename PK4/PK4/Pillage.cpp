#include "Pillage.h"

namespace
{
	const int ID = 1;
	const std::string DESC1 = "PILLAGE IMPROVEMENT";
	const std::string DESC2 = "COSTS ";
	const std::string DESC3 = " ACTION(S)";
}

int Pillage::cost = 1;

Pillage::Pillage(InGameObject & owner) : Ability(ID, owner)
{
	
}

Pillage::~Pillage()
{
}

void Pillage::use()
{
	InGameObject& object = getOwner();
	Field * field = object.getField();
	Improvement * imp = field->getImprovement();

	if (imp != nullptr && object.getActionPoints() > 0)
	{
		imp->grantLoot(object.getOwner().getResources());
		field->deleteImprovement();
		object.spendActionPoints(cost);
	}
}

ContextInfoContent * Pillage::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back(DESC1, sf::Color::Black);
	vector->emplace_back(DESC2 + std::to_string(cost) + DESC3, sf::Color::Black);
	return vector;
}
