#ifndef MESSAGEDELIVERYSYSTEM_H
#define MESSAGEDELIVERYSYSTEM_H

#include <queue>
#include <pthread.h>
#include "message.h"
#include "SocketLib/networkinterface.h"
#include "mds_interface.h"
#include "systeminterface.h"
#include "subscribableexchange.h"

using std::queue;
using Socket::NetworkInterface;

namespace NRMCNetwork
{
	// Singleton
	class MessageDeliverySystem: public SubscribableExchange, public SystemInterface, public MDS_Interface
	{
	  // Attributes
	  private:
		NetworkInterface* socket;
		queue<Message*> msgSendQueue;
		bool run;
		pthread_t mdsThread;
	  // Operations
	  public:
		static MessageDeliverySystem& getInstance (  );
		void queueMessage ( Message* message );
		bool startSystem (  );
		bool stopSystem (  );
	  private:
		MessageDeliverySystem ( NetworkInterface* socket );
		void handler ( struct sockaddr_in& addr, char* msg );
	};
}

#endif
