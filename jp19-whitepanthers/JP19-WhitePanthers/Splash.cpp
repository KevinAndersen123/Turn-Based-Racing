#include "Splash.h"

Splash::Splash(Game & t_game, sf::Sound &t_selectSound) :
	m_game(t_game),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_neonFont]),
	m_text2(t_game.m_levelData, 50, " Press A to Continue", sf::Vector2f(1100, 850.0f)),
	m_selectSound(t_selectSound),
	m_bgText(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_bGSixID])
{
	loadAssets();
}

Splash::~Splash()
{
}

void Splash::update(sf::Time t_deltaTime)
{
	if (m_animationState == AnimationMode::Appear)
	{
		if (m_bgSprite.getColor().a < 255)
		{
			m_bgSprite.setColor(m_bgSprite.getColor() + sf::Color{ 0,0,0,10 });
		}
		else
		{
			m_animationState = AnimationMode::None;
		}
	}

	if (m_game.m_controller.m_currentState.A && m_animationState == AnimationMode::None)
	{
		m_selectSound.play();
		m_animationState = AnimationMode::Disappear;
	}

	if (m_animationState == AnimationMode::Disappear)
	{
		if (m_bgSprite.getColor().a > 0)
		{
			m_bgSprite.setColor(m_bgSprite.getColor() - sf::Color{ 0,0,0,10 });
		}
	}
	if (m_bgSprite.getColor().a <= 0)
	{
		m_game.m_currentMode = GameMode::MainMenu;
	}
}

void Splash::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color::Black);

	t_window.draw(m_bgSprite);
	m_text2.render(t_window);

	t_window.display();

}

void Splash::loadAssets()
{
	m_text2.setColour(sf::Color{ 102, 255, 255, 255 });
	m_bgSprite.setTexture(m_bgText);
	m_bgSprite.setColor(m_bgSprite.getColor() - sf::Color{ 0,0,0,255 });
}
