#include "UpgradesTab.h"

/// <summary>
/// sets up a basic upgrade tab with no label
/// </summary>
/// <param name="t_game"></param>
/// <param name="t_font"></param>
UpgradesTab::UpgradesTab(Game & t_game) :
	Label(t_game.m_levelData),
	m_game(t_game),
	m_font(ResourceManager::m_fontHolder[m_levelData.m_myFonts.m_neonFont]),
	m_tabPosition(sf::Vector2f(300.0,300.0f)),
	m_transparent(false),
	m_texture(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_tabID])
{
	loadAssets();
}


/// <summary>
/// sets up the upgrade tab with a label
/// </summary>
/// <param name="t_game"></param>
/// <param name="t_font"></param>
/// <param name="t_size"></param>
/// <param name="t_string"></param>
/// <param name="t_position"></param>
/// <param name="t_transparent"></param>
UpgradesTab::UpgradesTab(Game & t_game, int t_size, std::string t_string, sf::Vector2f t_position, bool t_transparent) :
	Label(t_game.m_levelData, t_size, t_string,t_position-sf::Vector2f(90.0f,315.0f), t_transparent),
	m_game(t_game),
	m_font(ResourceManager::m_fontHolder[m_levelData.m_myFonts.m_neonFont]),
	m_tabPosition(t_position),
	m_transparent(t_transparent),
	m_texture(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_tabID])
{
	loadAssets();
}

UpgradesTab::~UpgradesTab()
{
}

/// <summary>
/// renders the upgrade tab
/// </summary>
/// <param name="t_window"></param>
void UpgradesTab::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_tab);
	t_window.draw(m_text);
}


/// <summary>
/// makes the upgrade tab invisable
/// </summary>
/// <param name="t_rate"></param>
/// <param name="t_time"></param>
/// <returns>true when invisable</returns>
bool UpgradesTab::makeTabTransparent(int t_rate, int t_time)
{
	m_rateOfTransparency++;
	if (m_rateOfTransparency >= t_time)
	{
		if (m_tab.getColor().a > 0)
		{
			m_tab.setColor(m_tab.getColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_text.setFillColor(m_text.getFillColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_rateOfTransparency = 0;
		}
		else
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// makes the upgrades tab visable
/// </summary>
/// <param name="t_rate"></param>
/// <param name="t_time"></param>
/// <returns>true when tab is invisable</returns>
bool UpgradesTab::makeTabOpaque(int t_rate, int t_time)
{
	m_rateOfOpaqueness++;
	if (m_rateOfOpaqueness >= t_time)
	{
		if (m_tab.getColor().a < 255)
		{
			m_text.setFillColor(m_text.getFillColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_tab.setColor(m_tab.getColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_rateOfOpaqueness = 0;
		}
		else
		{
			return true;
		}
	}
	return false;
}

void UpgradesTab::setPosition(sf::Vector2f t_position)
{
	m_tabPosition = t_position;
	m_position = m_tabPosition - sf::Vector2f(90.0f, 300.0f);
	m_text.setPosition(m_position);
	m_tab.setPosition(m_tabPosition);
}

sf::Vector2f UpgradesTab::getPosition()
{
	return m_tabPosition;
}

/// <summary>
/// loads the assets for the upgrade tab
/// </summary>
void UpgradesTab::loadAssets()
{
	m_tab.setTexture(m_texture);
	m_tab.setOrigin(m_tab.getGlobalBounds().width / 2, m_tab.getGlobalBounds().height / 2);
	m_tab.setPosition(m_tabPosition);
	m_tab.setScale(1.1f, 1.5f);
	if (m_transparent)
	{
		m_tab.setColor(m_tab.getColor() - sf::Color{ 0,0,0,255 });
	}
}
