#ifndef HIGHSCORE
#define HIGHSCORE

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

class Game;

class Highscore
{
public:
	Highscore(Game & t_game,sf::Sound &t_backSound);
	~Highscore();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);
private:
	sf::Text m_headingText;

	sf::Font& m_font;
	Game &m_game;
	std::vector<sf::Text>m_scoreText;

	sf::Sprite m_heading;
	sf::Texture &m_headingTex;

	sf::Sprite m_main;
	sf::Texture &m_mainTex;

	sf::Sprite m_backButton;
	sf::Texture &m_backButtonTex;

	sf::Sprite m_background;
	sf::Texture &m_backgroundTex;

	int m_moveTimer;
	sf::Vector2f m_speed;

	sf::Sound &m_backSound;

	void moveBackButton();
	void loadText();
	void setupSprites();
};

#include "Game.h"
#endif //!HIGHSCORE