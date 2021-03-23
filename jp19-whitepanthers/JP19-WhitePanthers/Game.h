#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include "Globals.h"
#include "Controls.h"
#include "Credits.h"
#include "Cutscene.h"
#include "Equipment.h"
#include "Highscore.h"
#include "Licence.h"
#include "MainMenu.h"
#include "Options.h"
#include "Pause.h"
#include "Store.h"
#include "TrackSelection.h"
#include "Splash.h"
#include "Controller.h"
#include "LevelLoader.h"
#include "Player.h"
#include "ResourceManager.h"

class Licence;
class Splash;
class GamePlay;
class MainMenu;
class Options;
class Cutscene;
class Credits;
class Pause;
class HighScore;
class Controls;
class Store;
class Equipment;
class TrackSelection;
class Player;

class Game
{
public:
	Game();
	~Game();
	void run();

	GameMode m_currentMode{ GameMode::Licence};
	
	LevelData m_levelData;

	Xbox360Controller m_controller;
	int m_currency;
private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void updateSoundVol();
	void setupAssets();
	void setupClasses();
	void loadLevel();

	std::unique_ptr<Licence> m_licenceScreen;
	std::unique_ptr<Splash> m_splashScreen;
	std::shared_ptr<MainMenu> m_mainMenuScreen;
	std::shared_ptr<Options> m_optionsScreen;
	std::shared_ptr<GamePlay> m_gameplayScreen;
	std::unique_ptr<Credits> m_creditsScreen;
	std::unique_ptr<Cutscene> m_cutsceneScreen;
	std::shared_ptr<Highscore> m_highscoreScreen;
	std::shared_ptr<Controls> m_controlsScreen;
	std::shared_ptr<Equipment> m_equipmentScreen;
	std::shared_ptr<Store> m_storeScreen;
	std::unique_ptr<TrackSelection> m_trackSelectionScreen;

	sf::RenderWindow m_window;
	bool m_exitGame;

	sf::Music m_bgMusic;
	sf::Music m_gameplayMusic;

	sf::SoundBuffer m_moveBuff;
	sf::Sound m_moveSound;

	sf::SoundBuffer m_selectBuff;
	sf::Sound m_selectSound;

	sf::SoundBuffer m_backBuff;
	sf::Sound m_backSound;

	sf::SoundBuffer m_buyBuff;
	sf::Sound m_buySound;

	sf::SoundBuffer m_carAccelBuff;
	sf::Sound m_accelerateSound;

	sf::SoundBuffer m_downshiftBuff;
	sf::Sound m_downshiftSound;

	sf::SoundBuffer m_brakeBuff;
	sf::Sound m_brakeSound;
};

#include "GamePlay.h"
#endif // !GAME