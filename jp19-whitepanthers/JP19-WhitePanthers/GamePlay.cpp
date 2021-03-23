#include "GamePlay.h"

GamePlay::GamePlay(Game & t_game, sf::Sound &t_downsiftSound, sf::Sound &t_accelerateSound, sf::Sound &t_brakeSound, sf::Music&t_gameplayMusic, sf::Music&t_bgMusic) :
	m_game(t_game),
	m_hud(t_game.m_controller,t_game.m_levelData),
	m_player(t_game.m_levelData, t_game.m_controller, m_hud.m_rhombus,0,t_downsiftSound,t_accelerateSound,t_brakeSound),
	m_aiCar1(t_game.m_levelData, 1),
	m_aiCar2(t_game.m_levelData, 2),
	m_aiCar3(t_game.m_levelData, 3),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_neonFont]),
	m_gameplayMusic(t_gameplayMusic),
	m_bgMusic(t_bgMusic),
	m_downshiftSound(t_downsiftSound),
	m_accelerateSound(t_accelerateSound),
	m_brakeSound(t_brakeSound),
	m_currentPos(0),
	m_pauseText{
	Label(m_game.m_levelData, 70, "PAUSED", sf::Vector2f{ ScreenSize::s_WIDTH / 2, 100.0f }, false),
	Label(m_game.m_levelData, 40, "PRESS Y TO GO TO TRACK SELECT", sf::Vector2f{ ScreenSize::s_WIDTH / 2, 400.0f }, false),
	Label(m_game.m_levelData, 40, "PRESS B TO RETURN TO RACE", sf::Vector2f{ ScreenSize::s_WIDTH / 2, 600.0f }, false)},
	m_bgTexture(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_bGThreeID])
{
	setupSprites();
	setupSquares();
	m_hud.setView(m_player.getPosition());

	m_text.setFillColor(sf::Color{ 255,255,255,255 });
	m_text.setFont(m_font);
	m_text.setCharacterSize(100);
	
}

GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time t_deltaTime)
{
	if (!m_pause)
	{
		if (m_raceWon == false)
		{
			m_hud.updateTimer(t_deltaTime);

			if (m_move == false)
			{
				m_player.updatePath();
				m_hud.update(t_deltaTime);

				if (m_game.m_controller.m_currentState.A)
				{
					m_move = true;
					m_timer = sf::Time::Zero;
				}
			}
			else
			{
				m_player.update(t_deltaTime, m_hud.m_rhombus);
				m_player.clearPath();

				m_hud.setViewCentre(m_player.getPosition());
				m_aiCar1.update(t_deltaTime);
				m_aiCar2.update(t_deltaTime);
				m_aiCar3.update(t_deltaTime);
			}

			if (m_move == true)
			{
				m_timer += t_deltaTime;
			}
			if (m_timer.asSeconds() > 3)
			{
				m_move = false;
				m_timer = sf::Time::Zero;

				m_hud.setView(m_player.getPosition());
			}
			gatePosition();
			if (m_game.m_controller.m_currentState.Start)
			{
				m_pause = true;
				m_pauseText[0].setPosition(m_hud.getView().getCenter() - sf::Vector2f{ 0.0f,300.0f });
				m_pauseText[1].setPosition(m_hud.getView().getCenter());
				m_pauseText[2].setPosition(m_hud.getView().getCenter() + sf::Vector2f{ 0.0f,100.0f });
				m_pauseBackground.setPosition(m_hud.getView().getCenter());
				m_accelerateSound.stop();
				m_downshiftSound.stop();
				m_brakeSound.stop();
			}
		}
	}
	else
	{
		if (m_game.m_controller.m_currentState.Y)
		{
			if (s_audioActive && s_musicActive)
			{
				m_gameplayMusic.stop();
				m_bgMusic.play();
			}
			m_pause = false;
			m_game.m_currentMode = GameMode::TrackSelection;
		}
		if (m_game.m_controller.m_currentState.B)
		{
			m_pause = false;
		}
	}

	if (m_raceWon == true)
	{
		if (m_game.m_controller.m_currentState.A == true)
		{
			if (s_audioActive && s_musicActive)
			{
				m_gameplayMusic.stop();
				m_bgMusic.play();
			}

			m_game.m_currentMode = GameMode::TrackSelection;
		}
	}
}

void GamePlay::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color::Black);
	t_window.setView(m_hud.getView());
	t_window.draw(m_bg);

	if (m_move == false)
	{
		m_player.drawPlayerPath(t_window);
	}
	m_player.render(t_window);
	m_aiCar1.render(t_window);
	m_aiCar2.render(t_window);
	m_aiCar3.render(t_window);
	
	if (m_raceWon == true)
	{
		t_window.draw(m_text);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		for (int i = 0; i < s_MAX_SQUARES; i++)
		{
			t_window.draw(m_rectangleDest[i]);
		}
	}

	if (m_move == false)
	{
		m_hud.render(t_window);
	}

	if (m_pause)
	{
		t_window.draw(m_pauseBackground);
		for (int i = 0; i < s_MAX_PAUSE_TEXT; i++)
		{
			m_pauseText[i].render(t_window);
		}
	}

	t_window.display();
}

void GamePlay::setupSprites()
{
	m_bg.setTexture(m_bgTexture);
	m_bg.setScale(1.5, 1.5);

	m_pauseText[0].setColour(sf::Color::Cyan);

	m_pauseBackground.setSize(sf::Vector2f{ 800.0f,800.0f });
	m_pauseBackground.setFillColor(sf::Color{ 128, 128, 128 , 200 });
	m_pauseBackground.setOrigin(m_pauseBackground.getGlobalBounds().width / 2, m_pauseBackground.getGlobalBounds().height / 2);
}

void GamePlay::resetGame()
{
	m_player.resetPlayer();
	m_aiCar1.resetCar();
	m_aiCar2.resetCar();
	m_aiCar3.resetCar();

	m_hud.setView(m_player.getPosition());
	m_hud.reset();
	m_move = false;
	m_raceWon = false;
}

void GamePlay::gatePosition()
{
	for (int i = 0; i < s_MAX_SQUARES; i++)
	{
		if (m_player.getSprite().getGlobalBounds().intersects(m_rectangleDest[i].getGlobalBounds()))
		{
			if ((i - 1) == m_currentPos)
			{
				m_currentPos = i;
			}
			else if (m_currentPos == (s_MAX_SQUARES - 1) && i == 0)
			{
				m_currentPos = i;
				m_hud.increaseLaps();
			}
		}
	}

	if (m_hud.getLap() > 2)
	{
		m_raceWon = true;
		m_game.m_currency += 300;
		m_text.setPosition(m_hud.getView().getCenter()+sf::Vector2f(-300.0f,200.0f));
		m_text.setString(" Your Time : " + std::to_string( m_hud.getTimer()) + "\n Press A to continue" );
	}
}

void GamePlay::setupSquares()
{
	for (int i = 0; i < s_MAX_SQUARES; i++)
	{
		m_rectangleDest[i].setSize(sf::Vector2f(500, 450));
		m_rectangleDest[i].setFillColor(sf::Color::Red);
	}

	m_rectangleDest[0].setPosition(3500, 500);
	m_rectangleDest[1].setPosition(4000, 500);
	m_rectangleDest[2].setPosition(5000, 500);
	m_rectangleDest[3].setPosition(5000, 1100);
	m_rectangleDest[4].setPosition(5000, 2200);
	m_rectangleDest[5].setPosition(3700, 1300);
	m_rectangleDest[6].setPosition(3000, 2200);
	m_rectangleDest[7].setPosition(2000, 2275);
	m_rectangleDest[8].setPosition(1000, 2200);
	m_rectangleDest[9].setPosition(1000, 500);
}
