#ifndef MYVECTOR3 
#define MYVECTOR3


/// <summary>
/// <summary>
/// Cliona Hayden
/// </summary>

#include <SFML/Graphics.hpp>
#include <string.h>
#include <math.h>

class MyVector3
{
public:
	//x coordinate
	double x;
	//y coordinate
	double y;
	//z coordinate
	double z;

	//Standard constructor
	MyVector3();
	//Standard destructor
	~MyVector3();
	//variable for converting vectors to string to output to the user
	std::string toString();

	//Constructors
	//Constructor taking 2 doubles
	MyVector3(double x, double y, double z);
	//Constructor takes vector3f, float
	MyVector3(sf::Vector3f t_sfVector);
	//Constructor takes vector3i, int
	MyVector3(sf::Vector3i t_sfVector);
	//Constructor takes vector2i, int
	MyVector3(sf::Vector2i t_sfVector);
	//Constructor takes vector2u, unsigned int
	MyVector3(sf::Vector2u t_sfVector);
	//Constructor takes vector2f, float
	MyVector3(sf::Vector2f t_sfVector);

	//equality operator, returns 1 if the vectors are the same
	bool operator == (const MyVector3 t_right) const;
	//inequality operator, returns 1 if the vectors are not the same
	bool operator != (const MyVector3 t_right) const;

	//Adds the x value of the first vector to the x value of the second and returns the resulting x value to a new vector3 and so on for the 
	//two values.
	MyVector3 operator +(const MyVector3 t_right) const;
	//subtracts the x value of the first vector from the x value of the second and returns the resulting x value to a new vector3 and so on for the next 
	//two values.
	MyVector3 operator -(const MyVector3 t_right) const;
	//multiplys the x value of the vector by a scalar and does this again for the next two values and returns a new resultng vector3.
	MyVector3 operator *(const double t_scalar) const;
	//divides the x value of the vector by a divisor and does this again for the next two values and returnns a new resulting vector3.
	MyVector3 operator /(const double t_divisor) const;
	//adds two vectors and assigns the new resulting vector to the first vector that was added to the second.
	MyVector3 operator +=(const MyVector3 t_right);
	//subtracts two vectors and assigns the new resulting vector to the first vector that was subtracted from the second.
	MyVector3 operator -=(const MyVector3 t_right);

	//Makes the values x,y,z of a vector negative
	MyVector3 operator -() const;
	void reverseX();
	void reverseY();

	//Calculates the lenght of a vector using the x,y,z values and returns it as a double.
	double length() const;
	//Calculates the lenght squared by getting it in radians and then converting it to degrees as a double
	double lengthSquared() const;
	//Gets the dot by multiplying the three values by their conterpart in the other vector
	double dot(const MyVector3 t_other) const;
	//gets the cross product of two vectors using matrixs
	MyVector3 crossProduct(const MyVector3 t_other) const;
	//Gets the angle between two vectors in degrees
	double angleBetween(const MyVector3 t_other) const;
	//gets the unit vector of a vector by dividing the values by the lenght of the vector
	MyVector3 unit() const;
	//normalise the vector and returns nothing
	void normalise();
	//gets the projestion of on vecor on the other and it should be parrallel to the opposing vector
	MyVector3 projection(const MyVector3 t_other) const;
	//gets the rejection by subtracting the vector from the projection
	MyVector3 rejection(const MyVector3 t_other) const;


	operator sf::Vector2f() { return sf::Vector2f{ static_cast<float>(x),static_cast<float>(y) }; };
	operator sf::Vector2i() { return sf::Vector2i{}; };
	operator sf::Vector2u();
	operator sf::Vector3i() { return sf::Vector3i{}; };
	operator sf::Vector3f() { return sf::Vector3f{}; };
};



#endif // !MYVECTOR3