#include "ObjectStack.h"



void ObjectStack::add(InGameObject * object)
{
	stack.push_back(object);
	event_object_added.invoke(*this, object);
}

ObjectStack::ObjectStack()
{
}


ObjectStack::~ObjectStack()
{
}

