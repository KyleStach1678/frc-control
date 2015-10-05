/*
 * CitrusMath.cpp
 *
 *  Created on: Oct 3, 2015
 *      Author: Kyle
 */

#include "CitrusMath.h"
#include <cmath>

Angle FindAngleDifference(Angle a1, Angle a2)
{
	return WrapAngle(a1 - a2, -180 * deg);
}

Angle WrapAngle(Angle a, Angle lowerBound)
{
	return std::fmod((a - lowerBound).to(deg), 360) * deg + lowerBound;
}

double sin(Angle a)
{
	return std::sin(a.to(rad));
}

double cos(Angle a)
{
	return std::cos(a.to(rad));
}

double tan(Angle a)
{
	return std::tan(a.to(rad));
}

double csc(Angle a)
{
	return 1 / sin(a);
}

double sec(Angle a)
{
	return 1 / cos(a);
}

double cot(Angle a)
{
	return 1 / tan(a);
}

Angle atan2(Length a, Length b)
{
	return atan(a / b);
}

Angle asin(Unitless a)
{
	return std::asin(a());
}

Angle acos(Unitless a)
{
	return std::acos(a());
}

Angle atan(Unitless a)
{
	return std::atan(a());
}
