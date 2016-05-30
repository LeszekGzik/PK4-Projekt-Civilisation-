#pragma once
#include <algorithm>
#include <vector>

template <typename TOut, typename... TIn>
using Delegate = TOut(*) (TIn...);

template<typename TSender, typename... TArgs>
class ICallback
{
	virtual void call(TSender& sender, TArgs... args) abstract;
};

template <typename TSender, typename... TArgs>
class Event
{
public:
	//typedef Delegate<void, TSender&, TArgs...> EventDelegate;
	using EventDelegate = void(ICallback<TSender, TArgs...>::*) (TSender&, TArgs...);

	Event() { }
	~Event() { }

	void invoke(TSender& sender, TArgs... event_args)
	{
		for (unsigned int i = 0; i < event_delegate.size(); i++)
		{
			event_delegate[i](sender, event_args...);
		}
	}

	void reg(EventDelegate del) 
	{ 
		event_delegate.push_back(del); 
	}

	void unreg(EventDelegate del) 
	{
		event_delegate.erase(std::remove(event_delegate.begin(), event_delegate.end(), del), event_delegate.end());
	}

private:
	std::vector<EventDelegate> event_delegate;
};