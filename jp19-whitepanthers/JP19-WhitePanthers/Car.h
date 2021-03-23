#ifndef CAR
#define CAR

#include <SFML/Graphics.hpp>
#include "MathUtility.h"
#include "LevelLoader.h"
#include "Thor/Vectors.hpp"
#include "ResourceManager.h"

class Car
{
public:
	Car(LevelData & t_level, int t_colour = 0);
	~Car();

	virtual void update(sf::Time t_dt);
	virtual void render(sf::RenderWindow & t_window) = 0;

	const float TOP_SPEED[4]{ 340.0f,340.0f,340.0f,320.0f };
	//max throttle car can give
	const float  MAX_THROTTLE[4]{ 1.4f,1.6f,1.6f,1.8f };
	// The maximum speed for this car
	float CURRENT_SPEED[4]{ TOP_SPEED[0], TOP_SPEED[1],TOP_SPEED[2],TOP_SPEED[3] };
	//mass of car
	const float MASS[4]{ 0.2f,0.18f,0.19f,0.17f };
	const float BRAKE_FORCE[4]{ 2.0f,1.5f,1.5f,1.25f }; //max force car can apply

protected:
	void setColour(int t_colour);

	sf::Sprite m_carSprite;
	sf::Texture &m_texture;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	float m_rotation;


	int m_colour;


private:
	LevelData &m_levelData;
	sf::IntRect m_colourArray[4];
	
	void loadAssets();
};
#endif // CAR
