#include "TrainWorker.h"

namespace
{
	const int ID = 8;
}

TrainWorker::TrainWorker(InGameObject & owner) : Ability(ID, owner, _not_targetable)
{
}


TrainWorker::~TrainWorker()
{
}

ContextInfoContent * TrainWorker::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->emplace_back("TRAIN WORKER", sf::Color::Black);
	vector->emplace_back("3 FOOD", sf::Color::Black);
	vector->emplace_back("COSTS 1 ACTION", sf::Color::Black);
	return vector;
}

void TrainWorker::use(Field * target)
{
	InGameObject& unit = getOwner();
	Player& player = unit.getOwner();
	Field * field = unit.getField();
	ResourcesHandler & resources = player.getResources();

	if (!field->objects().containsUnitType(UnitType::Worker)
		&& resources.isAvailable(ResourceType::Food, 3))
	{
		InGameObject * new_unit = field->newUnit<Worker>(player);
		new_unit->spendActionPoints();
		unit.spendActionPoints(1);
		resources.add(ResourceType::Food, -3);
	}
}
