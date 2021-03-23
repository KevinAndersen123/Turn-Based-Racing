#ifndef RHOMBUS
#define RHOMBUS

#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "MathUtility.h"
#include "CollisionDetector.h"
#include "OrientedBoundingBox.h"
#include "MyVector3.h"


class Rhombus
{
public:
	Rhombus(Xbox360Controller & t_controller);
	~Rhombus();

	void update();

	void render(sf::RenderWindow & t_window);

	bool collision();

	float getAcceleration();

	float getAngle();

	void setPosition(sf::Vector2f t_pos);

	sf::Vector2f getDirection();

	float getRotation();

private:

	sf::VertexArray lines{ sf::Lines }; // vertex array for drawing vectors

	Xbox360Controller & m_controller; // reference to the player controller

	sf::RectangleShape m_rectangle; // the inner rectangle that allows the reticle to move in

	sf::CircleShape m_circle; // the outer circle

	sf::RectangleShape m_reticleSquare; // the player reticle to show the controllers thumbstick position in the rhombus

	sf::Vector2f m_direction; // the direction the player is going to move

	sf::Vector2f m_previousPos;
};



#endif //Rhombus