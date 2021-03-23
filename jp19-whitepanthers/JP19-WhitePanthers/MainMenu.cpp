#include "MainMenu.h"

MainMenu::MainMenu(Game & t_game,sf::Sound & t_moveSound, sf::Sound & t_selectSound) :
	m_game(t_game),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_neonFont]),
	m_MenuOptions{
		TextButtons(t_game.m_levelData,sf::Vector2f{ -310.0f,320.0f },false,40,"PLAY"),
		TextButtons(t_game.m_levelData,sf::Vector2f{ -310.0f,390.0f },false,40,"CONTROLS"),
		TextButtons(t_game.m_levelData,sf::Vector2f{ -310.0f,460.0f },false,40,"SHOP"),
		TextButtons(t_game.m_levelData,sf::Vector2f{ -310.0f,530.0f },false,40,"GARAGE"),
		TextButtons(t_game.m_levelData,sf::Vector2f{ -310.0f,600.0f },false,40,"SETTINGS"),
		TextButtons(t_game.m_levelData,sf::Vector2f{ -310.0f,670.0f },false,40,"HIGHSCORES"),
		TextButtons(t_game.m_levelData,sf::Vector2f{ -310.0f,750.0f },false,40,"QUIT")
	},
	m_inputTimer( 10 ),
	m_cumalativeTime( sf::Time::Zero ),
	m_currentButton( ButtonName::Controls ),
	m_moveSound( t_moveSound ),
	m_selectSound(t_selectSound),
	m_bgLeftTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_mainLeftID]),
	m_carTex1(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_mainCar1ID]),
	m_carTex2(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_mainCar2ID]),
	m_headingTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_mainHeadingID]),
	m_bgBottomTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_mainBottomID]),
	m_backgroundTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_bGTwoID])
{
	setupText();
	setupSprites();
	m_currentButton = ButtonName::Play;
}

MainMenu::~MainMenu()
{
}

//---------------------------------------------------------------------------------------------------
/// <summary>
/// Function that updates the cumulative time and allows any animations on screen 
/// to play out
/// </summary>
/// <param name="t_deltaTime">time between frames</param>
///--------------------------------------------------------------------------------------------------
void MainMenu::update(sf::Time t_deltaTime)
{
	m_cumalativeTime += t_deltaTime;
	animateScreen();
}

//---------------------------------------------------------------------------------------------------
/// <summary>
/// Function that draws all sprites and text to the screen
/// </summary>
/// <param name="t_window">game window</param>
///--------------------------------------------------------------------------------------------------
void MainMenu::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color{ 89, 0, 179 });
	t_window.draw(m_background);
	t_window.draw(m_bgBottom);
	t_window.draw(m_carSprite1);
	t_window.draw(m_carSprite2);
	t_window.draw(m_bgLeft);
	t_window.draw(m_heading);
	for (int i = 0; i < s_MAX_BUTTONS; i++)
	{
		m_MenuOptions[i].draw(t_window);
	}

	t_window.display();
}

//---------------------------------------------------------------------------------------------------
/// <summary>
/// Function that sets up the menu options colour and highlight colour, also sets the 
/// current highlighted button to be highlighted on screen
/// </summary>
///--------------------------------------------------------------------------------------------------
void MainMenu::setupText()
{	
	for (int i = 0; i < s_MAX_BUTTONS; i++)
	{
		m_MenuOptions[i].setOutlineColour(sf::Color{ 230, 179, 255 });
		m_MenuOptions[i].setTextColour(sf::Color{ 184, 0, 230 });
	}
	m_MenuOptions[static_cast<int>(m_currentButton)].setHighlighted(true);
}


//---------------------------------------------------------------------------------------------------
/// <summary>
/// Loads in all textures for the sprites on screen, sets them tot he relevent sprite
/// and sets up the sprites position and scale to be ready to be drawn on screen
/// </summary>
///--------------------------------------------------------------------------------------------------
void MainMenu::setupSprites()
{
	// Left panel
	m_bgLeft.setTexture(m_bgLeftTex);
	m_bgLeft.setPosition(sf::Vector2f{ -600.0f,0.0f });

	// blue car
	m_carSprite1.setTexture(m_carTex1);
	m_carSprite1.setScale(1.7f, 1.7f);
	m_carSprite1.setPosition(sf::Vector2f{ 1300.0f,static_cast<float>(ScreenSize::s_HEIGHT) });

	// orange car
	m_carSprite2.setTexture(m_carTex2);
	m_carSprite2.setScale(2.3f, 2.3f);
	m_carSprite2.setPosition(sf::Vector2f{ 1000.0f, static_cast<float>(ScreenSize::s_HEIGHT + 150)});

	// logo
	m_headingTex.setSmooth(true);
	m_heading.setTexture(m_headingTex);
	m_heading.setScale(0.6f, 0.6f);
	m_heading.setPosition(sf::Vector2f{ -550.0f,30.0f });

	// cityscape
	m_background.setTexture(m_backgroundTex);
	m_background.setPosition(sf::Vector2f{ 0.0f,-150.0f });

	// road
	m_bgBottom.setTexture(m_bgBottomTex);
	m_bgBottom.setPosition(sf::Vector2f{ 0.0f,0.0f });
}

//---------------------------------------------------------------------------------------------------
/// <summary>
/// Function that checks if the user inputted up/down and changes the highlighted menu
/// option accordingly. Also checks if the user selected an option 
/// </summary>
///--------------------------------------------------------------------------------------------------
void MainMenu::checkInput()
{
	m_inputTimer--;

	// to go up an option
	if ((m_game.m_controller.m_currentState.LeftThumbStick.y < -50.0f || m_game.m_controller.m_currentState.DpadUp) && m_inputTimer < 0)
	{
		if (s_audioActive&& s_sfxActive) 
		{
			m_moveSound.play();
		}
		m_inputTimer = 10;
		if (static_cast<int>(m_currentButton) > 0)
		{
			m_currentButton = static_cast<ButtonName>(static_cast<int>(m_currentButton) - 1);
		}
		// loop to bottom option
		else
		{
			m_currentButton = ButtonName::Quit;
		}
	}
	// to go down an option
	if ((m_game.m_controller.m_currentState.LeftThumbStick.y > 50.0f || m_game.m_controller.m_currentState.DpadDown) && m_inputTimer < 0)
	{
		if (s_audioActive&& s_sfxActive)
		{
			m_moveSound.play();
		}
		m_inputTimer = 10;
		if (static_cast<int>(m_currentButton) < s_MAX_BUTTONS - 1)
		{
			m_currentButton = static_cast<ButtonName>(static_cast<int>(m_currentButton) + 1);
		}
		// loop to top option
		else
		{
			m_currentButton = ButtonName::Play;
		}
	}
	// select option
	if (m_game.m_controller.m_currentState.A)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_selectSound.play();
		}
		m_inputTimer = 10;
		m_animationMode = AnimationMode::Disappear;
	}
	//set current option to be highlighted
	for (int i = 0; i < s_MAX_BUTTONS; i++)
	{
		if (static_cast<int>(m_currentButton) != i)
		{
			m_MenuOptions[i].setHighlighted(false);
		}
		else
		{
			m_MenuOptions[static_cast<int>(m_currentButton)].setHighlighted(true);
		}
	}
}

//---------------------------------------------------------------------------------------------------
/// <summary>
/// checks which menu option was selected by the user and changes to the relevent screen
/// </summary>
///--------------------------------------------------------------------------------------------------
void MainMenu::checkButtonSelect()
{
	// reset screen
	m_animationMode = AnimationMode::Appear;
	m_cumalativeTime = sf::Time::Zero; 

	switch (m_currentButton)
	{
	case ButtonName::Play:
		m_game.m_currentMode = GameMode::TrackSelection;
		break;
	case ButtonName::Controls:
		m_game.m_currentMode = GameMode::Controls;
		break;
	case ButtonName::Shop:
		m_game.m_currentMode = GameMode::Store;
		break;
	case ButtonName::Garage:
		m_game.m_currentMode = GameMode::Equipment;
		break;
	case ButtonName::Settings:
		m_game.m_currentMode = GameMode::Options;
		break;
	case ButtonName::Highscore:
		m_game.m_currentMode = GameMode::Highscore;
		break;
	case ButtonName::Quit:
		m_game.m_currentMode = GameMode::Exit;
		break;
	default:
		break;
	}
}

//---------------------------------------------------------------------------------------------------
/// <summary>
/// handles the opening and closing animations and text glow. 
/// </summary>
///--------------------------------------------------------------------------------------------------
void MainMenu::animateScreen()
{

	/// ------------------------------
	/// Appearing animation
	/// ------------------------------
	if (m_animationMode == AnimationMode::Appear)
	{
		if (m_bgLeft.getPosition().x < 0.0f)
		{
			// slide left panel right
			m_bgLeft.move(sf::Vector2f{ 30.0f,0.0f });
			m_heading.move(sf::Vector2f{ 30.0f,0.0f });
			for (int i = 0; i < s_MAX_BUTTONS; i++)
			{
				m_MenuOptions[i].setPosition(m_MenuOptions[i].getPosition() + sf::Vector2f{ 30.0f,0.0f });
			}
		}
		else
		{
			// move cars up
			if (m_carSprite1.getPosition().y > 400.0f)
			{
				m_carSprite1.move(sf::Vector2f{-10.0f,-12.0f});
				m_carSprite2.move(sf::Vector2f{-9.0f,-11.0f});
			}
			else
			{
				m_animationMode = AnimationMode::None;
			}
		}
	}
	/// ------------------------------
	/// on screen animations
	/// ------------------------------
	if (m_animationMode == AnimationMode::None)
	{
		// make highlighted text glow
		for (int i = 0; i < s_MAX_BUTTONS; i++)
		{
			m_MenuOptions[i].makeTextGlow();
		}
		checkInput();
	}

	/// ------------------------------
	/// dissappear animation
	/// ------------------------------
	if (m_animationMode == AnimationMode::Disappear)
	{
		// move left panel back to original position 
		m_bgLeft.move(sf::Vector2f{ -30.0f,0.0f });
		m_heading.move(sf::Vector2f{ -30.0f,0.0f });
		for (int i = 0; i < s_MAX_BUTTONS; i++)
		{
			m_MenuOptions[i].setPosition(m_MenuOptions[i].getPosition() + sf::Vector2f{ -30.0f,0.0f });
		}
		if (m_bgLeft.getPosition().x <= -600.0f)
		{
			// switch to chosen screen
			checkButtonSelect();
		}
	}
}
