#include "RPLidar.h"

using namespace NRMCHardware;

vector<ScanPoint> RPLidar::getScan()
{
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
	this->port;
	this->sys = sys;
}

RPLidar::~RPLidar()
{
}

bool RPLidar::startScan()
{
}

bool RPLidar::stopScan()
{
}
