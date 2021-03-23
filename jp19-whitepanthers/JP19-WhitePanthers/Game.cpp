#include "Game.h"

int GLOBALS::s_currentVolume{ 50 };
bool GLOBALS::s_audioActive{ true };
bool GLOBALS::s_sfxActive{ true };
bool GLOBALS::s_musicActive{ true };

Game::Game() :
	m_window{ sf::VideoMode{ 1600, 900, 32 }, "Mafia Racers 3 By White Panthers" },
	m_exitGame( false ),
	m_currency(500)
{
	srand((unsigned)time(nullptr));
	setupAssets();
	setupClasses();
	m_bgMusic.setLoop(true);
	m_gameplayMusic.setLoop(true);
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}


void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
	}
}


/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_controller.connect())
	{
		m_controller.update(t_deltaTime);

		switch (m_currentMode)
		{
		case GameMode::Licence:
			m_licenceScreen->update(t_deltaTime);
			break;
		case GameMode::splash:
			m_splashScreen->update(t_deltaTime);
			break;
		case GameMode::MainMenu:
			m_mainMenuScreen->update(t_deltaTime);
			break;
		case GameMode::Options:
			m_optionsScreen->update(t_deltaTime);
			break;
		case GameMode::GamePlay:
			m_gameplayScreen->update(t_deltaTime);
			break;
		case GameMode::Pause:
			break;
		case GameMode::Credits:
			m_creditsScreen->update(t_deltaTime);
			break;
		case GameMode::Cutscene:
			m_cutsceneScreen->update(t_deltaTime);
			break;
		case GameMode::Highscore:
			m_highscoreScreen->update(t_deltaTime);
			break;
		case GameMode::Controls:
			m_controlsScreen->update(t_deltaTime);
			break;
		case GameMode::Equipment:
			m_equipmentScreen->update(t_deltaTime);
			break;
		case GameMode::Store:
			m_storeScreen->update(t_deltaTime);
			break;
		case GameMode::TrackSelection:
			m_trackSelectionScreen->update(t_deltaTime);
			break;
		default:
			break;
		}
	}
	updateSoundVol();
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	switch (m_currentMode)
	{
	case GameMode::Licence:
		m_licenceScreen->render(m_window);
		break;
	case GameMode::splash:
		m_splashScreen->render(m_window);
		break;
	case GameMode::MainMenu:
		m_mainMenuScreen->render(m_window);
		break;
	case GameMode::Options:
		m_optionsScreen->render(m_window);
		break;
	case GameMode::GamePlay:
		m_gameplayScreen->render(m_window);
		break;
	case GameMode::Pause:
		break;
	case GameMode::Credits:
		m_creditsScreen->render(m_window);
		break;
	case GameMode::Cutscene:
		m_cutsceneScreen->render(m_window);
		break;
	case GameMode::Highscore:
		m_highscoreScreen->render(m_window);
		break;
	case GameMode::Controls:
		m_controlsScreen->render(m_window);
		break;
	case GameMode::Equipment:
		m_equipmentScreen->render(m_window);
		break;
	case GameMode::Store:
		m_storeScreen->render(m_window);
		break;
	case GameMode::TrackSelection:
		m_trackSelectionScreen->render(m_window);
		break;
	case GameMode::Exit:
		m_window.close();
		break;
	default:
		break;
	}
}

void Game::updateSoundVol()
{
	m_brakeSound.setVolume(1.0f * s_currentVolume/10.0f);
	m_moveSound.setVolume(3.0f * s_currentVolume/10.0f);
	m_selectSound.setVolume(6.0f * s_currentVolume/10.0f);
	m_backSound.setVolume(8.0f * s_currentVolume/10.0f);
	m_buySound.setVolume(5.0f * s_currentVolume/10.0f);
	m_accelerateSound.setVolume(2.5f * s_currentVolume/10.0f);
	m_downshiftSound.setVolume(3.0f * s_currentVolume/10.0f);
	m_brakeSound.setVolume(1.0f * s_currentVolume/10.0f);
	m_gameplayMusic.setVolume(2.0f * s_currentVolume / 20.0f);
	m_bgMusic.setVolume(2.0f * s_currentVolume/20.0f);
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupAssets()
{
	loadLevel();
	ResourceManager::loadResources(m_levelData);
	m_backBuff = (ResourceManager::m_soundHolder[m_levelData.m_mySounds.m_backID]);
	m_selectBuff = (ResourceManager::m_soundHolder[m_levelData.m_mySounds.m_selectID]);
	m_carAccelBuff = (ResourceManager::m_soundHolder[m_levelData.m_mySounds.m_accelID]);
	m_brakeBuff = (ResourceManager::m_soundHolder[m_levelData.m_mySounds.m_brakeID]);
	m_buyBuff = (ResourceManager::m_soundHolder[m_levelData.m_mySounds.m_buyID]);
	m_downshiftBuff = (ResourceManager::m_soundHolder[m_levelData.m_mySounds.m_downshiftID]);
	m_moveBuff = (ResourceManager::m_soundHolder[m_levelData.m_mySounds.m_moveID]);
	if (!m_bgMusic.openFromFile("ASSETS/AUDIO/backgroundMusic.ogg"))
	{
		std::cout << "Cannot load audio- backgroundMusic" << std::endl;
	}
	if (!m_gameplayMusic.openFromFile("ASSETS/AUDIO/gameplay.ogg"))
	{
		std::cout << "Cannot load audio- backgroundMusic Gameplay" << std::endl;
	}
	m_accelerateSound.setBuffer(m_carAccelBuff);
	m_backSound.setBuffer(m_backBuff);
	m_selectSound.setBuffer(m_selectBuff);
	m_brakeSound.setBuffer(m_brakeBuff);
	m_buySound.setBuffer(m_buyBuff);
	m_downshiftSound.setBuffer(m_downshiftBuff);
	m_moveSound.setBuffer(m_moveBuff);

	m_gameplayMusic.setVolume(10);
	m_moveSound.setPitch(1.5);
	m_accelerateSound.setPlayingOffset(sf::seconds(1.5));
}

void Game::setupClasses()
{
	m_licenceScreen = std::make_unique<Licence>(*this,m_bgMusic);
	m_splashScreen = std::make_unique<Splash>(*this,m_selectSound);
	m_mainMenuScreen = std::make_shared<MainMenu>(*this,m_moveSound, m_selectSound);
	m_optionsScreen = std::make_shared<Options>(*this,m_backSound,m_selectSound,m_moveSound,m_bgMusic);
	m_gameplayScreen = std::make_unique<GamePlay>(*this,m_downshiftSound, m_accelerateSound, m_brakeSound,m_gameplayMusic,m_bgMusic);
	m_creditsScreen = std::make_unique<Credits>(*this);
	m_cutsceneScreen = std::make_unique<Cutscene>(*this);
	m_highscoreScreen = std::make_shared<Highscore>(*this, m_backSound);
	m_controlsScreen = std::make_shared<Controls>(*this,m_backSound, m_selectSound,	m_moveSound);
	m_equipmentScreen = std::make_shared<Equipment>(*this,m_gameplayScreen,m_selectSound, m_backSound,m_moveSound);
	m_storeScreen = std::make_shared<Store>(*this, m_equipmentScreen,m_selectSound, m_backSound,m_moveSound, m_buySound);
	m_trackSelectionScreen = std::make_unique<TrackSelection>(*this, m_gameplayScreen,m_bgMusic, m_gameplayMusic,m_backSound,m_moveSound,m_selectSound);
}

void Game::loadLevel()
{
	LevelLoader::load(1, m_levelData);
} 
