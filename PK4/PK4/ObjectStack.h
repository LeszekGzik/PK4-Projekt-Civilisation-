#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <iterator>
#include "GameDefinitions.h"

class Unit;

class ObjectStack 
{
public:
	typedef Unit* Element;

	// iterator dla pêtli foreach
	typedef std::list<Element>::iterator iterator;

	iterator begin() { return stack.begin(); }
	iterator end() { return stack.end(); }

	void add(Element object);
	bool empty() const { return stack.empty(); }
	void erase(iterator & it) { stack.erase(it); }
	void pop();
	int size() const { return stack.size(); }
	bool containsUnitType(UnitType type);

	Element next();
	Element top() const;
	ObjectStack();
	~ObjectStack();

private:
	std::list<Element> stack;
};

#include "Unit.h"
