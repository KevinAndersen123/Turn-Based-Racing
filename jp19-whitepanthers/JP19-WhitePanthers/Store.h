#ifndef STORE
#define STORE

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Game.h"
#include "Globals.h"
#include "UpgradesTab.h"
#include "UpgradeItem.h"
#include "LevelLoader.h"
#include "Label.h"
#include "Equipment.h"

class Equipment;
class Game;

class Store
{
public:
	Store(Game & t_game, std::shared_ptr<Equipment> t_equipment, sf::Sound & t_selectSound, sf::Sound & t_backSound, sf::Sound &t_moveSound, sf::Sound &t_buySound);
	~Store();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);

private:
	std::shared_ptr<Equipment> m_equipmentScreen;

	std::vector<std::vector<std::shared_ptr<UpgradeItem>>> m_upgradeItems; //holds the upgrdade items

	Label m_heading; //The store title

	sf::Time m_cumalativeTime;

	int m_currentScreen; //the screen it will change to 
	int m_currentTab; //the current tab that is selected
	int m_currentItem; //the current item that is selected
	int m_tabTimer; //time between switching tabs
	int m_itemTimer; //time between switching items

	AnimationMode m_currentMode; //The current mode of animation

	std::vector<std::shared_ptr<UpgradesTab>> m_tabs; //holds the upgrade tabs

	sf::Font &m_font;
	Game &m_game;
	sf::Sound &m_selectSound;
	sf::Sound &m_backSound;
	sf::Sound &m_moveSound;
	sf::Sound &m_buySound;

	//background sprite
	sf::Sprite m_bg;
	sf::Texture &m_tex;

	sf::Sprite m_coinsSprite;
	sf::Texture &m_coinsTex;

	Label m_coinsText;

	void loadAssets();
	void loadTabs();
	void setup();
	void reset();
	void highlightBoxes();
};

#endif //!STORE