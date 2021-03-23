#pragma once
#include <SFML/Graphics.hpp>
class Shader
{
public:
	Shader();
	~Shader();

	void spawn(sf::Vector2f t_position, float t_rotation,int t_colour);
	void changeOpacity();

	void update();
	void render(sf::RenderWindow &t_window);

	static void loadTextures();
private:
	static sf::Texture m_objectTexture;
	static sf::Texture m_distortionMap;

	sf::Sprite m_object;

	sf::Shader m_shader;
	int m_colour;
	sf::Clock m_clock;
	float m_distortionFactor;
	float m_riseFactor;
};
