#include "Car.h"

Car::Car(LevelData & t_level, int t_colour) :
	m_levelData(t_level),
	m_colour(t_colour),
	m_texture(ResourceManager::m_textureHolder[t_level.m_myTextures.m_carsID])
{
	loadAssets();
	setColour(m_colour);
}

Car::~Car()
{
}

void Car::update(sf::Time t_dt)
{
	
}

void Car::setColour(int t_colour)
{
	m_carSprite.setTexture(m_texture);
	m_carSprite.setTextureRect(m_colourArray[t_colour]);
}

void Car::loadAssets()
{
	m_colourArray[0] = m_levelData.m_SpriteSheet.m_blueColour;
	m_colourArray[1] = m_levelData.m_SpriteSheet.m_greenColour;
	m_colourArray[2] = m_levelData.m_SpriteSheet.m_redColour;
	m_colourArray[3] = m_levelData.m_SpriteSheet.m_yellowColour;
}
