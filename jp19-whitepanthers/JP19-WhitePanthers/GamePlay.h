#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "SFML/Graphics.hpp"
#include "Rhombus.h"
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "AiCar.h"
#include "Hud.h"

class Game;

class GamePlay
{
public:
	GamePlay(Game & t_game,sf::Sound &t_downsiftSound, sf::Sound &t_accelerateSound, sf::Sound &t_brakeSound, sf::Music&t_gameplayMusic, sf::Music&t_bgMusic);
	~GamePlay();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);

	void setupSprites();
	void setupSquares();
	void resetGame();


	void gatePosition();

	Player m_player;
private:

	AiCar m_aiCar1;
	AiCar m_aiCar2;
	AiCar m_aiCar3;

	Hud m_hud;

	Game &m_game;  	
	sf::Font &m_font;

	sf::Text m_text;

	sf::Music &m_bgMusic;
	sf::Music &m_gameplayMusic;
	sf::Sound &m_downshiftSound;
	sf::Sound &m_accelerateSound;
	sf::Sound &m_brakeSound;

	sf::Sprite m_bg;
	sf::Texture &m_bgTexture;
	
	static const int s_MAX_SQUARES = 10;

	unsigned m_currentPos;

	sf::RectangleShape m_rectangleDest[s_MAX_SQUARES];

	bool m_move{ false };

	bool m_raceWon{ false };
	static const int s_MAX_PAUSE_TEXT = 3;
	Label m_pauseText[s_MAX_PAUSE_TEXT];
	sf::RectangleShape m_pauseBackground;
	
	bool m_pause{ false };

	sf::Time m_timer{ sf::Time::Zero };
};
#endif //!GAMEPLAY