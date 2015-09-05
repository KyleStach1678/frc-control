#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

namespace RobotMap
{
const int lowGear = 1;
const int highGear = 2;

const int leftDrivePorts[] = {1, 8};
const int rightDrivePorts[] = {2, 7};
const int elevatorMotor = 5;

const int leftDriverStick = 0;
const int rightDriverStick = 1;

const int elevatorEncoders[] = {14, 15};
const int leftDriveEncoders[] = {12, 13};
const int rightDriveEncoders[] = {10, 11};

const int elevatorHallSensor = 0;

const int bottomElevatorProximity = 0;
const int topElevatorProximity = 1;
}

#endif
