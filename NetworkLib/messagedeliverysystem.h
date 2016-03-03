#ifndef MESSAGEDELIVERYSYSTEM_H
#define MESSAGEDELIVERYSYSTEM_H

#include <queue>
#include <pthread.h>
#include "message.h"
#include "SocketLib/networkinterface.h"
#include "mds_interface.h"
#include "systeminterface.h"
#include "subscribableexchange.h"
#include "notimplementedexception.h"
#include "../Util/systeminterface.h"

using std::queue;
using Socket::NetworkInterface;
using NRMCUtil::SystemInterface;

namespace NRMCNetwork
{
	// Singleton
	class MessageDeliverySystem: public SubscribableExchange, public SystemInterface, public MDS_Interface
	{
	  // Attributes
	  private:
		NetworkInterface* socket;
		queue<Message*> msgSendQueue;
		queue<Message*> msgRecvQueue;
		bool run;
		pthread_t mdsThread;
	  // Operations
	  public:
		~MessageDeliverySystem (  );
		static MessageDeliverySystem& getInstance (  );
		MessageDeliverySystem& operator+=( NetworkInterface* interface );
		void attachNetworkInterface( NetworkInterface* interface );
		void queueMessage ( Message* message );
		bool startSystem (  );
		bool stopSystem (  );
	  private:
		MessageDeliverySystem (  );
		void handler ( struct sockaddr_in& addr, char* msg );
	};
}

#endif
