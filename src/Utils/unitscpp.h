#ifndef unitscpp_h
#define unitscpp_h

#include <ostream>
#include <sstream>
#include <string>

typedef double NT; // Number Type

template <int U1, int U2, int U3, int U4, int U5>
class Units
{
  public:
	static const int AnglePow = U1;
	static const int LengthPow = U2;
	static const int TimePow = U3;
	static const int MassPow = U4;
	static const int CurrentPow = U5;

	Units(NT value_ = NT(0)) : value(value_)
	{
	}

	// This turns the class into a function object that allows
	// the user to easily get at the value.
	NT operator()() const
	{
		return value;
	}

	// Helper function to get a text representation of the
	// object's dimensions.  It is static because the
	// representation is known at compile time.
	static std::string dim(void)
	{
		std::stringstream s;
		s << "<" << U1 << "," << U2 << "," << U3 << "," << U4 << "," << U5 << ">";
		return s.str();
	}

	// Helper function for unit conversions.
	NT to(const Units& u) const
	{
		return value / u();
	}

	Units& operator=(const Units& rhs)
	{
		value = rhs();
		return *this;
	}

	// Arithmetic operators
	Units& operator+=(const Units& rhs)
	{
		value += rhs.value;
		return *this;
	}

	Units& operator-=(const Units& rhs)
	{
		value -= rhs.value;
		return *this;
	}

	Units& operator*=(const NT& rhs)
	{
		value *= rhs;
		return *this;
	}

	Units& operator/=(const NT& rhs)
	{
		value /= rhs;
		return *this;
	}

  private:
	NT value;
};

// Addition
template <int U1, int U2, int U3, int U4, int U5>
const Units<U1, U2, U3, U4, U5> operator+(const Units<U1, U2, U3, U4, U5>& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return Units<U1, U2, U3, U4, U5>(lhs() + rhs());
}

// Subtraction
template <int U1, int U2, int U3, int U4, int U5>
const Units<U1, U2, U3, U4, U5> operator-(const Units<U1, U2, U3, U4, U5>& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return Units<U1, U2, U3, U4, U5>(lhs() - rhs());
}

// Multiplication
template <int U1, int U2, int U3, int U4, int U5>
const Units<U1, U2, U3, U4, U5> operator*(const NT& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return Units<U1, U2, U3, U4, U5>(lhs * rhs());
}

template <int U1, int U2, int U3, int U4, int U5>
const Units<U1, U2, U3, U4, U5> operator*(const Units<U1, U2, U3, U4, U5>& lhs, const NT& rhs)
{
	return rhs * lhs;
}

template <int U1a, int U2a, int U3a, int U4a, int U5a, int U1b, int U2b, int U3b, int U4b, int U5b>
const Units<U1a + U1b, U2a + U2b, U3a + U3b, U4a + U4b, U5a + U5b> operator*(const Units<U1a, U2a, U3a, U4a, U5a>& lhs,
																			 const Units<U1b, U2b, U3b, U4b, U5b>& rhs)
{
	return Units<U1a + U1b, U2a + U2b, U3a + U3b, U4a + U4b, U5a + U5b>(lhs() * rhs());
}

// Division
template <int U1, int U2, int U3, int U4, int U5>
const Units<U1, U2, U3, U4, U5> operator/(const Units<U1, U2, U3, U4, U5>& lhs, const NT& rhs)
{
	return Units<U1, U2, U3, U4, U5>(lhs() / rhs);
}

template <int U1, int U2, int U3, int U4, int U5>
const Units<-U1, -U2, -U3, -U4, -U5> operator/(const NT& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return Units<-U1, -U2, -U3, -U4, -U5>(lhs / rhs());
}

template <int U1a, int U2a, int U3a, int U4a, int U5a, int U1b, int U2b, int U3b, int U4b, int U5b>
const Units<U1a - U1b, U2a - U2b, U3a - U3b, U4a - U4b, U5a - U5b> operator/(const Units<U1a, U2a, U3a, U4a, U5a>& lhs,
																			 const Units<U1b, U2b, U3b, U4b, U5b>& rhs)
{
	return Units<U1a - U1b, U2a - U2b, U3a - U3b, U4a - U4b, U5a - U5b>(lhs() / rhs());
}

// Comparisons and ordering
template <int U1, int U2, int U3, int U4, int U5>
bool operator==(const Units<U1, U2, U3, U4, U5>& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return (lhs() == rhs());
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator==(const Units<U1, U2, U3, U4, U5>& lhs, const NT& rhs)
{
	return (lhs() == rhs);
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator==(const NT& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return (lhs == rhs());
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator!=(const Units<U1, U2, U3, U4, U5>& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return not(lhs() == rhs());
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator!=(const Units<U1, U2, U3, U4, U5>& lhs, const NT& rhs)
{
	return not(lhs() == rhs);
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator!=(const NT& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return not(lhs == rhs());
}

// Ordering
template <int U1, int U2, int U3, int U4, int U5>
bool operator<=(const Units<U1, U2, U3, U4, U5>& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return lhs() <= rhs();
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator<=(const Units<U1, U2, U3, U4, U5>& lhs, const NT& rhs)
{
	return (lhs() <= rhs);
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator<=(const NT& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return (lhs <= rhs());
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator>=(const Units<U1, U2, U3, U4, U5>& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return lhs() >= rhs();
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator>=(const Units<U1, U2, U3, U4, U5>& lhs, const NT& rhs)
{
	return (lhs() >= rhs);
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator>=(const NT& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return (lhs >= rhs());
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator<(const Units<U1, U2, U3, U4, U5>& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return lhs() < rhs();
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator<(const Units<U1, U2, U3, U4, U5>& lhs, const NT& rhs)
{
	return (lhs() < rhs);
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator<(const NT& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return (lhs < rhs());
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator>(const Units<U1, U2, U3, U4, U5>& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return lhs() > rhs();
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator>(const Units<U1, U2, U3, U4, U5>& lhs, const NT& rhs)
{
	return (lhs() > rhs);
}

template <int U1, int U2, int U3, int U4, int U5>
bool operator>(const NT& lhs, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return (lhs > rhs());
}

template <int U1, int U2, int U3, int U4, int U5>
std::ostream& operator<<(std::ostream& s, const Units<U1, U2, U3, U4, U5>& rhs)
{
	return s << rhs();
}

// Typedefs for fundamental units
typedef Units<1, 0, 0, 0, 0> Angle;
typedef Units<0, 1, 0, 0, 0> Length;
typedef Units<0, 0, 1, 0, 0> Time;
typedef Units<0, 0, 0, 1, 0> Mass;
typedef Units<0, 0, 0, 0, 1> Current;

// Typedefs for derived units
typedef Units<0, 1, -1, 0, 0> Velocity;
typedef Units<0, 1, -2, 0, 0> Acceleration;
typedef Units<1, 0, -1, 0, 0> AngularVelocity;
typedef Units<1, 0, -2, 0, 0> AngularAcceleration;
typedef Units<0, 1, -2, 1, 0> Force;
typedef Units<0, -1, -2, 1, 0> Pressure;
typedef Units<0, -1, -2, 1, 0> Stress;
typedef Units<0, 2, -2, 1, 0> Energy;
typedef Units<0, 0, -1, 0, 0> Frequency;
typedef Units<0, 2, -3, 1, -1> Voltage;

// Unit constants
const double pi = 3.14159265358;
const Length m = 1;
const Length km = 1e3 * m;
const Length cm = 1e-2 * m;
const Length mm = 1e-3 * m;
const Length in = 2.54 * cm;
const Length ft = 12 * in;
const Angle rad = 1;
const Angle deg = 1.74532925e-2;
const Angle rev = 2 * pi * deg;
const Mass kg = 1;
const Mass g = .001 * kg;
const Mass mg = .001 * g;
const Time s = 1;
const Time hour = 3600 * s;
const Current A = 1;
const Voltage V = kg * m * m / (A * s * s * s);
const Length click = pi * 4 * in / 360;
const Length robotWidth = 1.5 * ft;
const Velocity maxHighRobotSpeed = 15 * ft / s;
const Velocity maxLowRobotSpeed = 5 * ft / s;
const AngularVelocity maxHighRobotAngularVelocity = 2 * maxHighRobotSpeed / (robotWidth / 2) * rad;

#endif //#ifndef unitscpp_h
