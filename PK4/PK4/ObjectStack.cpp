#include "ObjectStack.h"



void ObjectStack::add(Element object)
{
	stack.push_back(object);
}

void ObjectStack::pop()
{
	stack.pop_back();
}

bool ObjectStack::containsUnitType(UnitType type)
{
	iterator it = std::find_if(stack.begin(), stack.end(), [&type](Element unit) { return (unit->getType() == type); });
	return it != stack.end();
}

Unit * ObjectStack::next()
{
	if (empty())
		return nullptr;
	else
	{
		Element temp = stack.back();
		stack.pop_back();
		stack.push_front(temp);
		return stack.back();
	}
}

Unit * ObjectStack::top() const
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
	for each (Element object in stack)
		delete object;
}

