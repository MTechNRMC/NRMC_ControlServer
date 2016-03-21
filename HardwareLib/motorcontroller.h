#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "peripheral.h"
#include "direction.h"

namespace NRMCHardware
{
	// Interface
	class MotorController : public Peripheral
	{
		// Associations
		// Attributes
		// Operations
	public:
		virtual int getNumOfMotors() = 0;
		virtual Direction getDirection(int motor) = 0;
		virtual double getSpeed(int motor, Direction direction) = 0;
		virtual void setSpeed(int motor, char speed, Direction direction = both) = 0;
		virtual void setSpeed(int motor, double speed, Direction direction = both) = 0;
		virtual void setDirectionAll(Direction direction) = 0;
		virtual void setDirection(int motor, Direction direction) = 0;
		MotorController() {};
		virtual ~MotorController() {};
		virtual void allStop() = 0;
	};
}
#endif
