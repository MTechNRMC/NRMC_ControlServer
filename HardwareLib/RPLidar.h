/*
 * RPLidar.h
 *
 *  Created on: May 16, 2016
 *      Author: root
 */

#ifndef HARDWARELIB_RPLIDAR_H_
#define HARDWARELIB_RPLIDAR_H_

#include "lidar.h"
#include <string>
#include "peripheralsystem.h"
#include "peripheraltype.h"
#include "RPLidarIncludes/rplidar.h"

using std::string;
using namespace rp::standalone::rplidar;

namespace NRMCHardware
{
	class RPLidar: public Lidar
	{
	private:
		string port;
		PeripheralSystem sys;
		RPlidarDriver* driver;
	public:
		vector<ScanPoint> getScan();
		PeripheralType getType (  );
		PeripheralSystem getSystem ( );
		string getConnectedPort(  );
		RPLidar(string portName, unsigned int port, PeripheralSystem sys);
		virtual ~RPLidar();
		bool startScan();
		bool stopScan();
	private:
		bool checkRPLIDARHealth(RPlidarDriver& drv);
	};
}
#endif /* HARDWARELIB_RPLIDAR_H_ */
