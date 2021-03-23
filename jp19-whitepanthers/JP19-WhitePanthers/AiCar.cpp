#include "AiCar.h"


AiCar::AiCar(LevelData & t_level, int t_colour) :
	Car(t_level, t_colour),
	m_levelData(t_level),
	m_colour{ t_colour },
	m_previousPos{ 0.0f,0.0f }
{
	srand(static_cast<unsigned>(time(NULL)));
	init();
	setupNodes();
	Shader::loadTextures();
}

AiCar::~AiCar()
{
}

void AiCar::init()
{
	CURRENT_SPEED[m_colour] = 0.0f;
	//setup green car
	if (m_colour == 0)
	{
		m_carSprite.setPosition(3475, 700);
		m_carSprite.setOrigin(177, 91);
		m_carSprite.setScale(0.25, 0.25);
		m_position = m_carSprite.getPosition();
	}
	//setup pink car
	else if (m_colour == 1)
	{
		m_carSprite.setPosition(3475, 650);
		m_carSprite.setOrigin(177, 91);
		m_carSprite.setScale(0.25, 0.25);
		m_position = m_carSprite.getPosition();
	}
	//setup blue car
	else if (m_colour == 2)
	{
		m_carSprite.setPosition(3475, 750);
		m_carSprite.setOrigin(177, 91);
		m_carSprite.setScale(0.25, 0.25);
		m_position = m_carSprite.getPosition();
	}
	//setup yellow car
	else if (m_colour == 3)
	{
		m_carSprite.setPosition(3475, 600);
		m_carSprite.setOrigin(177, 91);
		m_carSprite.setScale(0.25, 0.25);
		m_position = m_carSprite.getPosition();
	}
	
}

void AiCar::update(sf::Time t_dt)
{
	m_position = m_carSprite.getPosition();

	m_trailTimer -= t_dt;
	if (m_trailTimer <= sf::seconds(0.0f))
	{
		m_trailTimer = sf::seconds(0.05);
		updateTrail();
	}
	
	//Car::update(t_dt);
	if (checkCollisionNode())
	{
		m_nodeIndex++;
	}
	offset = (m_nodes[m_nodeIndex].getPosition() + sf::Vector2f{ (static_cast<float>(rand() % 100) + -100) , (static_cast<float>(rand() % 100) + -100) });
	//if collision go to next node
	
	//get vector to the next node
	sf::Vector2f vectorToNode = seek(sf::Vector2f(offset));
	
	//Car::update(t_dt);
	checkIfCorner();

	if (inCorner == true && CURRENT_SPEED[m_colour] > 150)
	{
		brake(); //brake if not at expected speed at corner
	}
	else
	{
		accelerate();
	}
	
	m_steering += thor::unitVector(vectorToNode);
	
	m_steering = MathUtility::truncate(m_steering, MAX_THROTTLE[m_colour]);
	acceleration = m_steering / MASS[m_colour];
	m_velocity = MathUtility::truncate(m_velocity + acceleration, CURRENT_SPEED[m_colour]);
	auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / thor::Pi * 180 + 180;

	auto currentRotation = m_rotation;

	// Find the shortest way to rotate towards the node
	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}

	else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation = static_cast<int>((m_rotation)+1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		m_rotation = static_cast<int>((m_rotation)-1) % 360;
	}
	updateMovement(t_dt);
}

bool AiCar::checkCollisionNode()
{

	if (m_nodes[m_nodeIndex].getGlobalBounds().intersects(m_carSprite.getGlobalBounds()))
	{
		if (m_nodeIndex < MAX_NODES-1)
		{
			return true;
		}
		else 
		{
			m_nodeIndex = 0;
		}
	}
	return false;
}

void AiCar::render(sf::RenderWindow & t_window)
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		for (sf::CircleShape const & node : m_nodes)
		{
			for (sf::CircleShape const & node : m_nodes)
			{
				t_window.draw(node);
			}
		}
	}
}

void AiCar::updateMovement(sf::Time dt)
{
	double speed = thor::length(m_velocity);

	sf::Vector2f newPos(m_carSprite.getPosition().x + std::cos(MathUtility::DEG_TO_RAD  * m_rotation) * speed * (dt.asSeconds()),
		m_carSprite.getPosition().y + std::sin(MathUtility::DEG_TO_RAD  * m_rotation) * speed * (dt.asSeconds()));
	m_carSprite.setPosition(newPos.x, newPos.y);
	m_carSprite.setRotation(m_rotation);
}

void AiCar::setupNodes()
{
	//sets up nodes 
	for (int i = 0; i < MAX_NODES; i++)
	{
		m_nodes[i].setFillColor(sf::Color::Red);
		m_nodes[i].setRadius(100);
		m_nodes[i].setOrigin(100, 100);
	}
	//turn one
	m_nodes[0].setPosition(3975, 700);
	m_nodes[1].setPosition(4375, 685);
	m_nodes[2].setPosition(4990, 610);
	m_nodes[3].setPosition(5200, 800);
	//turn two
	m_nodes[4].setPosition(5250, 1400);
	m_nodes[5].setPosition(5250, 2150);
	m_nodes[6].setPosition(5000, 2480);
	m_nodes[6].setRadius(200);
	//turn 3
	m_nodes[7].setPosition(4350, 2200);
	m_nodes[8].setPosition(4250, 1550);
	//chicane
	m_nodes[9].setPosition(3600, 1550);
	m_nodes[9].setRadius(180);

	m_nodes[10].setPosition(3550, 2250);
	m_nodes[10].setRadius(150);

	m_nodes[11].setPosition(3200, 2450);

	//turn4
	m_nodes[12].setPosition(2000, 2450);
	m_nodes[13].setPosition(1550, 2450);

	//turn5
	m_nodes[14].setPosition(1250, 2200); //brake point
	m_nodes[15].setPosition(1350, 1150);
	m_nodes[16].setPosition(1450, 1000);

	//end straight
	m_nodes[17].setPosition(1800, 700);
	m_nodes[18].setPosition(2400, 700);
	m_nodes[19].setPosition(3350, 700);

}

void AiCar::updateTrail()
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
	shader->spawn(m_position, m_rotation, m_colour);
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

void AiCar::brake()
{
	CURRENT_SPEED[m_colour] -= BRAKE_FORCE[m_colour];
	//std::cout << "breaking\n";
}

void AiCar::accelerate()
{
	if (CURRENT_SPEED[m_colour] <= TOP_SPEED[m_colour])
	{
		CURRENT_SPEED[m_colour] += MAX_THROTTLE[m_colour];
		//std::cout << "accelerate\n";
	}
}

void AiCar::checkIfCorner()
{
	if(m_nodeIndex == 3|| m_nodeIndex == 6 || m_nodeIndex == 9|| m_nodeIndex == 11 || m_nodeIndex == 14 || m_nodeIndex == 16)
	{
		inCorner = true;
	}
	else 
	{
		inCorner = false;
	}
}

void AiCar::resetCar()
{
	CURRENT_SPEED[m_colour] = 0.0f;
	m_steering = sf::Vector2f(0.0f,0.0f);
	m_rotation = 0.0;
	m_carSprite.setRotation(m_rotation);
	m_nodeIndex = 0;
	m_velocity = sf::Vector2f(0.0f, 0.0f);
	//setup green car
	if (m_colour == 0)
	{
		m_carSprite.setPosition(3475, 700);
		m_position = m_carSprite.getPosition();
	}
	//setup pink car
	else if (m_colour == 1)
	{
		m_carSprite.setPosition(3475, 650);
		m_position = m_carSprite.getPosition();
	}
	//setup blue car
	else if (m_colour == 2)
	{
		m_carSprite.setPosition(3475, 750);
		m_position = m_carSprite.getPosition();
	}
	//setup yellow car
	else if (m_colour == 3)
	{
		m_carSprite.setPosition(3475, 600);
		m_position = m_carSprite.getPosition();
	}
	while (m_shaderTrailList.size() != 0)
	{
		m_shaderTrailList.pop_back();
	}
}


sf::Vector2f AiCar::seek(sf::Vector2f t_pos) const
{
	return sf::Vector2f(t_pos - m_position);
}
