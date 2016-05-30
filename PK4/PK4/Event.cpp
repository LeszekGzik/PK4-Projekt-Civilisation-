#include "Event.h"


template<typename TSender, typename... TArgs>
void Event<TSender, TArgs...>::invoke(TSender& sender, TArgs... event_args)
{
	/*for (std::vector<EventDelegate>::iterator it = event_delegate.begin(); it != event_delegate.end(); it++)
	{
		*it(sender, event_args);
	}*/

	for (unsigned int i = 0; i < event_delegate.size(); i++)
	{
		event_delegate[i](sender, event_args...);
	}
}

template<typename TSender, typename... TArgs>
void Event<TSender, TArgs...>::reg(EventDelegate del)
{
	event_delegate.push_back(del);
}

template<typename TSender, typename... TArgs>
void Event<TSender, TArgs...>::unreg(EventDelegate del)
{
	event_delegate.erase(std::remove(event_delegate.begin(), event_delegate.end(), del), event_delegate.end());
}