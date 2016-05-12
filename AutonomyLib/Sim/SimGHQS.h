#pragma once
#include <string>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>

#include "..\..\GHQ_Lib\ghqs_interface.h"

using std::string;
using std::thread;
using std::vector;
using std::queue;
using std::mutex;

using NRMC_GHQS::Device;
using NRMC_GHQS::GHQS_Observer;
using NRMC_GHQS::GHQS_Interface;

class SimGHQS :	public GHQS_Interface
{
private:
	thread* ghqsThread;
	vector<GHQS_Observer*> observers;
	queue<Message*> lidar;
	queue<Message*> accelGryo;
	mutex obsrvMutx;
public:
	SimGHQS(string file);
	~SimGHQS();
	Message* queryHardware(Device device);
	bool startHardwareStream(GHQS_Observer& observer);
	bool stopHardwareStream(GHQS_Observer& observer);
private:
	void ghqs();
};

