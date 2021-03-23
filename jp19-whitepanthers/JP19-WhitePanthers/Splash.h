#ifndef SPLASH
#define SPLASH

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "Game.h"
#include "Globals.h"
#include "Label.h"

class Game;

class Splash
{
public:
	Splash(Game & t_game, sf::Sound &t_selectSound);
	~Splash();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);
private:
	sf::Text m_text;

	Label m_text2;

	sf::Sprite m_bgSprite;
	sf::Texture &m_bgText;

	sf::Sound &m_selectSound;

	sf::Font& m_font;
	Game &m_game;

	AnimationMode m_animationState{ AnimationMode::Appear };
	void loadAssets();
};
#endif //!SPLASH