#ifndef LICENCE
#define LICENCE

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "Game.h"
#include "Label.h"
class Game;

class Licence
{
public:
	Licence(Game & t_game,sf::Music &t_bgMusic);
	~Licence();
	
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);
private:
	sf::Font& m_font;
	Game &m_game;

	sf::Sprite m_logo;
	sf::Texture &m_logoTex;
	sf::Sprite m_background;
	sf::Texture &m_backgroundTex;

	sf::Sound m_lightBuzz;
	sf::SoundBuffer &m_buzzBuffer;

	Label m_text;

	AnimationMode m_animationMode{ AnimationMode::Appear };
	sf::Time m_cumulativeTime;
	sf::Music &m_bgMusic;
	void setupText();
	void setupSprite();
};

#endif //!LICENCE