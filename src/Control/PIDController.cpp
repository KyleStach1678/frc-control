/*
 * PIDController.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: Kyle
 */

#include "PIDController.h"

namespace Citrus
{

PIDController::~PIDController()
{
	// TODO Auto-generated destructor stub
}

double PIDController::Calculate(double value, Time dt)
{
	double error = target - value;
	integral += error * dt();
	double derivative = ((error - lastError) / dt)();
	return error * kP + integral * kI + derivative * kD;
}

bool PIDController::IsFinished()
{
	return lastError < 1;
}

} /* namespace Citrus */
