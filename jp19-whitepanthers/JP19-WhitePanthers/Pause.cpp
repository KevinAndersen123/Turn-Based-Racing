#include "Pause.h"

Pause::Pause(Game & t_game) :
	m_game(t_game),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_neonFont]),
	m_title(m_game.m_levelData,80,"PAUSE",sf::Vector2f(ScreenSize::s_WIDTH / 2, 50.0f),false),
	m_currentOption(0),
	m_inputTimer(10),
	m_animationMode(AnimationMode::Appear),
	m_options{
	TextButtons(m_game.m_levelData,sf::Vector2f(ScreenSize::s_WIDTH / 2, 400.0),false,50,"RESUME"),
	TextButtons(m_game.m_levelData,sf::Vector2f(ScreenSize::s_WIDTH / 2, 500.0),false,50,"MAIN MENU")},
	m_backgroundTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_bGTwoID])
{
	setupSprites();
}

Pause::~Pause()
{
}

void Pause::update(sf::Time t_deltaTime)
{
	m_cumalativeTime += t_deltaTime;
	if (m_animationMode == AnimationMode::Appear)
	{
		for (int i = 0; i < s_MAX_OPTIONS; i++)
		{
			m_options[i].makeOpaque(7, 2);
		}
		m_title.makeOpaque(7, 2);
		if (m_cumalativeTime.asSeconds() > 2 )
		{
			m_animationMode = AnimationMode::None;
		}
	}
	if (m_animationMode == AnimationMode::None)
	{
		checkInput();
		for (int i = 0; i < s_MAX_OPTIONS; i++)
		{
			m_options[i].makeTextGlow();
		}
	}
	if (m_animationMode == AnimationMode::Disappear)
	{
		for (int i = 0; i < s_MAX_OPTIONS; i++)
		{
			m_options[i].makeTransparent(7, 2);
		}
		m_title.makeTransparent(7, 2);
		if (m_cumalativeTime.asSeconds() > 2)
		{
			switch (m_currentOption)
			{
			case 0:
				m_game.m_currentMode = GameMode::GamePlay;
				m_animationMode = AnimationMode::Appear;
				m_cumalativeTime = sf::Time::Zero;
				break;
			case 1:
				m_game.m_currentMode = GameMode::MainMenu;
				m_animationMode = AnimationMode::Appear;
				m_cumalativeTime = sf::Time::Zero;
				break;
			default:
				break;
			}
		}
	}
}

void Pause::render(sf::RenderWindow & t_window)
{
	t_window.clear();

	t_window.draw(m_background);
	t_window.draw(m_bgSquare);
	for (int i = 0; i < s_MAX_OPTIONS; i++)
	{
		m_options[i].draw(t_window);
	}
	m_title.render(t_window);

	t_window.display();
}

void Pause::setupSprites()
{
	m_background.setTexture(m_backgroundTex);

	m_title.setColour(sf::Color{ 0, 255, 255 ,0});
	m_title.changeTextProperties(true, false, false);

	m_bgSquare.setSize(sf::Vector2f{ 600.0f,700.0f });
	m_bgSquare.setPosition(sf::Vector2f{ 510.0f,150.0f });
	m_bgSquare.setFillColor(sf::Color{ 153, 153, 153, 150 });

	for (int i = 0; i < s_MAX_OPTIONS; i++)
	{
		m_options[i].changeTextProperties(true, false, false);
		m_options[i].setColour(sf::Color{ 255, 0, 255,0 });
		m_options[i].setOutlineColour(sf::Color{ 0, 255, 255 ,0});
	}
	m_options[m_currentOption].setHighlighted(true);

}

void Pause::checkInput()
{
	m_inputTimer--;
	if ((m_game.m_controller.m_currentState.DpadDown || m_game.m_controller.m_currentState.LeftThumbStick.y < -50)
		&& m_inputTimer < 0)
	{
		m_inputTimer = 10;
		m_options[m_currentOption].setHighlighted(false);
		m_currentOption++;
		if (m_currentOption > s_MAX_OPTIONS - 1)
		{
			m_currentOption = 0;
		}
		m_options[m_currentOption].setHighlighted(true);
	}

	if ((m_game.m_controller.m_currentState.DpadUp || m_game.m_controller.m_currentState.LeftThumbStick.y > 50)
		&& m_inputTimer < 0)
	{
		m_inputTimer = 10;
		m_options[m_currentOption].setHighlighted(false);
		m_currentOption--;
		if (m_currentOption < 0)
		{
			m_currentOption = s_MAX_OPTIONS - 1;
		}
		m_options[m_currentOption].setHighlighted(true);
	}

	if (m_game.m_controller.m_currentState.A && m_inputTimer < 0)
	{
		m_inputTimer = 10;
		m_animationMode = AnimationMode::Disappear;
		m_cumalativeTime = sf::Time::Zero;
	}
}
