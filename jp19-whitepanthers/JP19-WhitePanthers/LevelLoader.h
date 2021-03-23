#pragma once

#include <SFML/System/Vector2.hpp>
#include<SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

struct MyFonts
{
	std::string m_neonFontFileName;
	std::string m_neonFont;
	std::string m_arialBlackFontFileName;
	std::string m_arialBlackFont;
};

struct MyTextures
{
	std::string m_bGID;
	std::string m_bGFile;
	std::string m_bGTwoID;
	std::string m_bGTwoFile;
	std::string m_bGThreeID;
	std::string m_bGThreeFile;
	std::string m_bGFourID;
	std::string m_bGFourFile;
	std::string m_bGFiveID;
	std::string m_bGFiveFile;
	std::string m_bGSixID;
	std::string m_bGSixFile;
	std::string m_bGSevenID;
	std::string m_bGSevenFile;
	//---------------------
	std::string m_mainLeftID;
	std::string m_mainLeftFile;
	std::string m_mainCar1ID;
	std::string m_mainCar1File;
	std::string m_mainHeadingID;
	std::string m_mainHeadingFile;
	std::string m_mainCar2ID;
	std::string m_mainCar2File;
	std::string m_mainBottomID;
	std::string m_mainBottomFile;
	//-----------------------------
	std::string m_controlsControllerID;
	std::string m_controlsControllerFile;
	std::string m_controlsOGameID;
	std::string m_controlsOGameFile;
	std::string m_controlsOMainID;
	std::string m_controlsOMainFile;
	std::string m_controlsOTrackID;
	std::string m_controlsOTrackFile;
	std::string m_controlsOLeaderID;
	std::string m_controlsOLeaderFile;
	std::string m_controlsOStoreID;
	std::string m_controlsOStoreFile;
	//---------------------
	std::string m_coinID;
	std::string m_coinFile;
	std::string m_hudID;
	std::string m_hudFile;
	std::string m_sfmlID;
	std::string m_sfmlFile;
	std::string m_carsID;
	std::string m_carsFile;
	std::string m_tabID;
	std::string m_tabFile;
	std::string m_equipmentWheelID;
	std::string m_equipmentWheelFile;
	std::string m_equipmentOutlineID;
	std::string m_equipmentOutlineFile;
	//---------------------
	std::string m_highscoreHeadingID;
	std::string m_highscoreHeadingFile;
	std::string m_highscoreMainID;
	std::string m_highscoreMainFile;
	std::string m_highscoreBackID;
	std::string m_highscoreBackFile;
};

struct MySounds
{
	std::string m_backID;
	std::string m_backFile;
	std::string m_selectID;
	std::string m_selectFile;
	std::string m_accelID;
	std::string m_accelFile;
	std::string m_brakeID;
	std::string m_brakeFile;
	std::string m_buyID;
	std::string m_buyFile;
	std::string m_downshiftID;
	std::string m_downshiftFile;
	std::string m_moveID;
	std::string m_moveFile;
	std::string m_lightBuzzID;
	std::string m_lightBuzzFile;
};

struct CarSpriteData
{
	sf::IntRect m_blueColour;
	sf::IntRect m_greenColour;
	sf::IntRect m_redColour;
	sf::IntRect m_yellowColour;
};

struct UpgradesData
{
	std::string m_type;
	std::string m_name;
	int m_price;
	int m_modifier;
	
};

struct HighScoreAssetsData
{
	std::string m_highscoreMain;
	std::string m_highscoreHeading;
	std::string m_highscoresFont;
	std::string m_backButton;
	std::string m_background;
};

struct CarData
{
	sf::Vector2f m_position;
	float m_rotation;
};

struct LeaderboardData
{
	std::string m_name;
	float m_time;
};

struct LevelData
{
	MyFonts m_myFonts;
	MyTextures m_myTextures;
	MySounds m_mySounds;
	std::vector<UpgradesData> m_upgrades;
	CarSpriteData m_SpriteSheet;
	CarData m_car1;
	CarData m_car2;
	CarData m_car3;
	CarData m_car4;
	HighScoreAssetsData m_highscoreAssetsData;
	std::vector<LeaderboardData>m_scores;
};


class LevelLoader
{
public:
	LevelLoader() = default;
	static void load(int nr, LevelData& level);
};