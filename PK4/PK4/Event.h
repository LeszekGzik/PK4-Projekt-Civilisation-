#pragma once
#include <algorithm>
#include <vector>


template <class TSender, class TArgs>
class Event
{
	using EventDelegate = void(*) (TSender*, TArgs);

private:
	std::vector<EventDelegate> event_delegate;
public:
	Event();
	~Event();

	void invoke(TSender* sender, TArgs event_args);
	void reg(EventDelegate del);
	void unreg(EventDelegate del);
};

