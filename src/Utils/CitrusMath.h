/*
 * CitrusMath.h
 *
 *  Created on: Oct 3, 2015
 *      Author: Kyle
 */

#ifndef SRC_UTILS_CITRUSMATH_H_
#define SRC_UTILS_CITRUSMATH_H_

#include "Matrix.h"
#include "unitscpp.h"

/**
 * Find the smallest distance between the two angles (bounded from -180 degrees to 180 degrees)
 * @param a1 The first angle
 * @param a2 The second angle
 * @return The distance between a1 and a2
 */
Angle FindAngleDifference(Angle a1, Angle a2);

/**
 * Wraps an angle to a specific period
 * @param a The angle to be wrapped
 * @param lowerBound The lower bound on the new angle space
 * @return Angle a remapped from lowerBound to lowerBound + 180 degrees
 */
Angle WrapAngle(Angle a, Angle lowerBound);

double sin(Angle a);
double cos(Angle a);
double tan(Angle a);

double csc(Angle a);
double sec(Angle a);
double cot(Angle a);

Angle asin(Unitless a);
Angle acos(Unitless a);
Angle atan(Unitless a);
Angle atan2(Length a, Length b);

/**
 * Finds the minimum of two values
 * @param t1
 * @param t2
 * @return The smaller of t1 and t2
 */
template <typename T>
T min(T t1, T t2)
{
	return (t1 < t2 ? t1 : t2);
}

/**
 * Finds the maximum of two values
 * @param t1
 * @param t2
 * @return The larger of t1 and t2
 */
template <typename T>
T max(T t1, T t2)
{
	return (t1 > t2 ? t1 : t2);
}

/**
 * Bounds a value between a lower and an upper bound
 * @param value
 * @param lowerBound
 * @param upperBound
 * @return The value, guaranteed to be between lowerBound and upperBound
 */
template <typename T>
T BoundValue(T value, T lowerBound, T upperBound)
{
	return max(lowerBound, min(upperBound, value));
}

#endif /* SRC_UTILS_CITRUSMATH_H_ */
