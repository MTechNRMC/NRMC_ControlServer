#include "RPLidar.h"
#include <stdexcept>

using namespace NRMCHardware;
using std::runtime_error;

vector<ScanPoint> RPLidar::getScan()
{
	vector<ScanPoint> scan;

	unsigned long int numOfNodes = 360*2;
	rplidar_response_measurement_node_t nodes[numOfNodes];

	driver->grabScanData(nodes, numOfNodes);

	driver->ascendScanData(nodes, numOfNodes);
	for(unsigned long int node=0; node<numOfNodes; node++)
		scan.push_back(ScanPoint(nodes[node].distance_q2/4.0f,
				(nodes[node].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f));

	return scan;
}

PeripheralType RPLidar::getType()
{
	return PeripheralType::lidar;
}

PeripheralSystem RPLidar::getSystem()
{
	return sys;
}

string RPLidar::getConnectedPort()
{
	return port;
}

RPLidar::RPLidar(string portName, unsigned int port, PeripheralSystem sys)
{
	this->port = portName;
	this->sys = sys;
	driver = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);

	if(IS_FAIL(driver->connect(portName.c_str(), port)))
	{
		RPlidarDriver::DisposeDriver(driver);
		throw runtime_error("Unable to bind the LIDAR to port: " + portName);
	}

	// check health
	if(!checkRPLIDARHealth(*driver))
		throw runtime_error("Unknown hardware issue with the LIDAR");
}

RPLidar::~RPLidar()
{
	RPlidarDriver::DisposeDriver(driver);
}

bool RPLidar::startScan()
{
	return IS_OK(driver->startScan());
}

bool RPLidar::stopScan()
{
	return IS_OK(driver->stop());
}

bool RPLidar::checkRPLIDARHealth(RPlidarDriver& drv)
{
    u_result     op_result;
    rplidar_response_device_health_t healthinfo;


    op_result = drv.getHealth(healthinfo);
    if (IS_OK(op_result))
    {
        if (healthinfo.status == RPLIDAR_STATUS_ERROR)
        {
            drv.reset();
            return false;
        }
        else
            return true;
    }

    return false;
}
