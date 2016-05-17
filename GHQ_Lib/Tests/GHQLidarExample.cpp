#include <iostream>
#include <vector>

#include "../ghqs_interface.h"
#include "../generalhardwarequerysystem.h"
#include "../../HardwareLib/peripheralfactory.h"
#include "../../HardwareLib/smrtperipheral.h"
#include "../../HardwareLib/lidar.h"
#include "../../NetworkLib/liadrmessage.h"

using namespace NRMCHardware;
using namespace NRMC_GHQS;
using namespace NRMCNetwork;
using namespace std;


int main(int argc, const char * argv[])
{
	GHQS_Interface* ghqs = new GeneralHardwareQuerySystem(PeripheralFactory::getInstance());


	while(true)
	{
		static unsigned long int cnt = 0;
		LIADRMessage* msg = dynamic_cast<LIADRMessage*>(ghqs->queryHardware(Device::LocalizationLIDAR));
		cout << "Scan #: " << cnt++ << endl;
		for(unsigned int point=0; point < msg->getScan().size(); point++)
			cout << "Dst: " << msg->getScan()[point].dist << "mm\tAngle: " << msg->getScan()[point].angle << endl;
	}

    return 0;
}
