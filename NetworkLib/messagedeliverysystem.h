#ifndef MESSAGEDELIVERYSYSTEM_H
#define MESSAGEDELIVERYSYSTEM_H

#include <queue>
#include <thread>
#include "message.h"
#include "SocketLib/networkinterface.h"
#include "mds_interface.h"
#include "systeminterface.h"
#include "subscribableexchange.h"
#include "notimplementedexception.h"
#include "../Util/systeminterface.h"

using std::queue;
using std::thread;
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
		volatile bool run;
		thread mdsThread;
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
		void mds();
	};
}

#endif
