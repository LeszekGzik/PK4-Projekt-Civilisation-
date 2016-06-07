#include "ObjectStack.h"



void ObjectStack::add(InGameObject * object)
{
	stack.push_back(object);
}

void ObjectStack::pop()
{
	stack.pop_back();
}

InGameObject * ObjectStack::next()
{
	if (empty())
		return nullptr;
	else
	{
		InGameObject * temp = stack.back();
		stack.pop_back();
		stack.push_front(temp);
		return stack.back();
	}
}

InGameObject * ObjectStack::top() const
{
	if (empty())
		return nullptr;
	else
		return stack.back();
}

ObjectStack::ObjectStack()
{
}


ObjectStack::~ObjectStack()
{
	for each (InGameObject * object in stack)
		delete object;
}

