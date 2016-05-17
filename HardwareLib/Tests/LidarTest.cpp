#include <iostream>
#include <vector>

#include "../peripheralfactory.h"
#include "../smrtperipheral.h"
#include "../lidar.h"

using namespace NRMCHardware;
using namespace std;


int main(int argc, const char * argv[])
{
	SmrtPeripheral* smrt = PeripheralFactory::getInstance().getPeripheral(PeripheralSystem::LocalizationLIDAR);
	Lidar* ldr = dynamic_cast<Lidar*>(smrt->getPeripheral());

	if(ldr == 0)
		return -1;

	ldr->startScan();

	while(true)
	{
		static unsigned long int cnt = 0;
		vector<ScanPoint> scan = ldr->getScan();
		cout << "Scan #: " << cnt++ << endl;
		for(unsigned int point=0; point < scan.size(); point++)
			cout << "Dst: " << scan[point].dist << "mm\tAngle: " << scan[point].angle << endl;
	}

    return 0;
}
