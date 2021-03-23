#include "Credits.h"

Credits::Credits(Game & t_game) :
	m_game(t_game)
{
}

Credits::~Credits()
{
}

void Credits::update(sf::Time t_deltaTime)
{
}

void Credits::render(sf::RenderWindow & t_window)
{
	t_window.clear();

	t_window.display();
}
