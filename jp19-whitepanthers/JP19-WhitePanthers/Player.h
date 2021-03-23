#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Car.h"
#include "LevelLoader.h"
#include "Rhombus.h"
#include "Controller.h"
#include "Rhombus.h"
#include "MyMatrix3.h"
#include "Globals.h"
#include <Thor/Vectors.hpp>
#include <list>
#include "shader.h"
class Player : public Car
{
public:
	Player(LevelData &t_level, Xbox360Controller &t_controller, Rhombus &t_rhombus, int t_colour, sf::Sound &t_downsiftSound, sf::Sound &t_accelerateSound, sf::Sound &t_brakeSound);

	~Player();

	void update(sf::Time t_dt, Rhombus &t_rhombus);
	void render(sf::RenderWindow & t_window);

	void movement(sf::Time t_dt);

	sf::Vector2f getPosition();

	sf::VertexArray lines{sf::Lines};

	float getAngle(sf::Vector2f t_vec);

	void changeColour(int t_colour);

	int getColour();

	void resetPlayer();

	void updatePath();
	void clearPath();
	void drawPlayerPath(sf::RenderWindow & t_window);

	sf::Sprite getSprite();

private:

	void setupSprite();
	void updateTrail();

	LevelData & m_levelData;

	Xbox360Controller &m_controller;

	Rhombus & m_rhombus;
	 
	const int MAX_SPEED = 330;

	float m_currentSpeed;

	float m_steering;

	sf::Vector2f m_forwardVec;

	bool m_once{ false };
	bool m_playSound = true;
	sf::Vector2f m_previousPos;
	sf::Time m_trailTimer{ sf::seconds(0.0) };
	std::list<sf::CircleShape>m_path;
	static const int s_MAX_PATH = 10;
	const float m_STEP = 18.0f;
	sf::Sound &m_downshiftSound;
	sf::Sound &m_accelerateSound;
	sf::Sound &m_brakeSound;
	std::list<Shader*> m_shaderTrailList;
	static const int s_MAX_TRAIL = 5;
};
#endif //!PLAYER

