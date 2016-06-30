#include "Pillage.h"

namespace
{
	const int ID = 19;
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

	if (imp != nullptr && object.hasFullAction())
	{
		imp->grantLoot(object.getOwner().getResources());
		field->deleteImprovement();
		object.spendActionPoints();
	}
}

ContextInfoContent * Pillage::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("PILLAGE", sf::Color::Black);
	vector->emplace_back("REQUIRES FULL ACTIONS", sf::Color::Red);
	vector->emplace_back("GRANTS RESOURCES", sf::Color::Blue);
	return vector;
}
