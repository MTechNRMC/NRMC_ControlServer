#include "subscribableexchange.h"

using namespace NRMCNetwork;

SubscribableExchange::SubscribableExchange (  )
{
	
}

SubscribableExchange::~SubscribableExchange (  )
{
	while (subscribers.size() > 0)
	{
		subscribers.erase (subscribers.begin());
	}
}

vector<ExchangeSubscriber*> SubscribableExchange::getSubscribers const (  )
{
	return subscribers;
}

void SubscribableExchange::subscribe ( ExchangeSubscriber& subscriber )
{
	subscribers.push_back(subscriber);
}

void SubscribableExchange::updateSubscribers ( const Message& message )
{
	for (int i = 0; i < subscribers.size(); i++)
	{
		subscribers[i].queueMessage (message);
	}
}

