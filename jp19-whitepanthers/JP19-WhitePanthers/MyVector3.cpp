/// <summary>
/// Vector 3 class
///16/12/17
/// </summary>
#include "MyVector3.h"
#define PI           3.14159265358979323846

/// <summary>
/// Defautl constructor set all 3 values to zero
/// </summary>
MyVector3::MyVector3() :
	x{ 0.0 },
	y{ 0.0 },
	z{ 0.0 }
{
}

/// <summary>
/// default destructor
/// nothing to release because we only have
/// primitive type data
/// </summary>
MyVector3::~MyVector3()
{
}

/// <summary>
/// 
/// </summary>
/// <returns>the vector as a string surrounded by square brackets and seperated by commas</returns>
std::string MyVector3::toString()
{
	const std::string output = "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
	return output;
}

MyVector3::MyVector3(double t_x, double t_y, double t_z)
{
	x = t_x;
	y = t_y;
	z = t_z;
}

MyVector3::MyVector3(sf::Vector3f t_sfVector)
{
	x = static_cast<float>(t_sfVector.x);
	y = static_cast<float>(t_sfVector.y);
	z = static_cast<float>(t_sfVector.z);
}

MyVector3::MyVector3(sf::Vector3i t_sfVector)
{
	x = static_cast<int>(t_sfVector.x);
	y = static_cast<int>(t_sfVector.y);
	z = static_cast<int>(t_sfVector.z);
}

MyVector3::MyVector3(sf::Vector2i t_sfVector)
{
	x = static_cast<int>(t_sfVector.x);
	y = static_cast<int>(t_sfVector.y);
	z = 0.0;
}

MyVector3::MyVector3(sf::Vector2u t_sfVector)
{
	x = static_cast<unsigned int>(t_sfVector.x);
	y = static_cast<unsigned int>(t_sfVector.y);
	z = 0.0;
}

MyVector3::operator sf::Vector2u()
{
	double newx{ x };
	double newy{ y };
	if (newx < 0)
	{
		newx = -newx;
	}
	if (newy < 0)
	{
		newy = -newy;
	}
	return sf::Vector2u{ static_cast<unsigned>(newx),static_cast<unsigned>(newy) };
}

MyVector3::MyVector3(sf::Vector2f t_sfVector)
{
	x = static_cast<float>(t_sfVector.x);
	y = static_cast<float>(t_sfVector.y);
	z = 0.0;
}

bool MyVector3::operator==(const MyVector3 t_right) const
{
	if (x == t_right.x && y == t_right.y && z == t_right.z)
	{
		return true;
	}
	return false;
}

bool MyVector3::operator!= (const MyVector3 t_right) const
{
	const bool answer(x != t_right.x || y != t_right.y || z != t_right.z);
	return answer;
}

MyVector3 MyVector3::operator+(const MyVector3 t_right) const
{
	return MyVector3(x + t_right.x, y + t_right.y, z + t_right.z);
}

MyVector3 MyVector3::operator-(const MyVector3 t_right) const
{
	return MyVector3(x - t_right.x, y - t_right.y, z - t_right.z);
}

MyVector3 MyVector3::operator*(const double t_scalar) const
{
	return MyVector3(x * t_scalar, y * t_scalar, z * t_scalar);
}

MyVector3 MyVector3::operator/(const double t_divisor) const
{
	if (t_divisor != 0)
	{
		return MyVector3(x / t_divisor, y / t_divisor, z / t_divisor);
	}
	else
	{
		return MyVector3{};
	}
}

MyVector3 MyVector3::operator +=(const MyVector3 t_right)
{
	x = x + t_right.x;
	y = y + t_right.y;
	z = z + t_right.z;

	return MyVector3(x, y, z);
}

MyVector3 MyVector3::operator -=(const MyVector3 t_right)
{
	x = x - t_right.x;
	y = y - t_right.y;
	z = z - t_right.z;

	return MyVector3(x, y, z);
}

MyVector3 MyVector3::operator-() const
{
	return MyVector3(-x, -y, -z);
}

double MyVector3::length() const
{
	const double result = std::sqrt(x * x + y * y + z * z);
	return result;
}

double MyVector3::lengthSquared() const
{
	const double result = std::pow(x, 2.0) + std::pow(y, 2.0) + std::pow(z, 2.0);
	return result;
}

double MyVector3::dot(const MyVector3 t_other) const
{
	return ((x * t_other.x) + (y* t_other.y) + (z * t_other.z));
}

MyVector3 MyVector3::crossProduct(const MyVector3 t_other) const
{
	double xVar = 0.0;
	double yVar = 0.0;
	double zVar = 0.0;

	xVar = y * (t_other.z) - z * (t_other.y);
	yVar = z * (t_other.x) - x * (t_other.z);
	zVar = x * (t_other.y) - y * (t_other.x);

	return MyVector3{ xVar,yVar,zVar };
}

double MyVector3::angleBetween(const MyVector3 t_other) const
{
	double top = dot(t_other);
	double under = length() * t_other.length();
	double angleInRadians;
	if (under != 0)
	{
		double answer = top / under;
		if (answer > 1) answer = 1;
		if (answer < -1) answer = -1;
		angleInRadians = std::acos(answer);
		const double angleInDegrees = angleInRadians * 180.0 / PI;
		return angleInDegrees;
	}
	return 0.0;
}

MyVector3 MyVector3::unit() const
{
	double var1{ 0.0 };
	double var2{ 0.0 };
	double var3{ 0.0 };
	double lenghtOfVector = length();
	if (lenghtOfVector != 0.0) // dont divide by zero
	{
		var1 = x / lenghtOfVector;
		var2 = y / lenghtOfVector;
		var3 = z / lenghtOfVector;
	}

	return MyVector3{ var1,var2,var3 }; // return a MYVector3
}

void MyVector3::reverseX()
{
	x = -x;
}

void MyVector3::reverseY()
{
	y = -y;
}

void MyVector3::normalise()
{
	double lenghtOfVector = length();
	if (lenghtOfVector != 0.0) //dont divide by zero
	{
		x = x / lenghtOfVector;
		y = y / lenghtOfVector;
		z = z / lenghtOfVector;
	}
}

MyVector3 MyVector3::projection(const MyVector3 t_other) const
{
	double lenghtSq = lengthSquared();
	double dotProduct = dot(t_other);
	double scale{ 1.0 };
	if (lenghtSq != 0)
	{
		scale = dotProduct / lenghtSq;
	}
	return this->operator*(scale);
}

MyVector3 MyVector3::rejection(const MyVector3 t_other) const
{
	return MyVector3(t_other - projection(t_other)); // takes the projection from the vector to get the rejection
}