#include "subscribableexchange.h"

using namespace NRMCNetwork;

SubscribableExchange::SubscribableExchange (  )
{
}

SubscribableExchange::~SubscribableExchange (  )
{
}

vector<ExchangeSubscriber*> SubscribableExchange::getSubscribers const (  )
{
	throw NotImplementedException;
}

void SubscribableExchange::subscribe ( ExchangeSubscriber& subscriber )
{
	throw NotImplementedException;
}

void SubscribableExchange::updateSubscribers ( const Message& message )
{
	throw NotImplementedException;
}

