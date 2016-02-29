#ifndef MICROMAESTRO12_H
#define MICROMAESTRO12_H

#include "motorcontroller.h"
#include "servocontroller.h"

namespace NRMCHardware
{
	class MicroMaestro12 : public ServoController, public MotorController
	{
		// Associations
		// Attributes
	private:
		const int maxValue;
		SmrtSerialPort* port;
		// Operations
	public:
		int getNumOfServos();
		void setPos(int servo, char pos);
		void setPos(int servo, double pos);
		int getNumOfMotors();
		Direction* getDirection();
		Direction getDirection(int motor);
		double* getSpeed();
		double getSpeed(int motor);
		void setSpeed(int motor, char speed, Direction direction = both);
		void setSpeed(int motor, double speed, Direction direction = both);
		void setDirectionAll(Direction direction);
		void setDirection(int motor, Direction direction);
		MicroMaestro12(SmrtSerialPort* port);
		~MicroMaestro12();
		void allStop();
		static bool connectedTo(SerialPortInterface& port);
	};
}
#endif
