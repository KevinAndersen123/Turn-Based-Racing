#include "Cutscene.h"

Cutscene::Cutscene(Game & t_game) :
	m_game(t_game)
{
}

Cutscene::~Cutscene()
{
}

void Cutscene::update(sf::Time t_deltaTime)
{
}

void Cutscene::render(sf::RenderWindow & t_window)
{
	t_window.clear();

	t_window.display();
}
