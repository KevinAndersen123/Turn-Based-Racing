#include "Equipment.h"

Equipment::Equipment(Game & t_game, std::shared_ptr<GamePlay> t_gameplayScreen,sf::Sound & t_selectSound, sf::Sound & t_backSound,sf::Sound &t_moveSound) :
	m_game(t_game),
	m_currentScreen(0),
	m_currentTab(0),
	m_currentItem(0),
	m_itemTimer(0),
	m_tabTimer(0),
	m_inputTimer(10),
	m_gameplayScreen(t_gameplayScreen),
	m_currencyText(t_game.m_levelData,40,"Coins: ",sf::Vector2f{100.0f,50.0f},true),
	m_title(t_game.m_levelData, 100, "Garage", sf::Vector2f{ 750.0f,50.0f }, true),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_neonFont]),
	m_backSound(t_backSound),
	m_selectSound( t_selectSound),
	m_moveSound(t_moveSound),
	m_statsText{
	Label(t_game.m_levelData,30,"WEIGHT: ",sf::Vector2f{ 1020.0f,700.0f},false),
	Label(t_game.m_levelData,30,"SPEED: ",sf::Vector2f{ 1020.0f,750.0f },false),
	Label(t_game.m_levelData,30,"BRAKE: ",sf::Vector2f{ 1020.0f,800.0f },false),
	Label(t_game.m_levelData,30,"ACCELERATION: ",sf::Vector2f{ 970.0f,850.0f },false) },
	m_coinsTex(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_coinID]),
	m_backgroundTex(ResourceManager::m_textureHolder[m_game.m_levelData.m_myTextures.m_bGTwoID]),
	m_outlineTex(ResourceManager::m_textureHolder[m_game.m_levelData.m_myTextures.m_equipmentOutlineID]),
	m_wheelTex(ResourceManager::m_textureHolder[m_game.m_levelData.m_myTextures.m_equipmentWheelID])
{
	m_colour = m_gameplayScreen->m_player.getColour();
	loadTabs();
	setupSprites();
	setupText();
}

Equipment::~Equipment()
{
}

void Equipment::update(sf::Time t_deltaTime)
{
	m_cumalativeTime += t_deltaTime;
	m_currencyText.setString("Coins: " + std::to_string(m_game.m_currency));
	m_coinSprite.setPosition(sf::Vector2f{ m_currencyText.getPosition().x + m_currencyText.getGlobalBounds().width - 20.0f, 
		m_currencyText.getPosition().y + m_currencyText.getGlobalBounds().height / 2 });

	updateStatBars();


	if (m_currentMode == AnimationMode::Appear)
	{
		m_currencyText.makeOpaque(7, 2);
		m_title.makeOpaque(7, 2);
		for (auto &tab : m_tabs)
		{
			tab->makeTabOpaque(7,2);
		}
		for (auto & upgrade1 : m_upgradeItems)
		{
			for (auto &up : upgrade1)
			{
				up->makeItemOpaque(7, 2);
			}
		}
		//if (m_wheelSprite.getColor().a < 255)
		{
			m_wheelSprite.setColor(m_wheelSprite.getColor() + sf::Color{ 0,0,0,10 });
			m_outline.setColor(m_outline.getColor() + sf::Color{ 0,0,0,10 });
			m_statAdd.setFillColor(m_statAdd.getFillColor() + sf::Color{ 0,0,0,10 });
			for (int i = 0; i < s_MAX_STATS; i++)
			{
				m_statsText[i].makeOpaque(7, 2);
				m_statBars[i].setFillColor(m_statBars[i].getFillColor() + sf::Color{ 0,0,0,10 });
			}
		}

		if(m_cumalativeTime.asSeconds() > 2)
		{
			m_currentMode = AnimationMode::None;
		}
	}

	if (m_currentMode == AnimationMode::None)
	{
		highlightBoxes();
		turnWheel();
		if (m_game.m_controller.m_currentState.B)
		{
			if (s_audioActive && s_sfxActive)
			{
				m_backSound.play();
			}
			m_currentMode = AnimationMode::Disappear;
			m_currentScreen = 1;
			m_cumalativeTime = sf::seconds(0);
		}
		else if (m_game.m_controller.m_currentState.Y)
		{
			if (s_audioActive && s_sfxActive)
			{
				m_selectSound.play();
			}
			m_currentMode = AnimationMode::Disappear;
			m_currentScreen = 2;
			m_cumalativeTime = sf::seconds(0);
		}
	}

	if (m_currentMode == AnimationMode::Disappear)
	{
		m_currencyText.makeTransparent(7, 2);
		m_title.makeTransparent(7, 2);
		for (auto &tab : m_tabs)
		{
			tab->makeTabTransparent(7, 2);
		}
		for (auto & upgrade1 : m_upgradeItems)
		{
			for (auto &up : upgrade1)
			{
				up->makeItemTransparent(7, 2);
			}
		}

		m_wheelSprite.setColor(m_wheelSprite.getColor() - sf::Color{ 0,0,0,10 });
		m_outline.setColor(m_outline.getColor() - sf::Color{ 0,0,0,10 });
		m_statAdd.setFillColor(m_statAdd.getFillColor() - sf::Color{ 0,0,0,10 });
		for (int i = 0; i < s_MAX_STATS; i++)
		{
			m_statsText[i].makeTransparent(7, 2);
			m_statBars[i].setFillColor(m_statBars[i].getFillColor() - sf::Color{ 0,0,0,10 });
		}

		if (m_cumalativeTime.asSeconds() > 2)
		{
			//changes the screens and resets it
			switch (m_currentScreen)
			{
			case 1:
				m_game.m_currentMode = GameMode::MainMenu;
				reset();
				break;
			case 2:
				m_game.m_currentMode = GameMode::Store;
				reset();
				break;
			default:
				break;
			}
		}
	}
}

void Equipment::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color::Black);
	t_window.draw(m_background);
	m_currencyText.render(t_window);
	m_title.render(t_window);
	t_window.draw(m_coinSprite);

	for(int i = s_MAX_TABS - 1; i >= 0; i--)
	{
		if (i != m_currentTab)
		{
			m_tabs[i]->render(t_window);
		}
	}
	m_tabs[m_currentTab]->render(t_window);

	for (int i = m_upgradeItems[m_currentTab].size() - 1; i >= 0; i--)
	{
		m_upgradeItems[m_currentTab][i]->render(t_window);
	}

	for (int i = 0; i < s_MAX_STATS; i++)
	{
		m_statsText[i].render(t_window);
		t_window.draw(m_statBars[i]);
	}
	t_window.draw(m_statAdd);

	t_window.draw(m_outline);
	t_window.draw(m_wheelSprite);

	t_window.display();
}

void Equipment::passToEquip(int t_tab, UpgradeItem t_upgrade)
{
	m_currentItem = m_upgradeItems[t_tab].size();
	m_upgradeItems[t_tab].push_back(std::make_shared<UpgradeItem>(t_upgrade));
	m_upgradeItems[t_tab][m_currentItem]->setPosition(sf::Vector2f(EQUIPMENT_POSITION[t_tab].x, EQUIPMENT_POSITION[t_tab].y + (m_currentItem * 100.0f)));
	for (int i =0;i< m_upgradeItems.size();i++)
	{
		if (m_upgradeItems[i].size() > 0)
		{
			m_currentTab = i;
			m_currentItem = 0;
			break;
		}
	}
	for (int i = 0; i < m_upgradeItems[t_tab].size(); i++)
	{
		m_upgradeItems[t_tab][i]->purchase(false);
	}
}

void Equipment::loadTabs()
{
	std::shared_ptr<UpgradesTab> temp;
	for (int i = 0; i < s_MAX_TABS; i++)
	{
		temp = std::make_shared<UpgradesTab>(m_game, 30, TAB_NAMES[i], sf::Vector2f(TAB_POSITION.x + (150.0f * i), TAB_POSITION.y), true);
		m_tabs.push_back(temp);
		m_tabs[i]->changeTextProperties(true, true, true);
	}

	std::vector<std::shared_ptr<UpgradeItem>> itemList;
	for (int i = 0; i < s_MAX_TABS; i++)
	{
		m_upgradeItems.push_back(itemList);
	}
}

void Equipment::setupText()
{
	m_currencyText.setColour(sf::Color{ 0, 255, 255 , 0});
	m_title.setColour(sf::Color{ 0, 255, 255 , 0 });
}

void Equipment::setupSprites()
{
	m_background.setTexture(m_backgroundTex);
	m_background.setPosition(sf::Vector2f{ 0.0f,0.0f });

	m_coinSprite.setTexture(m_coinsTex);
	m_coinSprite.setOrigin(sf::Vector2f{ m_coinSprite.getGlobalBounds().width / 2, m_coinSprite.getGlobalBounds().height / 2 });
	m_coinSprite.setScale(sf::Vector2f{0.5f,0.5f});
	m_coinSprite.setPosition(sf::Vector2f{ m_currencyText.getPosition().x + m_currencyText.getGlobalBounds().width, 
		m_currencyText.getPosition().y + m_currencyText.getGlobalBounds().height / 2 });

	m_wheelSprite.setTexture(m_wheelTex);
	m_wheelSprite.setOrigin(m_wheelSprite.getGlobalBounds().width / 2, m_wheelSprite.getGlobalBounds().height / 2);
	m_wheelSprite.setPosition(sf::Vector2f{ 1200.0f,350.0f });
	m_wheelSprite.setColor(m_wheelSprite.getColor() - sf::Color{ 0,0,0,255 });

	m_outline.setTexture(m_outlineTex);
	m_outline.setPosition(sf::Vector2f{ 1135.0f,410.0f });
	m_outline.setColor(m_outline.getColor() - sf::Color{ 0,0,0,255 });

	for (int i = 0; i < s_MAX_STATS; i++)
	{
		m_statBars[i].setFillColor((sf::Color{ 0, 255, 255, 0 }));
		m_statBars[i].setPosition(sf::Vector2f{ 1100.0f,705.0f + (50.0f * i) });
	}
	m_statBars[0].setSize(sf::Vector2f{ m_gameplayScreen->m_player.MAX_THROTTLE[m_colour] * 100,10.0f });
	m_statBars[1].setSize(sf::Vector2f{ m_gameplayScreen->m_player.TOP_SPEED[m_colour] / 2,10.0f });
	m_statBars[2].setSize(sf::Vector2f{ m_gameplayScreen->m_player.MASS[m_colour] * 500,10.0f });
	m_statBars[3].setSize(sf::Vector2f{ m_gameplayScreen->m_player.BRAKE_FORCE[m_colour] * 100,10.0f });

	m_statAdd.setFillColor(sf::Color{ 255, 0, 255, 0 });
	m_statAdd.setSize(sf::Vector2f{ 0.0f,0.0f });
}

void Equipment::reset()
{
	m_currentMode = AnimationMode::Appear;
	m_currentScreen = 0;
	m_cumalativeTime = sf::seconds(0);
}

void Equipment::highlightBoxes()
{
	//clears all the secelted boxes
	for (auto &upgrade1 : m_upgradeItems)
	{
		for (auto &upgrade2 : upgrade1)
		{
			upgrade2->highlighted(false);
		}
	}
	if (m_upgradeItems[m_currentTab].size() > 0)
	{
		m_currentMaxTab = m_upgradeItems.size();
		m_currentMaxItems = m_upgradeItems[m_currentTab].size();
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
			m_currentItem = (m_currentItem + 1) % m_currentMaxItems;
			m_itemTimer = 0;
		}
		else if (m_game.m_controller.m_currentState.DpadUp && m_itemTimer >= 15 ||
			m_game.m_controller.m_currentState.LeftThumbStick.y < -50 && m_itemTimer >= 15)
		{
			if (s_audioActive && s_sfxActive)
			{
				m_moveSound.play();
			}
			m_currentItem = (m_currentItem == 0 ? (m_currentMaxItems - 1) : m_currentItem - 1);
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
			for (int i = 0; i < s_MAX_TABS; i++)
			{
				if (m_upgradeItems[(m_currentTab + (i + 1)) % m_currentMaxTab].size() > 0)
				{
					m_currentTab = (m_currentTab + (i + 1)) % m_currentMaxTab;
					m_currentItem = 0;
					m_itemTimer = 0;
					m_tabTimer = 0;
					break;
				}
			}
		}
		else if (m_game.m_controller.m_currentState.LB ||
			m_game.m_controller.m_currentState.DpadLeft && m_tabTimer >= 15 ||
			m_game.m_controller.m_currentState.LeftThumbStick.x < -50 && m_tabTimer >= 15)
		{
			if (s_audioActive && s_sfxActive)
			{
				m_moveSound.play();
			}
			for (int i = 0; i < s_MAX_TABS; i++)
			{
				m_currentTab--;
				if (m_currentTab < 0)
				{
					m_currentTab = s_MAX_TABS - 1;
				}
				if (m_upgradeItems[m_currentTab].size() > 0)
				{
					m_currentItem = 0;
					m_itemTimer = 0;
					m_tabTimer = 0;
					break;
				}
			}
		}
		if (m_game.m_controller.m_currentState.A && !m_upgradeItems[m_currentTab][m_currentItem]->getPurchase())
		{
			m_upgradeItems[m_currentTab][m_currentItem]->purchase(true);
			m_mods[m_currentTab].x += m_upgradeItems[m_currentTab][m_currentItem]->m_modifier * 10.0f;
		}
	}
}

void Equipment::turnWheel()
{
	m_inputTimer--;
	if (m_game.m_controller.m_currentState.LTrigger > 20 && m_inputTimer < 0)
	{
		m_inputTimer = 10;
		m_wheelSprite.rotate(-90);
		m_colour++;
		if (m_colour > 3)
		{
			m_colour = 0;
		}
		m_gameplayScreen->m_player.changeColour(m_colour);
	}
	if (m_game.m_controller.m_currentState.RTrigger > 20 && m_inputTimer < 0)
	{
		m_inputTimer = 10;
		m_wheelSprite.rotate(90);
		m_colour--;
		if (m_colour < 0)
		{
			m_colour = 3;
		}
		m_gameplayScreen->m_player.changeColour(m_colour);
	}
}

void Equipment::updateStatBars()
{
	m_statBars[0].setSize(sf::Vector2f{ m_gameplayScreen->m_player.MAX_THROTTLE[m_colour] * 100,10.0f } + m_mods[0]);
	m_statBars[1].setSize(sf::Vector2f{ m_gameplayScreen->m_player.TOP_SPEED[m_colour] / 2,10.0f } + m_mods[1]);
	m_statBars[2].setSize(sf::Vector2f{ m_gameplayScreen->m_player.MASS[m_colour] * 500,10.0f } + m_mods[2]);
	m_statBars[3].setSize(sf::Vector2f{ m_gameplayScreen->m_player.BRAKE_FORCE[m_colour] * 100,10.0f } + m_mods[3]);

	if (m_upgradeItems[m_currentTab].size() > 0)
	{
		switch (m_currentTab)
		{
		case 0:
			if (!m_upgradeItems[m_currentTab][m_currentItem]->getPurchase())
			{
				m_statAdd.setSize(sf::Vector2f{ m_upgradeItems[m_currentTab][m_currentItem]->m_modifier * 10.0f, 10.0f });
			}
			else
			{
				m_statAdd.setSize(sf::Vector2f{ 0.0f,10.0f });
			}
			m_statAdd.setPosition(m_statBars[0].getPosition() + sf::Vector2f{ m_statBars[0].getGlobalBounds().width,0.0f });
			break;


		case 1:
			if (!m_upgradeItems[m_currentTab][m_currentItem]->getPurchase())
			{
				m_statAdd.setSize(sf::Vector2f{ m_upgradeItems[m_currentTab][m_currentItem]->m_modifier * 10.0f, 10.0f });
			}
			else
			{
				m_statAdd.setSize(sf::Vector2f{ 0.0f,10.0f });
			}
			m_statAdd.setPosition(m_statBars[1].getPosition() + sf::Vector2f{ m_statBars[1].getGlobalBounds().width,0.0f });
			break;


		case 2:
			if (!m_upgradeItems[m_currentTab][m_currentItem]->getPurchase())
			{
				m_statAdd.setSize(sf::Vector2f{ m_upgradeItems[m_currentTab][m_currentItem]->m_modifier * 10.0f, 10.0f });
			}
			else
			{
				m_statAdd.setSize(sf::Vector2f{ 0.0f,10.0f });
			}
			m_statAdd.setPosition(m_statBars[2].getPosition() + sf::Vector2f{ m_statBars[2].getGlobalBounds().width,0.0f });
			break;


		case 3:
			if (!m_upgradeItems[m_currentTab][m_currentItem]->getPurchase())
			{
				m_statAdd.setSize(sf::Vector2f{ m_upgradeItems[m_currentTab][m_currentItem]->m_modifier * 10.0f, 10.0f });
			}
			else
			{
				m_statAdd.setSize(sf::Vector2f{ 0.0f,10.0f });
			}
			m_statAdd.setPosition(m_statBars[3].getPosition() + sf::Vector2f{ m_statBars[3].getGlobalBounds().width,0.0f });
			break;
		
		
		default:
			break;
		}
	}
}
