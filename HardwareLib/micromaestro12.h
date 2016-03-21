#ifndef MICROMAESTRO12_H
#define MICROMAESTRO12_H

#include "motorcontroller.h"
#include "servocontroller.h"
#include "smrtserialport.h"

namespace NRMCHardware
{
	class MicroMaestro12 : public ServoController, public MotorController
	{
		// Associations
		// Attributes
	private:
		struct Motor
		{
			Direction dir;
			char forwardSpeed;
			char backwardSpeed;
			static const char netural = 127;
		};
		const char maxValue = 254;	// we will be using a one byte resolution
		SmrtSerialPort* port;
		Motor* motors;
		// Operations
	public:
		int getNumOfServos();
		void setPos(int servo, char pos);
		void setPos(int servo, double pos);
		int getNumOfMotors();
		Direction getDirection(int motor);
		double getSpeed(int motor, Direction direction);
		void setSpeed(int motor, char speed, Direction direction = both);
		void setSpeed(int motor, double speed, Direction direction = both);
		void setDirectionAll(Direction direction);
		void setDirection(int motor, Direction direction);
		MicroMaestro12(SmrtSerialPort* port);
		~MicroMaestro12();
		void allStop();
		static bool connectedTo(SerialPortInterface& port);
	private:
		void setMotor(int motor);
	};
}
#endif
