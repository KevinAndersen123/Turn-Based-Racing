#include "Licence.h"

Licence::Licence(Game & t_game,sf::Music &t_bgMusic) :
	m_game(t_game),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_arialBlackFont]),
	m_cumulativeTime{ sf::Time::Zero },
	m_text(Label(t_game.m_levelData, 90, "Made with SFML", sf::Vector2f{ 800.0f,700.0f }, false )),
	m_bgMusic(t_bgMusic),
	m_backgroundTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_bGID]),
	m_logoTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_sfmlID]),
	m_buzzBuffer(ResourceManager::m_soundHolder[t_game.m_levelData.m_mySounds.m_lightBuzzID])
{
	setupSprite();
	setupText();
	m_lightBuzz.play();
}

Licence::~Licence()
{
}

void Licence::update(sf::Time t_deltaTime)
{
	m_cumulativeTime += t_deltaTime;
	if (m_animationMode == AnimationMode::Appear)
	{
		if (m_cumulativeTime < sf::seconds(2))
		{
			if ((m_cumulativeTime < sf::seconds(0.3)) ||
				(m_cumulativeTime < sf::seconds(0.9) && m_cumulativeTime > sf::seconds(0.6)) ||
				(m_cumulativeTime < sf::seconds(1.5) && m_cumulativeTime > sf::seconds(1.2)))
			{
				m_logo.setColor(m_logo.getColor() - sf::Color{ 0,0,0,50 });
			}
			else
			{
				m_logo.setColor(m_logo.getColor() + sf::Color{ 0,0,0,50 });
			}
		}
		else
		{
			if (m_text.getColour().a < 255)
			{
				m_text.setColour(m_text.getColour() + sf::Color{ 0,0,0,10 });
			}
			else
			{
				m_cumulativeTime = sf::Time::Zero;
				m_animationMode = AnimationMode::None;
			}
		}
	}
	if (m_animationMode == AnimationMode::None)
	{
		if (m_cumulativeTime > sf::seconds(2))
		{
			m_animationMode = AnimationMode::Disappear;
		}
	}
	if (m_animationMode == AnimationMode::Disappear)
	{
		if (m_logo.getColor().a > 0)
		{
			m_logo.setColor(m_logo.getColor() - sf::Color{ 0,0,0,10 });
		}
		else if(m_text.getColour().a > 0)
		{
			m_text.setColour(m_text.getColour() - sf::Color{ 0,0,0,10 });
		}
		else
		{
			m_lightBuzz.stop();
			m_bgMusic.play();
			m_game.m_currentMode = GameMode::splash;
		}
	}
}

void Licence::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color::Black);

	t_window.draw(m_background);
	t_window.draw(m_logo);
	m_text.render(t_window);

	t_window.display();
}

void Licence::setupText()
{
	m_text.setColour(sf::Color{ 102, 255, 255, 0 });
	m_text.changeTextProperties(true, false, false);
}

void Licence::setupSprite()
{
	m_logo.setTexture(m_logoTex);
	m_logo.setPosition(sf::Vector2f{ 600.0f,150.0f });
	m_logo.setColor(m_logo.getColor() - sf::Color{ 0,0,0,255 });

	m_background.setTexture(m_backgroundTex);
	m_background.setPosition(sf::Vector2f{ 0.0f,0.0f });

	m_lightBuzz.setBuffer(m_buzzBuffer);
	m_lightBuzz.setVolume(100);
	m_lightBuzz.setPlayingOffset(sf::seconds(0.5));
}
