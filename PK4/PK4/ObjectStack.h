#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <iterator>
#include "InGameObject.h"
#include "Event.h"

class ObjectStack 
{
private:
	std::list<InGameObject*> stack;

public:
	// iterator dla pêtli foreach
	typedef std::list<InGameObject*>::iterator iterator;
	iterator begin() { return stack.begin(); }
	iterator end() { return stack.end(); }

	void add(InGameObject* object);
	bool empty() const { return stack.empty(); }
	void pop();
	int size() const { return stack.size(); }
	InGameObject* next();
	InGameObject* top() const;
	ObjectStack();
	~ObjectStack();

};

