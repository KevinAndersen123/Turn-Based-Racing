#include "TrackSelection.h"


TrackSelection::TrackSelection(Game & t_game, std::shared_ptr<GamePlay> t_gameplay, sf::Music &t_bgMusic, sf::Music &t_gameplayMusic,sf::Sound 
	&t_backSound, sf::Sound&t_moveSound, sf::Sound&t_selectSound) :
	m_game(t_game),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_neonFont]),
	currentTrack(1),
	m_bgMusic{t_bgMusic},
	m_gameplayMusic{t_gameplayMusic},
	m_gameplay(t_gameplay),
	m_backSound(t_backSound),
	m_selectSound(t_selectSound),
	m_moveSound(t_moveSound),
	m_trackText1(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_bGThreeID]),
	m_bgText(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_bGTwoID])
{
	loadAssets();
}

TrackSelection::~TrackSelection()
{
}

void TrackSelection::update(sf::Time t_deltaTime)
{
	m_inputTimer--;
	if (m_game.m_controller.m_currentState.B)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_backSound.play();
		}
		m_game.m_currentMode = GameMode::MainMenu;
	}

	if (m_game.m_controller.m_currentState.A)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_selectSound.play();
		}
		m_bgMusic.stop();
		if (s_audioActive && s_musicActive)
		{
			m_gameplayMusic.play();
		}
		resetGame();
		m_game.m_currentMode = GameMode::GamePlay;
	}

	if (m_game.m_controller.m_currentState.LeftThumbStick.x > 50 && m_inputTimer < 0 ||
		m_game.m_controller.m_currentState.DpadRight && m_inputTimer < 0)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_inputTimer = 10;
		currentTrack = (currentTrack + 1) % 3;
	}
	else if (m_game.m_controller.m_currentState.LeftThumbStick.x < -50 && m_inputTimer < 0 ||
		m_game.m_controller.m_currentState.DpadLeft && m_inputTimer < 0)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_inputTimer = 10;
		currentTrack = currentTrack == 0 ? (3-1) : currentTrack - 1;
	}
	m_selection.setPosition(sf::Vector2f(400 * (currentTrack+1), 100));
}

void TrackSelection::render(sf::RenderWindow & t_window)
{
	t_window.setView(t_window.getDefaultView());
	t_window.clear(sf::Color::Black);

	t_window.draw(m_bgSprite);
	
	for (auto & tabs : m_trackTab)
	{
		tabs->render(t_window);
	}

	for (int i = 0; i < 3; i++)
	{
		m_track.setPosition(sf::Vector2f(400 * (i + 1), 500));
		t_window.draw(m_track);
	}

	t_window.draw(m_selection);

	t_window.display();
}

void TrackSelection::loadAssets()
{
	m_text.setFont(m_font);
	m_text.setString("track selection : Press a to go to gameplay \n b to go to main menu");
	m_text.setCharacterSize(30);
	m_text.setPosition(sf::Vector2f(300.0f, 300.0f));

	m_bgSprite.setTexture(m_bgText);
	
	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<UpgradesTab> temp = std::make_shared<UpgradesTab>(m_game,30, ("Track: " + std::to_string(i + 1)), sf::Vector2f(400 * (i + 1), 500), false);

		m_trackTab.push_back(temp);
	}
	m_track.setTexture(&m_trackText1);
	m_track.setSize(sf::Vector2f(300,250));
	m_track.setOrigin(m_track.getSize().x / 2.0f, m_track.getSize().y / 2.0f);

	m_selection.setRadius(25);
	m_selection.setPointCount(3);
	m_selection.setFillColor(sf::Color::Green);
	m_selection.setRotation(180);
	m_selection.setPosition(sf::Vector2f(275, 100));
}

void TrackSelection::resetGame()
{
	m_gameplay->resetGame();
}
