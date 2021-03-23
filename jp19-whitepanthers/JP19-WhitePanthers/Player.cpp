#include "Player.h"

Player::Player(LevelData &t_level, Xbox360Controller &t_controller, Rhombus &t_rhombus, int t_colour, sf::Sound &t_downsiftSound, sf::Sound &t_accelerateSound, sf::Sound &t_brakeSound) :
	Car(t_level, t_colour),
	m_levelData(t_level),
	m_controller(t_controller),
	m_rhombus(t_rhombus),
	m_currentSpeed(0.0f),
	m_steering(0.0f),
	m_downshiftSound(t_downsiftSound),
	m_accelerateSound(t_accelerateSound),
	m_brakeSound(t_brakeSound)
{
	Shader::loadTextures();
	m_acceleration = sf::Vector2f{ 0.0f,0.0f };
	m_velocity = sf::Vector2f{ 3.0f,0.0f };
	m_forwardVec = sf::Vector2f(1, 0);

	setupSprite();
}

Player::~Player()
{
}

void Player::update(sf::Time t_dt, Rhombus &t_rhombus)
{
	Car::update(t_dt);
	movement(t_dt);
	m_position += m_velocity;
	m_carSprite.setPosition(m_position);
	m_carSprite.setRotation(thor::polarAngle(m_forwardVec));
	m_playSound = false;

	m_trailTimer -= t_dt;
	if (m_trailTimer <= sf::seconds(0.0))
	{
		m_trailTimer = sf::seconds(0.05);
		updateTrail();
	}
}

void Player::render(sf::RenderWindow & t_window)
{

	if (m_shaderTrailList.size() != 0)
	{
		std::list<Shader*>::iterator it = m_shaderTrailList.begin();

		for (; it != m_shaderTrailList.end(); it++)
		{
			Shader *shader = *it;
			shader->render(t_window);
		}
	}
	t_window.draw(m_carSprite);
	t_window.draw(lines);

}

void Player::movement(sf::Time t_dt)
{
		float const radius = 10;

		auto Theta = static_cast<MyVector3>(m_velocity).angleBetween(static_cast<MyVector3>(m_rhombus.getDirection()));

		Theta = (Theta - 90) * (thor::Pi / 180.0f);

		auto chord = (2 * (radius)) * (sin(Theta / 2.0f));

		auto height = radius * (1 - cos(Theta / 2.0f));

		auto vector = sf::Vector2f((height)-(chord / 2.0f), height);

		m_steering = m_rhombus.getAngle();

		m_steering = m_steering / (180.0f * (MASS[m_colour] + 1));

		thor::rotate(vector, -90.0f);
		thor::rotate(m_velocity, m_steering);
		thor::rotate((m_forwardVec), m_steering);
		
		float speed = thor::length( m_rhombus.getDirection() / (MAX_THROTTLE[m_colour]/ 0.05f));

		m_acceleration = vector +  m_velocity * speed;

		thor::setPolarAngle(m_acceleration, thor::polarAngle(m_forwardVec));

		m_velocity += m_acceleration;

		if (m_steering >= 0.3 || m_steering <= -0.3)
		{
			if (m_playSound == true)
			{
				m_downshiftSound.setPlayingOffset(sf::seconds(2));
				m_brakeSound.setPlayingOffset(sf::seconds(1));

				if (s_audioActive && s_sfxActive)
				{
					m_downshiftSound.play();
					m_brakeSound.play();
				}

				m_playSound = false;
			}
			m_velocity = MathUtility::truncate(m_velocity, 5.0);
		}
		else
		{
			if (m_playSound == true)
			{
				m_accelerateSound.setPlayingOffset(sf::seconds(1.5));
				if (s_audioActive && s_sfxActive)
				{
					m_accelerateSound.play();
				}
				m_brakeSound.stop();
				m_downshiftSound.stop();
				m_playSound = false;
			}
			m_velocity = MathUtility::truncate(m_velocity, 6);
		}

}

float Player::getAngle(sf::Vector2f t_vec)
{
	sf::Vector2f upVec = sf::Vector2f(0, -1);

	auto angleBetween = static_cast<MyVector3>(upVec).angleBetween(t_vec);

	return angleBetween;
}

void Player::changeColour(int t_colour)
{
	m_colour = t_colour;

	if (m_colour < 0)
	{
		m_colour = 0;
	}
	else if (m_colour > 3)
	{
		m_colour = 3;
	}

	Car::setColour(m_colour);
}

int Player::getColour()
{
	return m_colour;
}

void Player::resetPlayer()
{
	m_brakeSound.stop();
	m_downshiftSound.stop();
	m_accelerateSound.stop();
	m_position = m_levelData.m_car1.m_position;
	m_carSprite.setPosition(m_position);

	m_acceleration = sf::Vector2f(0.0f, 0.0f);
	thor::setPolarAngle(m_forwardVec, 0.0f);
	thor::setPolarAngle(m_velocity, thor::polarAngle(m_forwardVec));

	m_carSprite.setRotation(thor::polarAngle(m_forwardVec));

	while (m_shaderTrailList.size() != 0)
	{
		m_shaderTrailList.pop_back();
	}
}

void Player::drawPlayerPath(sf::RenderWindow & t_window)
{
	for (auto circ : m_path)
	{
		t_window.draw(circ);
	}
}

sf::Sprite Player::getSprite()
{
	return m_carSprite;
}

void Player::updatePath()
{
	m_playSound = true;
	m_path.clear();

	float steering;
	sf::Vector2f vel = m_velocity;

	for (int i = 0; i < s_MAX_PATH; i++)
	{
			steering = m_rhombus.getAngle();

			steering = (steering / 180.0f) * s_MAX_PATH;

			thor::rotate(vel, steering);

			sf::CircleShape circ(10);
			circ.setPosition((m_position) + sf::Vector2f(vel.x * (m_STEP * i), vel.y * (m_STEP * i)));
			circ.setOrigin(circ.getGlobalBounds().width / 2, circ.getGlobalBounds().height / 2);
			circ.setFillColor(sf::Color::Red);
			m_path.push_front(circ);
	}
	
}

void Player::clearPath()
{
	m_path.clear();
}

sf::Vector2f Player::getPosition()
{
	return m_position;
}

void Player::setupSprite()
{
	m_position = m_levelData.m_car1.m_position;
	m_carSprite.setPosition(m_position);
	m_carSprite.setOrigin(177, 91);
	m_carSprite.setScale(0.25, 0.25);

	m_previousPos = m_position;
}

void Player::updateTrail()
{
	if (m_shaderTrailList.size() != 0)
	{
		std::list<Shader*>::iterator it = m_shaderTrailList.begin();

		for (; it != m_shaderTrailList.end(); it++)
		{
			Shader *shader = *it;
			shader->changeOpacity();
		}
	}
	Shader *shader = new Shader();
	shader->spawn(m_position, thor::polarAngle(m_forwardVec), m_colour);
	m_shaderTrailList.push_front(shader);

	if (m_shaderTrailList.size() > s_MAX_TRAIL)
	{
		m_shaderTrailList.pop_back();
	}

	if (m_shaderTrailList.size() > s_MAX_TRAIL)
	{
		m_shaderTrailList.pop_back();
	}

	if (m_shaderTrailList.size() != 0)
	{
		std::list<Shader*>::iterator it = m_shaderTrailList.begin();

		for (; it != m_shaderTrailList.end(); it++)
		{
			Shader *shader = *it;
			shader->update();
		}
	}
}
