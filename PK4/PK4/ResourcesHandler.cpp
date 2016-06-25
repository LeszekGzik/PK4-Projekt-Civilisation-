#include "ResourcesHandler.h"

ResourcesSet::ResourcesSet(int iron, int food, int gems, int wood)
	: iron(iron), food(food), gems(gems), wood(wood)
{ }

ResourcesSet::ResourcesSet()
	: iron(0), food(0), gems(0), wood(0)
{ }


ResourcesHandler::ResourcesHandler()
{
}

void ResourcesHandler::add(ResourceType type, int amount)
{
	switch (type)
	{
	default:
	case Food:
		this->resources.food += amount;
		break;
	case Wood:
		this->resources.wood += amount;
		break;
	case Iron:
		this->resources.iron += amount;
		break;
	case Gems:
		this->resources.gems += amount;
		break;
	}

	this->event_resource_change.invoke(*this, type);
}

void ResourcesHandler::set(ResourceType type, int amount)
{
	switch (type)
	{
	default:
	case Food:
		this->resources.food = amount;
		break;
	case Wood:
		this->resources.wood = amount;
		break;
	case Iron:
		this->resources.iron = amount;
		break;
	case Gems:
		this->resources.gems = amount;
		break;
	}

	this->event_resource_change.invoke(*this, type);
}

void ResourcesHandler::set(ResourcesSet & set)
{
	this->resources = set;
}

int ResourcesHandler::get(ResourceType type) const
{
	switch (type)
	{
	default:
	case Food:
		return this->resources.food;
	case Wood:
		return this->resources.wood;
	case Iron:
		return this->resources.iron;
	case Gems:
		return this->resources.gems;
	}
}

bool ResourcesHandler::isAvailable(ResourceType type, int amount)
{
	return get(type) >= amount;
}
