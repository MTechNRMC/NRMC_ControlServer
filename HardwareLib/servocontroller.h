#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include "peripheral.h"


namespace NRMCHardware
{
	// Interface
	class ServoController : public Peripheral
	{
		// Associations
		// Attributes
		// Operations
	public:
		virtual int getNumOfServos() = 0;
		virtual void setPos(int servo, char pos) = 0;
		virtual void setPos(int servo, double pos) = 0;
		ServoController() {};
		~ServoController() {};
	};
}

#endif
