#ifndef CREDITS
#define CREDITS

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Game.h"

class Game;

class Credits
{
public:
	Credits(Game & t_game);
	~Credits();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);
private:
	Game &m_game;
};

#endif //!CREDITS
