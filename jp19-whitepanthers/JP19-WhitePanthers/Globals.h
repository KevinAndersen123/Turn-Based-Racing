#ifndef GLOBALS
#define GLOBALS

#include <SFML\Graphics.hpp>

enum class AnimationMode
{
	None,
	Disappear,
	Appear,
	Always
};

enum class GameMode
{
	Licence, // unique
	splash, // unique
	MainMenu, // shared
	Options, // shared
	GamePlay, // unique
	Pause, // unique
	Credits, // unique
	Cutscene, // unique
	Highscore, // shared
	Controls, // shared
	Equipment, //shared
	Store, //shared
	TrackSelection, //unique
	Exit
};

struct ScreenSize
{
public:
	static const int s_WIDTH{ 1600 }; //The width of the screen
	static const int s_HEIGHT{ 900 }; //The height of the screen
};


static const sf::Color s_SELECTED = sf::Color::Magenta;
static const sf::Color s_UN_SELECTED = sf::Color::Cyan;
static const sf::Color s_BOUGHT = sf::Color{ 9, 249, 117 };
static const sf::Color s_INVALID = sf::Color{ 255, 0, 0 };

static const int s_MAX_TABS{ 4 };
const std::string TAB_NAMES[s_MAX_TABS] = { "Spoiler","Tyres","Brakes","Engine" }; //The tabs names
const sf::Vector2f TAB_POSITION{ sf::Vector2f(200.0f, 520.0f) }; //the initial of the fist tab
const std::string UPGRADE_NAME[s_MAX_TABS] = { "spoiler","tyres","brakes","engine" }; //the names of each of the upgrades
const sf::Vector2f UPGRADE_POSITION[s_MAX_TABS] = { sf::Vector2f(70.0f, 320.0f),sf::Vector2f(470.0f,320.0f),
													sf::Vector2f(870.0f, 320.0f),sf::Vector2f(1270.0f,320.0f) }; //The initial position of each item
const sf::Vector2f EQUIPMENT_POSITION[s_MAX_TABS] = { sf::Vector2f(70.0f, 320.0f),sf::Vector2f(210.0f,320.0f),
													sf::Vector2f(370.0f, 320.0f),sf::Vector2f(510.0f,320.0f) };
extern int s_currentVolume;

extern bool s_audioActive;
extern bool s_sfxActive;
extern bool s_musicActive;

#endif