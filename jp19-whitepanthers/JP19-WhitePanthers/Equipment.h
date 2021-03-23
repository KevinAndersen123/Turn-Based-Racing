#ifndef EQUIPMENT
#define EQUIPMENT

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "Game.h"
#include "UpgradesTab.h"
#include "UpgradeItem.h"
#include "Label.h"
#include "GamePlay.h"

class GamePlay;
class Game;

class Equipment
{
public:
	Equipment(Game & t_game,std::shared_ptr<GamePlay> t_gameplayScreen, sf::Sound & t_selectSound, sf::Sound & t_backSound,sf::Sound &t_moveSound);
	~Equipment();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);
	void passToEquip(int t_tab, UpgradeItem t_upgrade);
private:
	std::vector<std::shared_ptr<UpgradesTab>> m_tabs; //holds the upgrade tabs
	std::vector<std::vector<std::shared_ptr<UpgradeItem>>> m_upgradeItems;

	AnimationMode m_currentMode{ AnimationMode::Appear };

	std::shared_ptr<GamePlay>m_gameplayScreen;

	int m_currentScreen;
	int m_currentTab;
	int m_currentItem; 
	int m_tabTimer; 
	int m_itemTimer; 
	int m_currentMaxTab;
	int m_currentMaxItems;

	sf::Font &m_font;
	Game &m_game;

	Label m_title;
	Label m_currencyText;

	sf::Sound &m_selectSound;
	sf::Sound &m_backSound;
	sf::Sound &m_moveSound;

	sf::Sprite m_wheelSprite;
	sf::Texture &m_wheelTex;
	sf::Sprite m_outline;
	sf::Texture &m_outlineTex;
	int m_inputTimer;
	int m_colour;

	static const int s_MAX_STATS = 4;
	Label m_statsText[s_MAX_STATS];
	sf::RectangleShape m_statBars[s_MAX_STATS];
	sf::RectangleShape m_statAdd;
	sf::Vector2f m_mods[s_MAX_STATS];

	sf::Sprite m_coinSprite;
	sf::Texture &m_coinsTex;

	sf::Time m_cumalativeTime;

	sf::Sprite m_background;
	sf::Texture &m_backgroundTex;

	void loadTabs();
	void setupText();
	void setupSprites();
	void reset();
	void highlightBoxes();
	void turnWheel();
	void updateStatBars();
};

#endif //!EQUIPMENT