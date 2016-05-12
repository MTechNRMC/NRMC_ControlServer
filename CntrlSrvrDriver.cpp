#include <iostream>
#include <vector>
#include <exception>

#include "Util/systeminterface.h"
#include "NetworkLib/messagedeliverysystem.h"
#include "NetworkLib/SocketLib/udp_sock.h"
#include "MCS_Lib/manualcontrolsystem.h"
#include "HardwareLib/peripheralfactory.h"
#include "HardwareLib/termiosfactory.h"

#define PORT 5000

using std::cout;
using std::vector;
using std::exception;

using NRMCUtil::SystemInterface;
using NRMCNetwork::MessageDeliverySystem;
using Socket::UDP_Sock;
using NRMC_MCS::ManualControlSystem;
using NRMCHardware::PeripheralFactory;
using NRMCHardware::TermiosFactory;

int main(int argc, char** args)
{
	vector<SystemInterface*> sys;		// vector to hold sub systems running on different threads

	// create a UDP socket and attach it to the MDS
	cout << "Attaching socket to MDS...";
	MessageDeliverySystem::getInstance() += new UDP_Sock(PORT, false);
	cout << "Attached interface on port: " << PORT << std::endl;

	cout << "Attaching serial port factory to the Peripheral Factory...";
	PeripheralFactory::getInstance().attachFactory(TermiosFactory::getInstance());
	cout << "Attached\n";

	// create the MCS and add it to the system list
	sys.push_back(new ManualControlSystem(MessageDeliverySystem::getInstance(),
												PeripheralFactory::getInstance()));

	// start all the systems
	cout << "Starting subsystem(s)\n";
	for(unsigned int s=0; s<sys.size(); s++)
	{
		cout << "\tStarting System: " << s << "...";
		sys[s]->startSystem();
		cout << "Started\n";
	}
	cout << "All system(s) started\n";

	// start the MDS
	cout << "Starting MDS...\n";
	MessageDeliverySystem::getInstance().runMDS();

	// clean up
	cout << "Stopping subsystem(s)\n";
	for(unsigned int s=0; s<sys.size(); s++)
	{
		cout << "\tStopping System: " << s << "...";
		sys[s]->stopSystem();
		delete sys[s];
		sys[s] = 0;
		cout << "Stopped\n";
	}
	cout << "All system(s) stopped\n";
	sys.clear();

	return 0;
}
