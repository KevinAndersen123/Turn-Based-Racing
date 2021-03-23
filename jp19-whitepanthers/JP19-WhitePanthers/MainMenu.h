#ifndef MAINMENU
#define MAINMENU

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Game.h"
#include "TextButtons.h"

class Game;


class MainMenu
{
public:
	MainMenu(Game & t_game,sf::Sound & t_moveSound, sf::Sound & t_selectSound);
	~MainMenu();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);

	void setupText();
private:

	enum class ButtonName
	{
		Play,
		Controls,
		Shop,
		Garage,
		Settings,
		Highscore,
		Quit
	};

	sf::Font &m_font;
	Game &m_game;
	sf::Sound & m_moveSound;
	sf::Sound & m_selectSound;
	static const int s_MAX_BUTTONS = 7;
	TextButtons m_MenuOptions[s_MAX_BUTTONS];
	ButtonName m_currentButton;
	int m_inputTimer;

	sf::Sprite m_bgLeft;
	sf::Texture &m_bgLeftTex;

	sf::Sprite m_carSprite1;
	sf::Texture &m_carTex1;

	sf::Sprite m_carSprite2;
	sf::Texture &m_carTex2;

	sf::Sprite m_background;
	sf::Texture &m_backgroundTex;

	sf::Sprite m_heading;
	sf::Texture &m_headingTex;

	sf::Sprite m_bgBottom;
	sf::Texture &m_bgBottomTex;

	AnimationMode m_animationMode{ AnimationMode::Appear };
	sf::Time m_cumalativeTime;

	void setupSprites();
	void checkInput();
	void checkButtonSelect();
	void animateScreen();
};

#endif //!MAINMENU