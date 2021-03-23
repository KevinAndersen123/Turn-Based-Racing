#ifndef CONTROLS
#define CONTROLS

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Game.h"
#include "Label.h"
#include "SelectBox.h"

class Game;

class Controls
{
public:
	Controls(Game & t_game, sf::Sound &t_backSound,sf::Sound &t_selectSound, sf::Sound &t_moveSound);
	~Controls();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);
private:
	sf::Font &m_font;
	Game &m_game;

	AnimationMode m_animationMode;

	sf::Sprite m_background;
	sf::Texture &m_bgTex;

	sf::Sprite m_controller;
	sf::Texture &m_controllerTex;

	Label m_title;

	static const int s_MAX_OPTIONS = 5;
	SelectBox m_options[s_MAX_OPTIONS];

	sf::Sprite m_overlays[s_MAX_OPTIONS];
	sf::Texture m_overlaysTex[s_MAX_OPTIONS];

	int m_currentButton;
	int m_inputTimer;

	sf::Sound &m_backSound;
	sf::Sound &m_selectSound;
	sf::Sound &m_moveSound;
	/*sf::SoundBuffer &m_backSoundBuff;
	sf::SoundBuffer &m_selectSoundBuff;
	sf::SoundBuffer &m_moveSoundBuff;*/

	void setupSprites();
	void setupText();
	void highlightButton();
	void checkInput();
	void setupOverlays();
	void renderControllerOverlay(sf::RenderWindow &t_window);
};

#endif //!CONTROLS