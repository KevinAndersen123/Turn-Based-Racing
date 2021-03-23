#include "shader.h"

sf::Texture Shader::m_objectTexture;
sf::Texture Shader::m_distortionMap;

Shader::Shader()
	: m_distortionFactor{ 0.175f }
	, m_riseFactor{ 5.0f }
{
	m_object.setTexture(m_objectTexture);
	m_object.setOrigin(m_object.getGlobalBounds().width / 2, m_object.getGlobalBounds().height / 2);

	if (!m_shader.loadFromFile("trail_shader.vs", "trail_shader.fs"))
	{
		sf::err() << "Failed to load shader, exiting..." << std::endl;
	}

	m_shader.setUniform("currentTexture", sf::Shader::CurrentTexture);
	m_shader.setUniform("distortionMapTexture", m_distortionMap);
}

Shader::~Shader()
{
}

void Shader::spawn(sf::Vector2f t_position, float t_rotation,int t_colour)
{
	m_object.setPosition(t_position);
	m_object.setRotation(t_rotation);
	m_colour = t_colour;
	switch (m_colour)
	{
	case 0:
		m_object.setColor(sf::Color{ 73,255,0,255 });
		break;
	case 1:
		m_object.setColor(sf::Color{ 253,0,255,255 });
		break;
	case 2:
		m_object.setColor(sf::Color{ 0,249,255,255 });
		break;
	case 3:
		m_object.setColor(sf::Color{ 253,255,1,255 });
		break;
	default:
		break;
	}
}

void Shader::changeOpacity()
{
	m_object.setColor(sf::Color(m_object.getColor().r, m_object.getColor().g,
		m_object.getColor().b,m_object.getColor().a - 50));
}

void Shader::update()
{
	m_shader.setUniform("time", m_clock.getElapsedTime().asSeconds());
	m_shader.setUniform("distortionFactor", m_distortionFactor);
	m_shader.setUniform("riseFactor", m_riseFactor);
}

void Shader::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_object, &m_shader);
}

void Shader::loadTextures()
{
	if (!m_objectTexture.loadFromFile("ASSETS/IMAGES/Haze.png"))
	{
		sf::err() << "Failed to load object texture, exiting..." << std::endl;
	}

	if (!m_distortionMap.loadFromFile("ASSETS/IMAGES/DistortionMap.png"))
	{
		sf::err() << "Failed to load distortion map, exiting..." << std::endl;
	}

	// It is important to set repeated to true to enable scrolling upwards
	m_distortionMap.setRepeated(true);

	// Setting smooth to true lets us use small maps even on larger images
	m_distortionMap.setSmooth(true);
}
