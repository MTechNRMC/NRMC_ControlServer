#include "micromaestro12.h"

using namespace NRMCHardware;

int MicroMaestro12::getNumOfServos (  )
{
	return 12;		// the micro mastro being used only allows for 12 servos per board and we will not be dasiy chaining them
}

int MicroMaestro12::getNumOfMotors()
{
	return getNumOfServos();	// same number of motors can be supported as servos
}

Direction MicroMaestro12::getDirection(int motor)
{
	if (motor < 0 || motor > getNumOfMotors())
		return Direction::stop;	// no motor so return stopped

	return motors[motor];
}

double NRMCHardware::MicroMaestro12::getSpeed(int motor, Direction direction)
{
	if(motor < 0 || motor > getNumOfMotors())
		return 0.0;	// motor does not exsist so return 0

	if (direction == Direction::backward)
		return (double)(motors[motor].backwardSpeed / maxValue);	// return the reverse speed
	
	return (double)(motors[motor].forwardSpeed / maxValue);			// return the forward speed
}

void NRMCHardware::MicroMaestro12::setSpeed(int motor, char speed, Direction direction)
{
	if (motor < 0 || motor > 1)
		return;	// fail

	// calc the speed
	char actSpeed = (char)((speed/maxValue) * motors[motor].netural);

	// set the speed in the specfied dir
	switch (direction)
	{
	case NRMCHardware::forward:		// set the forward speed
		motors[motor].forwardSpeed = actSpeed;
		break;
	case NRMCHardware::backward:	// set the reverse speed
		motors[motor].backwardSpeed = actSpeed;
		break;
	default:						// set the speed in both dir
		motors[motor].forwardSpeed = actSpeed;
		motors[motor].backwardSpeed = actSpeed;
		break;
	}

	// set the motor to the new values
	setMotor(motor);
}

void NRMCHardware::MicroMaestro12::setSpeed(int motor, double speed, Direction direction)
{
	if (speed < 0.0)
		speed = 0.0;
	else if (speed > 1.0)
		speed = 1.0;

	setSpeed(motor, (char)(speed*maxValue), direction);
}

void NRMCHardware::MicroMaestro12::setDirectionAll(Direction direction)
{
	for (int motor = 0; motor < getNumOfMotors(); motor++)
		setDirection(motor, direction);
}

void NRMCHardware::MicroMaestro12::setDirection(int motor, Direction direction)
{
	// check if a valid motor was passed
	if (motor < 0 || motor > 1)
		return;

	// set the new dir. Both is the same as stop
	motors[motor].dir = direction != Direction::both ? direction : Direction::stop;	
	setMotor(motor);				// set the changes
}


void MicroMaestro12::setPos ( int servo, char pos )
{
	char msg[] = { 0xFF, 0x00, 0x00 };	// base message
	// check if the servo number is correct
	if (servo < 0 || servo > maxValue)
		return;		// fail silently

	// set the servo to move and to what pos
	msg[1] = (char)servo;
	msg[2] = pos;

	port->getSerialPort().writeBytes(msg);
}

void MicroMaestro12::setPos ( int servo, double pos )
{
	// check if pos is between 0.0 and 1.0 if not clamp it to the respective value
	if (pos < 0.0)
		pos = 0.0;
	else if (pos > 1.0)
		pos = 1.0;

	// calc the actual pos
	char actPos = (char)(pos*maxValue);

	setPos(servo, actPos);
}

MicroMaestro12::MicroMaestro12 ( SmrtSerialPort* port )
{
	Motor tmp = { Direction::stop, Motor::netural, Motor::netural };
	this->port = port;
	motors = new Motor[getNumOfMotors()];

	// init all the motors
	for (int motor = 0; motor < getNumOfMotors(); motor++)
		motors[motor] = tmp;
}

MicroMaestro12::~MicroMaestro12 (  )
{
	delete[] motors;
	delete port;
}

void NRMCHardware::MicroMaestro12::allStop()
{
	setDirectionAll(Direction::stop);	// stop all the motors
}

bool NRMCHardware::MicroMaestro12::connectedTo(SerialPortInterface & port)
{
	char* receivedMsg;
	static const char errorRequest[] = { 0xA1 };
	port.writeBytes(errorRequest);

	// look for a response
	if ((receivedMsg = port.readBytes()) != 0)
		return true;	// a message was received can assume that a micro mastro is connected

	return false;	// no message was received on this port
}

void NRMCHardware::MicroMaestro12::setMotor(int motor)
{
	char speed;
	// check if the passed motor is valid
	if (motor < 0 || motor > 1)
		return;		 // fail

	switch (motors[motor].dir)
	{
	case Direction::backward:	// set move forward
		speed = motors[motor].backwardSpeed;
		break;
	case Direction::forward:	// set move backwards
		speed = motors[motor].forwardSpeed;
		break;
	default:					// default to stop
		speed = motors[motor].netural;
		break;
	}

	setPos(motor, speed);
}

