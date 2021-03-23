#include "Controls.h"

Controls::Controls(Game & t_game, sf::Sound &t_backSound, sf::Sound &t_selectSound, sf::Sound &t_moveSound) :
	m_game(t_game),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_neonFont]),
	m_title(t_game.m_levelData, 60, "CONTROLS", sf::Vector2f{ 800.0f,100.0f }, false),
	m_animationMode{ AnimationMode::Appear },
	m_currentButton{ 0 },
	m_inputTimer{ 10 },
	m_options{
	SelectBox(t_game.m_levelData,40,sf::Vector2f{ 30.0f, 30.0f },"GAMEPLAY",false,sf::Vector2f{ 500.0f,300.0f},sf::Color::Cyan,false,false),
	SelectBox(t_game.m_levelData,40,sf::Vector2f{ 30.0f, 30.0f },"MAIN MENU",false,sf::Vector2f{ 500.0f,400.0f },sf::Color::Cyan,false,false),
	SelectBox(t_game.m_levelData,40,sf::Vector2f{ 30.0f, 30.0f },"TRACK SELECTION",false,sf::Vector2f{ 500.0f,500.0f },sf::Color::Cyan,false,false),
	SelectBox(t_game.m_levelData,40,sf::Vector2f{ 30.0f, 30.0f },"LEADERBOARD",false,sf::Vector2f{ 500.0f,600.0f },sf::Color::Cyan,false,false),
	SelectBox(t_game.m_levelData,40,sf::Vector2f{ 30.0f, 30.0f },"STORE",false,sf::Vector2f{ 500.0f,700.0f },sf::Color::Cyan,false,false) },
	m_backSound( t_backSound ),
	m_selectSound(t_selectSound),
	m_moveSound(t_moveSound),
	m_bgTex(ResourceManager::m_textureHolder[m_game.m_levelData.m_myTextures.m_bGID]),
	m_controllerTex(ResourceManager::m_textureHolder[m_game.m_levelData.m_myTextures.m_controlsControllerID])
{
	setupSprites();
	setupText();
}

Controls::~Controls()
{
}

void Controls::update(sf::Time t_deltaTime)
{
	if (m_animationMode == AnimationMode::Appear)
	{
		for (int i = 0; i < s_MAX_OPTIONS; i++)
		{
			m_options[i].makeCheckboxOpaque(7, 2);
			m_options[i].makeOpaque(7, 2);
			m_overlays[i].setColor(m_overlays[i].getColor() + sf::Color{ 0,0,0,15 });
		}

		m_controller.setColor(m_controller.getColor() + sf::Color{ 0,0,0,15 });

		if (m_title.makeOpaque(7, 2))
		{
			m_animationMode = AnimationMode::Always;
		}

	}
	else if (m_animationMode == AnimationMode::Always)
	{
		checkInput();
		highlightButton();
		if (m_game.m_controller.m_currentState.B && m_inputTimer < 0)
		{
			if (s_audioActive && s_sfxActive)
			{
				m_backSound.play();
			}
			m_animationMode = AnimationMode::Disappear;
		}
	}
	else if (m_animationMode == AnimationMode::Disappear)
	{
		for (int i = 0; i < s_MAX_OPTIONS; i++)
		{
			m_options[i].makeCheckboxTransparent(7, 2);
			m_options[i].makeTransparent(7, 2);
			m_overlays[i].setColor(m_overlays[i].getColor() - sf::Color{ 0,0,0,15 });
		}

		m_controller.setColor(m_controller.getColor() - sf::Color{ 0,0,0,15 });

		if (m_title.makeTransparent(7, 2))
		{
			m_animationMode = AnimationMode::Appear;
			m_game.m_currentMode = GameMode::MainMenu;
		}
	}
}

void Controls::render(sf::RenderWindow & t_window)
{
	t_window.clear();
	t_window.draw(m_background);
	m_title.render(t_window);
	t_window.draw(m_controller);
	for (int i = 0; i < s_MAX_OPTIONS; i++)
	{
		m_options[i].draw(t_window);
	}
	renderControllerOverlay(t_window);
	t_window.display();
}

void Controls::setupSprites()
{
	m_background.setTexture(m_bgTex);
	
	m_controller.setTexture(m_controllerTex);
	m_controller.setScale(sf::Vector2f{ 2.0f,2.0f });
	m_controller.setPosition(sf::Vector2f{ 600.0f,200.0f });
	m_controller.setColor(m_controller.getColor() - sf::Color{ 0,0,0,255 });

	setupOverlays();
}

void Controls::setupText()
{
	m_title.setColour(sf::Color{ 0, 255, 255, 0 });
	m_title.changeTextProperties(true, false, false);

	for (int i = 0; i < s_MAX_OPTIONS; i++)
	{
		m_options[i].setColour(sf::Color{ 255, 255, 0, 0 });
		m_options[i].changeTextProperties(true, false, false);
	}
}

void Controls::highlightButton()
{
	for (int i = 0; i < s_MAX_OPTIONS; i++)
	{
		if (i != m_currentButton)
		{
			m_options[i].setHighlighted(false);
		}
		else
		{
			m_options[i].setHighlighted(true);
		}
	}

}

void Controls::checkInput()
{
	m_inputTimer--;

	if (m_game.m_controller.m_currentState.DpadDown && m_inputTimer < 0 || 
		m_game.m_controller.m_currentState.LeftThumbStick.y > 50 && m_inputTimer < 0)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_inputTimer = 10;
		if (m_currentButton == s_MAX_OPTIONS - 1)
		{
			m_currentButton = 0;
		}
		else
		{
			m_currentButton++;
		}
	}

	if (m_game.m_controller.m_currentState.DpadUp && m_inputTimer < 0 ||
		m_game.m_controller.m_currentState.LeftThumbStick.y < -50 && m_inputTimer < 0)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_inputTimer = 10;
		if (m_currentButton == 0)
		{
			m_currentButton = s_MAX_OPTIONS - 1;
		}
		else
		{
			m_currentButton--;
		}
	}

	if (m_game.m_controller.m_currentState.A && m_inputTimer < 0)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_selectSound.play();
		}
		m_inputTimer = 10;
		for (int i = 0; i < s_MAX_OPTIONS; i++)
		{
			m_options[i].setActive(false);
		}
		m_options[m_currentButton].setActive(true);
	}
}

void Controls::setupOverlays()
{
	m_overlaysTex[0] = ResourceManager::m_textureHolder[m_game.m_levelData.m_myTextures.m_controlsOGameID];
	m_overlaysTex[1] = ResourceManager::m_textureHolder[m_game.m_levelData.m_myTextures.m_controlsOMainID];
	m_overlaysTex[2] = ResourceManager::m_textureHolder[m_game.m_levelData.m_myTextures.m_controlsOTrackID];
	m_overlaysTex[3] = ResourceManager::m_textureHolder[m_game.m_levelData.m_myTextures.m_controlsOLeaderID];
	m_overlaysTex[4] = ResourceManager::m_textureHolder[m_game.m_levelData.m_myTextures.m_controlsOStoreID];
	for (int i = 0; i < s_MAX_OPTIONS; i++)
	{
		m_overlays[i].setPosition(m_controller.getPosition());
		m_overlays[i].setTexture(m_overlaysTex[i]);
		m_overlays[i].setScale(sf::Vector2f{ 2.0f,2.0f });
	}
}

void Controls::renderControllerOverlay(sf::RenderWindow & t_window)
{
	for (int i = 0; i < s_MAX_OPTIONS; i++)
	{
		if (m_options[i].getActive())
		{
			t_window.draw(m_overlays[i]);
		}
	}
}
