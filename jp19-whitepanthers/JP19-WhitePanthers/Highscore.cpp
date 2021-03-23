#include "Highscore.h"

Highscore::Highscore(Game & t_game,sf::Sound & t_backsound) :
	m_game(t_game),
	m_moveTimer(60),
	m_speed( 15.0f,0.0f ),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_neonFont]),
	m_backSound(t_backsound),
	m_headingTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_highscoreHeadingID]),
	m_mainTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_highscoreMainID]),
	m_backButtonTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_highscoreBackID]),
	m_backgroundTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_bGFourID])
{
	loadText();
	setupSprites();
}

Highscore::~Highscore()
{
}

void Highscore::update(sf::Time t_deltaTime)
{
	if (m_game.m_controller.m_currentState.B)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_backSound.play();
		}
		m_game.m_currentMode = GameMode::MainMenu;
	}
	moveBackButton();
}

void Highscore::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color::Black);

	t_window.draw(m_background);
	t_window.draw(m_heading);
	t_window.draw(m_main);
	t_window.draw(m_headingText);
	for (int i = 0; i < m_scoreText.size(); i++)
	{
		t_window.draw(m_scoreText[i]);
	}
	t_window.draw(m_backButton);
	t_window.display();
}

void Highscore::moveBackButton()
{
	m_moveTimer--;
	if (m_moveTimer <= 0)
	{
		m_speed.x = m_speed.x * -1;
		m_backButton.move(m_speed);
		m_moveTimer = 60;
	}
}

void Highscore::loadText()
{
	m_headingText.setFont(m_font);
	m_headingText.setString("HighScores");
	m_headingText.setCharacterSize(100);
	m_headingText.setFillColor(sf::Color{ 102, 255, 255 });
	m_headingText.setPosition(sf::Vector2f(600.0f, 10.0f));

	for (int i = 0; i < m_game.m_levelData.m_scores.size(); i++)
	{
		if (i < 20)
		{
			sf::Text text;
			text.setString(m_game.m_levelData.m_scores[i].m_name + " : " + std::to_string(static_cast<int>(m_game.m_levelData.m_scores[i].m_time)));
			text.setFillColor(sf::Color{ 255, 153, 255 });
			text.setFont(m_font);
			text.setCharacterSize(50);
			if (i < 10)
			{
				text.setPosition(sf::Vector2f{ 400.0f, 250.0f + (50.0f * i) });
			}
			else
			{
				text.setPosition(sf::Vector2f{ 1000.0f, 250.0f + (50.0f * (i - 10)) });
			}

			m_scoreText.push_back(text);
		}
	}
}

void Highscore::setupSprites()
{
	m_heading.setTexture(m_headingTex);
	m_heading.setPosition(sf::Vector2f{70.0f,20.0f});

	m_main.setTexture(m_mainTex);
	m_main.setPosition(sf::Vector2f{ 170.0f,200.0f });

	m_backButtonTex.setSmooth(true);
	m_backButton.setTexture(m_backButtonTex);
	m_backButton.setPosition(sf::Vector2f{100.0f,800.0f});
	m_backButton.setOrigin(sf::Vector2f{ m_backButton.getGlobalBounds().width / 2, m_backButton.getGlobalBounds().height / 2 });

	m_background.setTexture(m_backgroundTex);
	m_background.setPosition(sf::Vector2f{ 0.0f,0.0f });
}
