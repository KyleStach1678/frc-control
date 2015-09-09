/*
 * PIDController.cpp
 *
 *  Created on: Sep 7, 2015
 *      Author: Kyle
 */

#include <Control/PIDController.h>

namespace Citrus
{

PIDController::PIDController(PIDSourcePtr sensor, PIDOutputPtr actuator, double kP, double kI, double kD) : Controller(sensor, actuator)
{
	proportional = integral = derivative = 0;
	this->kP = kP;
	this->kI = kI;
	this->kD = kD;
	this->goal = 0;
}

PIDController::~PIDController()
{
	// TODO Auto-generated destructor stub
}

void PIDController::SetGoal(double goal)
{
	this->goal = goal;
}

double PIDController::Calculate(double input, Time dt)
{
	double error = goal - input;
	derivative = (error - proportional) / dt();
	proportional = error;
	integral += input * dt();
	return kP * proportional + kI * integral + kD * derivative;
}

void PIDController::Start()
{
	Controller::Start();
}

bool PIDController::IsFinished()
{
	return false;
}

void PIDController::Stop()
{
	Controller::Start();
}

} /* namespace Citrus */
