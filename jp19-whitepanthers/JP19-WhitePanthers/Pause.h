#ifndef PAUSE
#define PAUSE

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Game.h"
#include "TextButtons.h"

class Game;

class Pause
{
public:
	Pause(Game & t_game);
	~Pause();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);
private:
	sf::Font &m_font;
	Game &m_game;

	sf::Time m_cumalativeTime;

	sf::Sprite m_background;
	sf::Texture &m_backgroundTex;

	Label m_title;

	static const int s_MAX_OPTIONS = 2;
	TextButtons m_options[s_MAX_OPTIONS];
	int m_currentOption;

	int m_inputTimer;

	sf::RectangleShape m_bgSquare;

	AnimationMode m_animationMode;

	void setupSprites();
	void checkInput();
};

#endif //!PAUSE