#ifndef AI_CAR
#define AI_CAR

#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "Car.h"
#include <time.h>
#include "shader.h"

class AiCar : public Car
{
public:
	AiCar(LevelData & t_level, int t_colour);
	~AiCar();

	void init();
	void update(sf::Time t_dt);
	bool checkCollisionNode();
	sf::Vector2f seek(sf::Vector2f t_pos) const;
	void render(sf::RenderWindow & t_window);

	sf::Sprite getSprite() const { return m_carSprite; } 
	void brake(); //breaks
	void accelerate(); //accelerates car
	void checkIfCorner(); //checks if car is at a corner node
	void resetCar();

private:
	int m_colour; //colour of car
	void updateMovement(sf::Time dt);
	void setupNodes(); //setups nodes on track
	void updateTrail();
	
	LevelData & m_levelData;
	sf::CircleShape m_nodes[20];
	const int MAX_NODES = 20;
	sf::Vector2f m_position;
	int m_nodeIndex = 0;
	// The current rotation on car
	double m_rotation{ 0.0 };

	bool inCorner = false;
	// Current velocity.
	sf::Vector2f m_velocity;

	sf::Vector2f offset;
	// Steering vector.
	sf::Vector2f m_steering;
	//acceleration
	sf::Vector2f acceleration;
	// The ahead vector.
	sf::Vector2f m_ahead;

	// The half-ahead vector.
	sf::Vector2f m_halfAhead;

	// The maximum see ahead range.
	static float constexpr MAX_SEE_AHEAD{ 50.0f };

	std::list<Shader*> m_shaderTrailList;
	sf::Time m_trailTimer{ sf::seconds(0.0) };
	sf::Vector2f m_previousPos;
	static const int s_MAX_TRAIL = 5;
};

#endif //AI_CAR