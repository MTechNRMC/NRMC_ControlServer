#include "SimGHQS.h"

#include <fstream>
#include <sstream>
#include <iterator>
#include <chrono>

#include "..\..\NetworkLib\liadrmessage.h"

#define DELAY 1

using std::ifstream;
using std::stringstream;
using std::iterator;

using NRMCNetwork::LIADRMessage;

SimGHQS::SimGHQS(string file)
{
	int mode = 0;

	string line;
	sockaddr_in addr;	// dummy addr

	ghqsThread = 0;
	ifstream fstrm(file);

	while (std::getline(fstrm, line))
	{
		// check if we need to change mode
		if (line.length() > 1 && line[0] == '#')
		{
			if (line[1] == 'L')
				mode = 1;	// set to lidar
			else if (line[1] == 'A')
				mode = 2;	// set to accel
		}
		else if(!line.empty())
		{
			stringstream ss;
			ss.str(line);
			switch (mode)
			{
			case 1:		// lidar
				int range << ss;
				int angle << ss;
				lidar.push(new LIADRMessage(0, range, angle, 0, 0, addr));
				break;
			case 2:		// accel
				break;
			default:
				break;
			}
		}
	}
}

SimGHQS::~SimGHQS()
{
	if (ghqsThread != 0)
	{
		delete ghqsThread;
		ghqsThread = 0;
	}

	observers.clear();
}

Message * SimGHQS::queryHardware(Device device)
{
	Message* msg = 0;
	switch (device)
	{
	case NRMC_GHQS::LocalizationLIDAR:
		if (lidar.empty())
			break;
		msg = lidar.front();
		lidar.pop();
		break;
	case NRMC_GHQS::Accelerometer:
		if (accelGryo.empty())
			break;
		msg = accelGryo.front();
		accelGryo.pop();
		break;
	}

	return msg;
}

bool SimGHQS::startHardwareStream(GHQS_Observer & observer)
{
	obsrvMutx.lock();
	observers.push_back(&observer);
	obsrvMutx.unlock();

	// check if a thread needs to be started
	if (ghqsThread == 0)
		ghqsThread = new thread(&SimGHQS::ghqs, this);

	return true;
}

bool SimGHQS::stopHardwareStream(GHQS_Observer & observer)
{
	obsrvMutx.lock();
	for (vector<GHQS_Observer*>::iterator it = observers.begin(); it != observers.end(); it++)
	{
		if (*it == &observer)
			observers.erase(it);
	}
	obsrvMutx.unlock();

	// if there are no more observers kill the thread
	if (observers.empty() && ghqsThread != 0)
	{
		ghqsThread->join();
		delete ghqsThread;
		ghqsThread = 0;
	}

	return true;
}

void SimGHQS::ghqs()
{
	while (!observers.empty())
	{
		obsrvMutx.lock();
		// notifiy the observers
		for (int obsvr = 0; obsvr < observers.size(); obsvr++)
			observers[obsvr]->notify();
		obsrvMutx.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));	// sleep for the specfied delay
	}
}
