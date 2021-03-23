#pragma once

#include <string>
#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelLoader.h"

class ResourceManager
{
public:	
	static void loadResources(LevelData & t_data);
	static thor::ResourceHolder<sf::Texture, std::string> m_textureHolder;
	static thor::ResourceHolder<sf::Font, std::string> m_fontHolder;
	static thor::ResourceHolder<sf::SoundBuffer, std::string> m_soundHolder;
};
