#pragma once
#include "GameDefinitions.h"
#include "Event.h"

struct ResourcesSet
{
	int iron;
	int food;
	int gems;
	int wood;

	ResourcesSet(int iron, int food, int gems, int wood);
	ResourcesSet();
};

class ResourcesHandler
{
public:
	typedef Event<ResourcesHandler, ResourceType> ResourceChange;

	ResourcesHandler::ResourcesHandler();

	ResourceChange & eventResourceChange() { return this->event_resource_change; }

	void add(ResourceType type, int amount);
	int get(ResourceType type) const;
	void set(ResourceType type, int amount);
	void set(ResourcesSet & set);

	bool isAvailable(ResourceType type, int amount);

private:
	ResourceChange event_resource_change;

	ResourcesSet resources;
};