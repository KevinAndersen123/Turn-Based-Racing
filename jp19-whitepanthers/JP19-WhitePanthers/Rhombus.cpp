#include "Rhombus.h"

Rhombus::Rhombus(Xbox360Controller & t_controller) :
	m_controller(t_controller)
{

	m_rectangle.setSize(sf::Vector2f(125, 125));
	m_rectangle.setRotation(45);
	m_rectangle.setFillColor(sf::Color::White);
	
	m_rectangle.setOutlineColor(sf::Color::White);
	m_rectangle.setPosition(500.0f, 500.0f);
	m_rectangle.setOrigin(m_rectangle.getSize().x / 2.0f, m_rectangle.getSize().y / 2.0f);

	m_circle.setFillColor(sf::Color::Transparent);
	m_circle.setOutlineColor(sf::Color::White);
	m_circle.setRadius(m_rectangle.getSize().x * 0.75f);
	m_circle.setOutlineThickness(10);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setPosition(m_rectangle.getPosition());
	

	m_reticleSquare.setFillColor(sf::Color::Red);
	m_reticleSquare.setSize(sf::Vector2f(5,5));
	m_reticleSquare.setOrigin(m_reticleSquare.getSize().x / 2.0f, m_reticleSquare.getSize().y / 2.0f);
	m_reticleSquare.setPosition(m_rectangle.getPosition());
}

Rhombus::~Rhombus()
{
}

void Rhombus::update()
{	
	

	if (collision())
	{
		m_previousPos =  m_rectangle.getPosition();
		m_reticleSquare.setPosition(m_reticleSquare.getPosition() + (m_controller.m_currentState.LeftThumbStick / 20.0f) );
	}
	else
	{
		m_reticleSquare.setPosition(m_previousPos);
	}

	getDirection();

	/*lines.clear();
	lines.append(sf::Vertex{ m_rectangle.getPosition(), sf::Color::Red });
	lines.append(sf::Vertex{ m_reticleSquare.getPosition(), sf::Color::Red });*/
}

void Rhombus::render(sf::RenderWindow & t_window)
{

	t_window.draw(m_rectangle);
	t_window.draw(m_circle);

	if (collision())
	{
		t_window.draw(m_reticleSquare);
	}

	t_window.draw(lines);

	
}

bool Rhombus::collision()
{
	return CollisionDetector::collision(m_rectangle, m_reticleSquare);
}

float Rhombus::getAcceleration()
{
	auto length = getDirection();

	return thor::length(length) ;
}

float Rhombus::getAngle()
{
	sf::Vector2f upVec = sf::Vector2f(0, -1);

	auto angleBetween = static_cast<MyVector3>(upVec).angleBetween(m_direction);

	/*if (angleBetween > 45)
	{
		angleBetween = 45;
	}*/

	if (m_direction.x < 0)
	{
		return -(angleBetween);
	}
	else if (m_direction.x > 0)
	{
		return angleBetween;
	}

	return 0;
	
}

void Rhombus::setPosition(sf::Vector2f t_pos)
{
	m_rectangle.setPosition(t_pos);
	m_circle.setPosition(m_rectangle.getPosition());
	m_reticleSquare.setPosition(m_rectangle.getPosition());
}

sf::Vector2f Rhombus::getDirection()
{
	m_direction = m_reticleSquare.getPosition() - m_rectangle.getPosition();

	if (m_direction != sf::Vector2f{ 0.0f,0.0f })
	{
		if (m_direction.x < 0.1 && m_direction.x > -0.1)
		{
			m_direction.x = 0;
		}
		else if (m_direction.y < 0.1 && m_direction.y > -0.1)
		{
			m_direction.y = 0;
		}

		return m_direction;
	}

	return sf::Vector2f(0,0);
}

float Rhombus::getRotation()
{
	return 1.0f;
}
