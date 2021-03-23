#include "LevelLoader.h"

/// The various operator >> overloads below are non-member functions used to extract
///  the game data from the YAML data structure.

void operator >> (const YAML::Node& t_SpriteSheetNode, CarSpriteData& t_SpriteSheet)
{
	t_SpriteSheet.m_blueColour.left = t_SpriteSheetNode["intRect1"]["x"].as<float>();
	t_SpriteSheet.m_blueColour.top = t_SpriteSheetNode["intRect1"]["y"].as<float>();
	t_SpriteSheet.m_blueColour.width = t_SpriteSheetNode["intRect1"]["w"].as<float>();
	t_SpriteSheet.m_blueColour.height = t_SpriteSheetNode["intRect1"]["h"].as<float>();

	t_SpriteSheet.m_greenColour.left = t_SpriteSheetNode["intRect2"]["x"].as<float>();
	t_SpriteSheet.m_greenColour.top = t_SpriteSheetNode["intRect2"]["y"].as<float>();
	t_SpriteSheet.m_greenColour.width = t_SpriteSheetNode["intRect2"]["w"].as<float>();
	t_SpriteSheet.m_greenColour.height = t_SpriteSheetNode["intRect2"]["h"].as<float>();

	t_SpriteSheet.m_redColour.left = t_SpriteSheetNode["intRect3"]["x"].as<float>();
	t_SpriteSheet.m_redColour.top = t_SpriteSheetNode["intRect3"]["y"].as<float>();
	t_SpriteSheet.m_redColour.width = t_SpriteSheetNode["intRect3"]["w"].as<float>();
	t_SpriteSheet.m_redColour.height = t_SpriteSheetNode["intRect3"]["h"].as<float>();

	t_SpriteSheet.m_yellowColour.left = t_SpriteSheetNode["intRect4"]["x"].as<float>();
	t_SpriteSheet.m_yellowColour.top = t_SpriteSheetNode["intRect4"]["y"].as<float>();
	t_SpriteSheet.m_yellowColour.width = t_SpriteSheetNode["intRect4"]["w"].as<float>();
	t_SpriteSheet.m_yellowColour.height = t_SpriteSheetNode["intRect4"]["h"].as<float>();
	
}

void operator >> (const YAML::Node& t_fontNode,MyFonts& t_fonts)
{
	t_fonts.m_neonFontFileName = t_fontNode["neon_font_file"].as<std::string>();
	t_fonts.m_arialBlackFontFileName = t_fontNode["arial_black_font_file"].as<std::string>();
	t_fonts.m_neonFont = t_fontNode["neon_font"].as<std::string>();
	t_fonts.m_arialBlackFont = t_fontNode["arial_black_font"].as<std::string>();
}

void operator >> (const YAML::Node& t_textureNode, MyTextures& t_texture)
{
	t_texture.m_bGID = t_textureNode["bg_one_ID"].as<std::string>();
	t_texture.m_bGFile = t_textureNode["bg_one_file"].as<std::string>();
	t_texture.m_bGTwoID = t_textureNode["bg_two_ID"].as<std::string>();
	t_texture.m_bGTwoFile = t_textureNode["bg_two_file"].as<std::string>();
	t_texture.m_bGThreeID = t_textureNode["bg_three_ID"].as<std::string>();
	t_texture.m_bGThreeFile = t_textureNode["bg_three_file"].as<std::string>();
	t_texture.m_bGFourID = t_textureNode["bg_four_ID"].as<std::string>();
	t_texture.m_bGFourFile = t_textureNode["bg_four_file"].as<std::string>();
	t_texture.m_bGFiveID = t_textureNode["bg_five_ID"].as<std::string>();
	t_texture.m_bGFiveFile = t_textureNode["bg_five_file"].as<std::string>();
	t_texture.m_bGSixID = t_textureNode["bg_six_ID"].as<std::string>();
	t_texture.m_bGSixFile = t_textureNode["bg_six_file"].as<std::string>();
	t_texture.m_bGSevenID = t_textureNode["bg_seven_ID"].as<std::string>();
	t_texture.m_bGSevenFile = t_textureNode["bg_seven_file"].as<std::string>();

	t_texture.m_mainLeftID = t_textureNode["main_left_ID"].as<std::string>();
	t_texture.m_mainLeftFile = t_textureNode["main_left_file"].as<std::string>();
	t_texture.m_mainCar1ID = t_textureNode["main_car_ID"].as<std::string>();
	t_texture.m_mainCar1File = t_textureNode["main_car_file"].as<std::string>();
	t_texture.m_mainHeadingID = t_textureNode["main_heading_ID"].as<std::string>();
	t_texture.m_mainHeadingFile = t_textureNode["main_heading_file"].as<std::string>();
	t_texture.m_mainCar2ID = t_textureNode["main_car2_ID"].as<std::string>();
	t_texture.m_mainCar2File = t_textureNode["main_car2_file"].as<std::string>();
	t_texture.m_mainBottomID = t_textureNode["main_bottom_ID"].as<std::string>();
	t_texture.m_mainBottomFile = t_textureNode["main_bottom_file"].as<std::string>();

	t_texture.m_controlsControllerID = t_textureNode["controls_controller_ID"].as<std::string>();
	t_texture.m_controlsControllerFile = t_textureNode["controls_controller_file"].as<std::string>();
	t_texture.m_controlsOGameID = t_textureNode["controls_overlay_game_ID"].as<std::string>();
	t_texture.m_controlsOGameFile = t_textureNode["controls_overlay_game_file"].as<std::string>();
	t_texture.m_controlsOMainID = t_textureNode["controls_overlay_main_ID"].as<std::string>();
	t_texture.m_controlsOMainFile = t_textureNode["controls_overlay_main_file"].as<std::string>();
	t_texture.m_controlsOTrackID = t_textureNode["controls_overlay_track_ID"].as<std::string>();
	t_texture.m_controlsOTrackFile = t_textureNode["controls_overlay_track_file"].as<std::string>();
	t_texture.m_controlsOLeaderID = t_textureNode["controls_overlay_leader_ID"].as<std::string>();
	t_texture.m_controlsOLeaderFile = t_textureNode["controls_overlay_leader_file"].as<std::string>();
	t_texture.m_controlsOStoreID = t_textureNode["controls_overlay_store_ID"].as<std::string>();
	t_texture.m_controlsOStoreFile = t_textureNode["controls_overlay_store_file"].as<std::string>();

	t_texture.m_coinID = t_textureNode["coin_ID"].as<std::string>();
	t_texture.m_coinFile = t_textureNode["coin_File"].as<std::string>();
	t_texture.m_hudID = t_textureNode["hud_ID"].as<std::string>();
	t_texture.m_hudFile = t_textureNode["hud_file"].as<std::string>();
	t_texture.m_sfmlID = t_textureNode["sfml_logo_ID"].as<std::string>();
	t_texture.m_sfmlFile = t_textureNode["sfml_logo_file"].as<std::string>();
	t_texture.m_carsID = t_textureNode["car_spritesheet_ID"].as<std::string>();
	t_texture.m_carsFile = t_textureNode["car_spritesheet_file"].as<std::string>();
	t_texture.m_tabID = t_textureNode["tab_ID"].as<std::string>();
	t_texture.m_tabFile = t_textureNode["tab_file"].as<std::string>();

	t_texture.m_equipmentWheelID = t_textureNode["equipment_wheel_ID"].as<std::string>();
	t_texture.m_equipmentWheelFile = t_textureNode["equipment_wheel_file"].as<std::string>();
	t_texture.m_equipmentOutlineID = t_textureNode["equipmenet_outline_ID"].as<std::string>();
	t_texture.m_equipmentOutlineFile = t_textureNode["equipment_outline_file"].as<std::string>();

	t_texture.m_highscoreHeadingID = t_textureNode["highscore_heading_ID"].as<std::string>();
	t_texture.m_highscoreHeadingFile = t_textureNode["highscore_heading_file"].as<std::string>();
	t_texture.m_highscoreMainID = t_textureNode["highscore_main_ID"].as<std::string>();
	t_texture.m_highscoreMainFile = t_textureNode["highscore_main_file"].as<std::string>();
	t_texture.m_highscoreBackID = t_textureNode["highscore_back_ID"].as<std::string>();
	t_texture.m_highscoreBackFile = t_textureNode["highscore_back_file"].as<std::string>();
}

void operator >> (const YAML::Node& t_soundNode, MySounds& t_sound)
{
	t_sound.m_backID = t_soundNode["back_sound_ID"].as<std::string>();
	t_sound.m_backFile = t_soundNode["back_sound_file"].as<std::string>();

	t_sound.m_selectID = t_soundNode["select_sound_ID"].as<std::string>();
	t_sound.m_selectFile = t_soundNode["select_sound_file"].as<std::string>();

	t_sound.m_accelID = t_soundNode["accelerating_sound_ID"].as<std::string>();
	t_sound.m_accelFile = t_soundNode["accelerating_sound_file"].as<std::string>();

	t_sound.m_brakeID = t_soundNode["brake_sound_ID"].as<std::string>();
	t_sound.m_brakeFile = t_soundNode["brake_sound_file"].as<std::string>();

	t_sound.m_buyID = t_soundNode["buy_sound_ID"].as<std::string>();
	t_sound.m_buyFile = t_soundNode["buy_sound_file"].as<std::string>();

	t_sound.m_downshiftID = t_soundNode["downshift_sound_ID"].as<std::string>();
	t_sound.m_downshiftFile = t_soundNode["downshift_sound_file"].as<std::string>();

	t_sound.m_moveID = t_soundNode["move_sound_ID"].as<std::string>();
	t_sound.m_moveFile = t_soundNode["move_sound_file"].as<std::string>();

	t_sound.m_lightBuzzID = t_soundNode["light_buzz_ID"].as<std::string>();
	t_sound.m_lightBuzzFile = t_soundNode["light_buzz_file"].as<std::string>();
}

/// <summary>
/// @brief Extracts the initial screen position for the player tank.
/// 
/// </summary>
/// <param name="tankNode">A YAML node</param>
/// <param name="tank">A simple struct to store data related to the player tank</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_carNode, CarData& t_car)
{
	t_car.m_position.x = t_carNode["position"]["x"].as<float>();
	t_car.m_position.y = t_carNode["position"]["y"].as<float>();
	t_car.m_rotation = t_carNode["rotation"].as<float>();
}

void operator >> (const YAML::Node& t_upgradesNode, UpgradesData& t_upgrades)
{
	t_upgrades.m_type = t_upgradesNode["type"].as<std::string>();
	t_upgrades.m_price = t_upgradesNode["price"].as<int>();
	t_upgrades.m_name = t_upgradesNode["name"].as<std::string>();
	t_upgrades.m_modifier = t_upgradesNode["modifier"].as<int>();
}

void operator >> (const YAML::Node& t_scoreNode, LeaderboardData& t_data)
{
	t_data.m_name = t_scoreNode["name"].as<std::string>();
	t_data.m_time = t_scoreNode["time"].as<float>();
}

/// <summary>
/// @brief Top level function that extracts various game data from the YAML data stucture.
/// 
/// Invokes other functions to extract the background, tank and obstacle data.
//   Because there are multiple obstacles, obstacle data are stored in a vector.
/// </summary>
/// <param name="tankNode">A YAML node</param>
/// <param name="tank">A simple struct to store data related to the player tank</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_levelNode, LevelData& t_level)
{
	t_levelNode["car1"] >> t_level.m_car1;

	t_levelNode["car2"] >> t_level.m_car2;

	t_levelNode["car3"] >> t_level.m_car3;

	t_levelNode["car4"] >> t_level.m_car4;

	t_levelNode["MyFonts"] >> t_level.m_myFonts;

	t_levelNode["carSprite"] >> t_level.m_SpriteSheet;

	t_levelNode["MyTextures"] >> t_level.m_myTextures;

	t_levelNode["MySounds"] >> t_level.m_mySounds;


	const YAML::Node& upgradeNode = t_levelNode["Upgrades"].as<YAML::Node>();
	for (unsigned i = 0; i < upgradeNode.size(); ++i)
	{
		UpgradesData upgrade;
		upgradeNode[i] >> upgrade;
		t_level.m_upgrades.push_back(upgrade);
	}

	const YAML::Node& scoresNode = t_levelNode["HighScore"].as<YAML::Node>();
	for (unsigned i = 0; i < scoresNode.size(); ++i)
	{
		LeaderboardData data;
		scoresNode[i] >> data;
		t_level.m_scores.push_back(data);
	}
}

////////////////////////////////////////////////////////////
void LevelLoader::load(int t_nr, LevelData& t_level)
{
	std::stringstream ss;
	ss << "level";
	ss << t_nr;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("File: " + ss.str() + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> t_level;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}


