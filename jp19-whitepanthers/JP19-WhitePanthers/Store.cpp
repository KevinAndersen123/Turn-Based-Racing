#include "Store.h"

/// <summary>
/// constructor for shop class
/// </summary>
/// <param name="t_game"></param>
/// <param name="t_font"></param>
Store::Store(Game & t_game, std::shared_ptr<Equipment> t_equipment, sf::Sound & t_selectSound, sf::Sound & t_backSound, sf::Sound &t_moveSound, sf::Sound &t_buySound) :
	m_game(t_game),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_neonFont]),
	m_currentMode(AnimationMode::Appear),
	m_currentScreen(0),
	m_coinsText(t_game.m_levelData, 40, "Coins:", sf::Vector2f(80.0f, 50.0f), true),
	m_heading(t_game.m_levelData, 70, "Store", sf::Vector2f(800.0f, 70.0f), true),
	m_currentTab(0),
	m_currentItem(0),
	m_itemTimer(0),
	m_tabTimer(0),
	m_equipmentScreen(t_equipment),
	m_backSound{t_backSound},
	m_selectSound(t_selectSound),
	m_moveSound(t_moveSound),
	m_buySound(t_buySound),
	m_coinsTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_coinID]),
	m_tex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_bGSevenID])
{
	loadTabs();
	loadAssets();
	setup();
}

Store::~Store()
{
}

/// <summary>
/// Update for shop class
/// This class transitions through the screen states
/// </summary>
/// <param name="t_deltaTime"></param>
void Store::update(sf::Time t_deltaTime)
{
	m_cumalativeTime += t_deltaTime;
	m_coinsText.setString("Coins: " + std::to_string(m_game.m_currency));
	m_coinsSprite.setPosition(sf::Vector2f{ m_coinsText.getPosition().x + m_coinsText.getGlobalBounds().width - 20.0f,
		m_coinsText.getPosition().y + m_coinsText.getGlobalBounds().height / 2 - 20.0f });

	if (m_currentMode == AnimationMode::Appear)
	{
		//makes the screen fade in

		for (auto &tab : m_tabs)
		{
			tab->makeTabOpaque(7, 2);
		}


		for (auto &upgrade1 : m_upgradeItems)
		{
			for (auto &upgrade2 : upgrade1)
			{
				upgrade2->makeItemOpaque(7, 2);
			}
		}
		m_heading.makeOpaque(7, 2);
		m_coinsText.makeOpaque(7, 2);

		if (m_cumalativeTime.asSeconds() >= 2)
		{
			m_currentMode = AnimationMode::None;
		}
	}

	if (m_currentMode == AnimationMode::None)
	{
		highlightBoxes();
		//checks for input to change screen
		if (m_game.m_controller.m_currentState.B)
		{
			if (s_audioActive && s_sfxActive)
			{
				m_backSound.play();
			}
			m_currentScreen = 1;
			m_currentMode = AnimationMode::Disappear;
			m_cumalativeTime = sf::seconds(0);
		}
		else if (m_game.m_controller.m_currentState.Y)
		{
			if (s_audioActive && s_sfxActive)
			{
				m_selectSound.play();
			}
			m_currentScreen = 2;
			m_currentMode = AnimationMode::Disappear;
			m_cumalativeTime = sf::seconds(0);
		}
	}
	
	if (m_currentMode == AnimationMode::Disappear)
	{
		for (auto &tab : m_tabs)
		{
			tab->makeTabTransparent(7,2);
		}


		for (auto &upgrade1 : m_upgradeItems)
		{
			for (auto &upgrade2 : upgrade1)
			{
				upgrade2->makeItemTransparent(7, 2);
			}
		}
		m_heading.makeTransparent(7, 2);
		m_coinsText.makeTransparent(7, 2);

		//changes the screen and resets the store

		if (m_cumalativeTime.asSeconds() >= 2)
		{
			//changes the screens and resets it
			switch (m_currentScreen)
			{
			case 1:
				m_game.m_currentMode = GameMode::MainMenu;
				reset();
				break;
			case 2:
				m_game.m_currentMode = GameMode::Equipment;
				reset();
				break;
			default:
				break;
			}
		}
	}
}

/// <summary>
/// renders the store screen
/// </summary>
/// <param name="t_window"></param>
void Store::render(sf::RenderWindow & t_window)
{
	t_window.clear();

	t_window.draw(m_bg);
	
	m_heading.render(t_window);
	m_coinsText.render(t_window);

	t_window.draw(m_coinsSprite);

	for (auto &tab : m_tabs)
	{
		tab->render(t_window);
	}

	for (auto & upgrade1:m_upgradeItems)
	{
		for (auto &up:upgrade1)
		{
			up->render(t_window);
		}
	}

	t_window.display();
}

/// <summary>
/// loads the background image
/// </summary>
void Store::loadAssets()
{
	m_bg.setTexture(m_tex);
	m_bg.setPosition(sf::Vector2f(0.0f, -300.0f));
	m_bg.setScale(1.0f, 0.8f);

	m_coinsSprite.setTexture(m_coinsTex);
	m_coinsSprite.setScale(0.5f, 0.5f);
	m_coinsSprite.setOrigin(sf::Vector2f{ m_coinsSprite.getGlobalBounds().width / 2, m_coinsSprite.getGlobalBounds().height / 2 });
	m_coinsSprite.setPosition(sf::Vector2f{ m_coinsText.getPosition().x + m_coinsText.getGlobalBounds().width - 20.0f,
		m_coinsText.getPosition().y + m_coinsText.getGlobalBounds().height / 2});
}

/// <summary>
/// initilises the tabs and the items for this screen
/// </summary>
void Store::loadTabs()
{
	std::shared_ptr<UpgradesTab> temp;
	for (int i = 0; i < s_MAX_TABS; i++)
	{
		temp = std::make_shared<UpgradesTab>(m_game, 30, TAB_NAMES[i], sf::Vector2f(TAB_POSITION.x + (400.0f * i),TAB_POSITION.y), true);
		m_tabs.push_back(temp);
		m_tabs[i]->changeTextProperties(true, true, true);
	}

	std::vector<std::shared_ptr<UpgradeItem>> itemList;
	int index = 0;
	for (int i = 0; i < s_MAX_TABS; i++)
	{
		for (UpgradesData const & upgradeData : m_game.m_levelData.m_upgrades)
		{
			if (upgradeData.m_type == UPGRADE_NAME[i])
			{
				itemList.push_back(std::make_shared<UpgradeItem>(m_game.m_levelData, upgradeData.m_name, upgradeData.m_price, upgradeData.m_modifier,
					sf::Vector2f(UPGRADE_POSITION[i].x, UPGRADE_POSITION[i].y + (index * 100.0f)), sf::Color::White, true));
				index++;
			}
		}
		m_upgradeItems.push_back(itemList);
		itemList.clear();
		index = 0;
	}
}

void Store::setup()
{
	m_coinsText.setColour(sf::Color::Cyan);
	m_heading.setColour(sf::Color::Cyan);
}

/// <summary>
/// resets the store screen
/// </summary>
void Store::reset()
{
	m_currentMode = AnimationMode::Appear;
	m_currentScreen = 0;
	m_cumalativeTime = sf::seconds(0);
}

/// <summary>
/// highlights the current box and checks if its bought
/// </summary>
void Store::highlightBoxes()
{
	//clears all the selected boxes
	for (auto &upgrade1 : m_upgradeItems)
	{
		for (auto &upgrade2 : upgrade1)
		{
			upgrade2->highlighted(false);
		}
	}
	//sets the current box to be selected
	m_upgradeItems[m_currentTab][m_currentItem]->highlighted(true);

	m_tabTimer++;
	m_itemTimer++;

	//moves the selected box
	if (m_game.m_controller.m_currentState.DpadDown && m_itemTimer >= 15 ||
		m_game.m_controller.m_currentState.LeftThumbStick.y > 50 && m_itemTimer >= 15)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_currentItem = (m_currentItem + 1) % 5;
		m_itemTimer = 0;
	}
	else if (m_game.m_controller.m_currentState.DpadUp && m_itemTimer >= 15 ||
		m_game.m_controller.m_currentState.LeftThumbStick.y < -50 && m_itemTimer >= 15)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_currentItem = (m_currentItem == 0 ? (5 - 1) : m_currentItem - 1);
		m_itemTimer = 0;
	}

	if (m_game.m_controller.m_currentState.RB ||
		m_game.m_controller.m_currentState.DpadRight && m_tabTimer >= 15 ||
		m_game.m_controller.m_currentState.LeftThumbStick.x > 50 && m_tabTimer >= 15)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_currentTab = (m_currentTab + 1) % s_MAX_TABS;
		m_itemTimer = 0;
		m_tabTimer = 0;
	}
	else if (m_game.m_controller.m_currentState.LB ||
		m_game.m_controller.m_currentState.DpadLeft && m_tabTimer >= 15 ||
		m_game.m_controller.m_currentState.LeftThumbStick.x < -50 && m_tabTimer >= 15)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_currentTab = (m_currentTab == 0 ? (s_MAX_TABS - 1) : m_currentTab - 1);
		m_itemTimer = 0;
		m_tabTimer = 0;
	}

	//purchases the current item 
	if (m_game.m_controller.m_currentState.A && !m_upgradeItems[m_currentTab][m_currentItem]->getPurchase()
		&& m_game.m_currency >= m_upgradeItems[m_currentTab][m_currentItem]->getPrice())
	{
		if (s_audioActive && s_sfxActive)
		{
			m_buySound.play();
		}
		m_upgradeItems[m_currentTab][m_currentItem]->purchase(true);
		m_equipmentScreen->passToEquip(m_currentTab, *m_upgradeItems[m_currentTab][m_currentItem]);
		m_game.m_currency -= m_upgradeItems[m_currentTab][m_currentItem]->getPrice();
	}
}
