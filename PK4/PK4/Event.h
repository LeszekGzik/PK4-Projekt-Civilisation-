#pragma once
#include <algorithm>
#include <vector>

template <typename TOut, typename... TIn>
using Delegate = TOut(*) (TIn...);

template<typename TSender, typename... TArgs>
class ICallback
{
public:
	virtual void call(TSender& sender, TArgs... args) abstract;
};

template <typename TSender, typename... TArgs>
class Event
{
public:
	typedef ICallback<TSender, TArgs...>* EventDelegate;

	template <typename TSource>
	struct Callback : ICallback<TSender, TArgs...>
	{
		typedef void(TSource::*Member) (TSender&, TArgs...);
		TSource * source;
		Member func;
		void call(TSender& sender, TArgs... args) { (source->*func)(sender, args...); }
		void set(TSource * source, Member func) { this->source = source; this->func = func; }
	};

	Event() { }
	~Event() { }

	void invoke(TSender& sender, TArgs... event_args)
	{
		for each (EventDelegate del in event_delegate)
			del->call(sender, event_args...);
	}

	void reg(EventDelegate del)
	{
		if (del != NULL)
			event_delegate.push_back(del);
	}

	void unreg(EventDelegate del)
	{
		event_delegate.erase(std::remove(event_delegate.begin(), event_delegate.end(), del), event_delegate.end());
	}

private:
	std::vector<EventDelegate> event_delegate;
};