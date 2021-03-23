#ifndef CUTSCENE
#define CUTSCENE

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Game.h"

class Game;

class Cutscene
{
public:
	Cutscene(Game & t_game);
	~Cutscene();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);
private:
	sf::Font m_font;
	Game &m_game;
};

#endif //!CUTSCENE