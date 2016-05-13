#pragma once
#include <algorithm>
#include <vector>

template <typename TOut, typename... TIn>
using Delegate = TOut(*) (TIn...);

template <class TSender, class... TArgs>
class Event
{
	typedef Delegate<void, TSender, TArgs...> EventDelegate;

private:
	std::vector<EventDelegate> event_delegate;
public:
	Event();
	~Event();

	void invoke(TSender* sender, TArgs... event_args);
	void reg(EventDelegate del);
	void unreg(EventDelegate del);
};

