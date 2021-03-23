#include "UpgradeItem.h"


/// <summary>
/// sets up the upgrade item with a label and a box
/// </summary>
/// <param name="t_font"></param>
/// <param name="t_data"></param>
/// <param name="t_string"></param>
/// <param name="t_price"></param>
/// <param name="t_modifier"></param>
/// <param name="t_position"></param>
/// <param name="t_color"></param>
/// <param name="t_transparent"></param>
/// <param name="t_highlighted"></param>
UpgradeItem::UpgradeItem(LevelData &t_data, std::string t_string, int t_price, int t_modifier,
								sf::Vector2f t_position, sf::Color t_color, bool t_transparent, bool t_highlighted) :
	Button(t_position, sf::Vector2f(250, 70), t_color, t_transparent),
	Label(t_data, 30, t_string + "\n+" + std::to_string(t_modifier) + "    " + std::to_string(t_price), t_position + sf::Vector2f(90.0f, 28.5f), t_transparent),
	m_data(t_data),
	m_price(t_price),
	m_modifier(t_modifier),
	m_purchased(false),
	m_highlighted(false),
	m_texture(ResourceManager::m_textureHolder[t_data.m_myTextures.m_coinID])
{
	setupAssets();
}


UpgradeItem::~UpgradeItem()
{
}

/// <summary>
/// renders the upgrade item
/// </summary>
/// <param name="t_window"></param>
void UpgradeItem::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_box);
	t_window.draw(m_text);
	t_window.draw(m_coin);
}

/// <summary>
/// makes the upgrade item visable
/// and return true when it is fully visable
/// </summary>
/// <param name="t_rate"></param>
/// <param name="t_time"></param>
/// <returns>true when visable</returns>
bool UpgradeItem::makeItemOpaque(int t_rate, int t_time)
{
	m_rateOfOpaqueness++;
	if (m_rateOfOpaqueness >= t_time)
	{
		if (m_box.getOutlineColor().a < 255)
		{
			m_box.setOutlineColor(m_box.getOutlineColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			if (m_purchased)
			{
				m_box.setFillColor(m_box.getFillColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			}
			m_coin.setColor(m_coin.getColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_text.setFillColor(m_text.getFillColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_rateOfOpaqueness = 0;
		}
		else
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// makes the upgrade item inviable
/// and returns true when it is invisable
/// </summary>
/// <param name="t_rate"></param>
/// <param name="t_time"></param>
/// <returns>true when invisable</returns>
bool UpgradeItem::makeItemTransparent(int t_rate, int t_time)
{
	m_rateOfTransparency++;
	if (m_rateOfTransparency >= t_time)
	{
		if (m_box.getOutlineColor().a > 0)
		{
			m_box.setOutlineColor(m_box.getOutlineColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			if (m_purchased)
			{
				m_box.setFillColor(m_box.getFillColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			}
			m_coin.setColor(m_coin.getColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
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
/// checks what color it should be depending on its status
/// </summary>
/// <param name="t_highlighted"></param>
void UpgradeItem::highlighted(bool t_highlighted)
{
	m_highlighted = t_highlighted;
	if (m_highlighted && !m_purchased)
	{
		m_box.setOutlineColor(s_SELECTED);
	}
	else if (!m_highlighted && !m_purchased)
	{
		m_box.setOutlineColor(s_UN_SELECTED);
	}
	else if(!m_highlighted && m_purchased)
	{
		m_box.setOutlineColor(s_BOUGHT);
	}
	else if (m_highlighted && m_purchased)
	{
		m_box.setOutlineColor(s_INVALID);
	}
}

/// <summary>
/// buys the upgrade item and make the background darker
/// </summary>
void UpgradeItem::purchase(bool t_bool)
{
	m_purchased = t_bool;
	if (m_purchased)
	{
		m_box.setFillColor(m_box.getFillColor() + sf::Color(0, 0, 0, 255));
	}
}

/// <summary>
/// checks if the item is purchased
/// </summary>
/// <returns>m_purchased</returns>
bool UpgradeItem::getPurchase()
{
	return m_purchased;
}

int UpgradeItem::getPrice()
{
	return m_price;
}

void UpgradeItem::setPosition(sf::Vector2f t_position)
{
	m_box.setPosition(t_position);
	m_text.setPosition(t_position + sf::Vector2f(90.0f, 28.5f));
	m_coin.setPosition(static_cast<float>(m_box.getPosition().x + m_box.getGlobalBounds().width / 1.4), static_cast<float>(m_box.getPosition().y + 5));
}

/// <summary>
/// sets up the upgrade items assets
/// </summary>
void UpgradeItem::setupAssets()
{
	m_coin.setTexture(m_texture);
	m_coin.setScale(sf::Vector2f(0.6f, 0.6f));
	m_coin.setPosition(sf::Vector2f(m_box.getPosition().x + m_box.getGlobalBounds().width/1.4, m_box.getPosition().y + 5));
	if (m_transparent)
	{
		m_coin.setColor(m_coin.getColor() - sf::Color{ 0,0,0,255 });
		m_box.setOutlineColor(m_box.getOutlineColor() - sf::Color{ 0,0,0,255 });
	}
}