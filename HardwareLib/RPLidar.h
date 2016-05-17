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

using std::string;

namespace NRMCHardware
{
	class RPLidar: public NRMCHardware::Lidar
	{
	private:
		string port;
		PeripheralSystem sys;
	public:
		vector<ScanPoint> getScan();
		PeripheralType getType (  );
		PeripheralSystem getSystem ( );
		string getConnectedPort(  );
		RPLidar(string portName, unsigned int port, PeripheralSystem sys);
		virtual ~RPLidar();
		bool startScan();
		bool stopScan();
	};
}
#endif /* HARDWARELIB_RPLIDAR_H_ */
