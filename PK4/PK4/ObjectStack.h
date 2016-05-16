#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <iterator>
#include "InGameObject.h"
#include "Event.h"
#include "Event.cpp"

class ObjectStack 
{
private:
	typedef Event<ObjectStack, InGameObject*> EventObjectAdded;
	typedef Event<ObjectStack, InGameObject*> EventObjectRemoved;

	std::list<InGameObject*> stack;
	EventObjectAdded event_object_added;
	EventObjectRemoved event_object_removed;

public:
	// iterator dla pêtli foreach
	typedef std::list<InGameObject*>::iterator iterator;
	iterator begin() { return stack.begin(); }
	iterator end() { return stack.end(); }

	bool empty() const { return stack.empty(); }
	void add(InGameObject* object);
	void event_objectAddedReg(EventObjectAdded::EventDelegate event_handler) { event_object_added.reg(event_handler); }
	void event_objectAddedUnreg(EventObjectAdded::EventDelegate event_handler) { event_object_added.unreg(event_handler); }
	void event_objectRemovedReg(EventObjectRemoved::EventDelegate event_handler) { event_object_removed.reg(event_handler); }
	void event_objectRemovedUnreg(EventObjectRemoved::EventDelegate event_handler) { event_object_removed.unreg(event_handler); }
	InGameObject* top() const { return stack.front(); }
	ObjectStack();
	~ObjectStack();

};

