/*
 * PIDController.cpp
 *
 *  Created on: Sep 7, 2015
 *      Author: Kyle
 */

#include "PIDController.h"

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

double PIDController::Calculate(double input, Time dt)
{
	double error = goal - input;
	derivative = (error - proportional) / dt.to(s);
	proportional = error;
	integral += input * dt.to(s);
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
