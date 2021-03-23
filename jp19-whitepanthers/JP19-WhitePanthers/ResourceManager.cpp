#include "ResourceManager.h"

thor::ResourceHolder<sf::Texture, std::string> ResourceManager::m_textureHolder;
thor::ResourceHolder<sf::Font, std::string> ResourceManager::m_fontHolder;
thor::ResourceHolder<sf::SoundBuffer, std::string> ResourceManager::m_soundHolder;

void ResourceManager::loadResources(LevelData & t_data)
{	
	try
	{
		//fonts
		m_fontHolder.acquire(t_data.m_myFonts.m_neonFont, thor::Resources::fromFile<sf::Font>(t_data.m_myFonts.m_neonFontFileName));
		m_fontHolder.acquire(t_data.m_myFonts.m_arialBlackFont, thor::Resources::fromFile<sf::Font>(t_data.m_myFonts.m_arialBlackFontFileName));

		//textures
		//backgrounds
		m_textureHolder.acquire(t_data.m_myTextures.m_bGID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_bGFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_bGTwoID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_bGTwoFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_bGThreeID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_bGThreeFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_bGFourID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_bGFourFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_bGFiveID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_bGFiveFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_bGSixID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_bGSixFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_bGSevenID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_bGSevenFile));
		//main menu
		m_textureHolder.acquire(t_data.m_myTextures.m_mainLeftID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_mainLeftFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_mainCar1ID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_mainCar1File));
		m_textureHolder.acquire(t_data.m_myTextures.m_mainHeadingID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_mainHeadingFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_mainCar2ID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_mainCar2File));
		m_textureHolder.acquire(t_data.m_myTextures.m_mainBottomID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_mainBottomFile));
		//controls screen
		m_textureHolder.acquire(t_data.m_myTextures.m_controlsControllerID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_controlsControllerFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_controlsOGameID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_controlsOGameFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_controlsOMainID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_controlsOMainFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_controlsOTrackID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_controlsOTrackFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_controlsOLeaderID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_controlsOLeaderFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_controlsOStoreID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_controlsOStoreFile));
		//extras
		m_textureHolder.acquire(t_data.m_myTextures.m_coinID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_coinFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_hudID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_hudFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_sfmlID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_sfmlFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_carsID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_carsFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_tabID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_tabFile));
		//equipment
		m_textureHolder.acquire(t_data.m_myTextures.m_equipmentWheelID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_equipmentWheelFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_equipmentOutlineID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_equipmentOutlineFile));
		//highscore
		m_textureHolder.acquire(t_data.m_myTextures.m_highscoreHeadingID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_highscoreHeadingFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_highscoreMainID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_highscoreMainFile));
		m_textureHolder.acquire(t_data.m_myTextures.m_highscoreBackID, thor::Resources::fromFile<sf::Texture>(t_data.m_myTextures.m_highscoreBackFile));

		//sounds
		m_soundHolder.acquire(t_data.m_mySounds.m_backID, thor::Resources::fromFile<sf::SoundBuffer>(t_data.m_mySounds.m_backFile));
		m_soundHolder.acquire(t_data.m_mySounds.m_selectID, thor::Resources::fromFile<sf::SoundBuffer>(t_data.m_mySounds.m_selectFile));
		m_soundHolder.acquire(t_data.m_mySounds.m_accelID, thor::Resources::fromFile<sf::SoundBuffer>(t_data.m_mySounds.m_accelFile));
		m_soundHolder.acquire(t_data.m_mySounds.m_brakeID, thor::Resources::fromFile<sf::SoundBuffer>(t_data.m_mySounds.m_brakeFile));
		m_soundHolder.acquire(t_data.m_mySounds.m_buyID, thor::Resources::fromFile<sf::SoundBuffer>(t_data.m_mySounds.m_buyFile));
		m_soundHolder.acquire(t_data.m_mySounds.m_downshiftID, thor::Resources::fromFile<sf::SoundBuffer>(t_data.m_mySounds.m_downshiftFile));
		m_soundHolder.acquire(t_data.m_mySounds.m_moveID, thor::Resources::fromFile<sf::SoundBuffer>(t_data.m_mySounds.m_moveFile));
		m_soundHolder.acquire(t_data.m_mySounds.m_lightBuzzID, thor::Resources::fromFile<sf::SoundBuffer>(t_data.m_mySounds.m_lightBuzzFile));
	}
	catch (thor::ResourceLoadingException& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}