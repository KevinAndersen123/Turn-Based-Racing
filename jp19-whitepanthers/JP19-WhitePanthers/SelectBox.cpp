#include "SelectBox.h"

SelectBox::SelectBox(LevelData &t_level, bool t_transparent, sf::Vector2f t_buttonSize, sf::Vector2f t_pos,
	sf::Color t_colour, bool t_active, bool t_highlight) :
	Button(t_pos, t_buttonSize, t_colour, t_transparent),
	Label(t_level, t_transparent),
	m_active(t_active),
	m_highlight(t_highlight)
{
	setupShape();
}

SelectBox::SelectBox(LevelData &t_level, int t_size, sf::Vector2f t_buttonSize, std::string t_string, bool t_transparent,
	sf::Vector2f t_pos, sf::Color t_colour, bool t_active, bool t_highlight) :
	Button(t_pos, t_buttonSize, t_colour, t_transparent),
	Label(t_level, t_size, t_string, t_pos, t_transparent),
	m_active(t_active),
	m_highlight(t_highlight)
{
	setupShape();
}

SelectBox::~SelectBox()
{
}

void SelectBox::draw(sf::RenderWindow & t_window)
{
	t_window.draw(m_box);
	if (m_active)
	{
		t_window.draw(m_selected);
	}
	t_window.draw(m_text);
}

bool SelectBox::makeCheckboxOpaque(int t_rate, int t_time)
{
	m_rateOfOpaqueness++;
	if (m_rateOfOpaqueness >= t_time)
	{
		if (m_box.getOutlineColor().a < 255)
		{
			m_box.setOutlineColor(m_box.getOutlineColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_selected.setFillColor(m_selected.getFillColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_text.setFillColor(m_text.getFillColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
		}
		else if (m_text.getFillColor().a >= 225)
		{
			return true;
		}
		m_rateOfOpaqueness = 0;
	}
	return false;
}

bool SelectBox::makeCheckboxTransparent(int t_rate, int t_time)
{
	m_rateOfTransparency++;
	if (m_rateOfTransparency >= t_time)
	{
		if (m_box.getOutlineColor().a > 0)
		{
			m_box.setOutlineColor(m_box.getOutlineColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_selected.setFillColor(m_selected.getFillColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_text.setFillColor(m_text.getFillColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
		}
		else if (m_text.getFillColor().a <= 0)
		{
			return true;
		}
		m_rateOfTransparency = 0;
	}
	return false;
}

void SelectBox::setHighlighted(bool t_highlighted)
{
	m_highlight = t_highlighted;
	if (m_highlight)
	{
		m_box.setOutlineColor(s_SELECTED);
	}
	else
	{
		m_box.setOutlineColor(s_UN_SELECTED);
	}
}

bool SelectBox::getHighlighted()
{
	return m_highlight;
}

void SelectBox::setActive(bool t_active)
{
	m_active = t_active;
}

bool SelectBox::getActive()
{
	return m_active;
}

void SelectBox::setupShape()
{
	m_selected.setSize(m_buttonSize - sf::Vector2f{ 10.0f,10.0f });
	m_selected.setOrigin(m_selected.getGlobalBounds().width / 2, m_selected.getGlobalBounds().height / 2);
	m_selected.setPosition(m_buttonPosition.x + m_buttonSize.x / 2, m_buttonPosition.y + m_buttonSize.y / 2);
	if (m_transparentButton)
	{
		m_selected.setFillColor(s_SELECTED - sf::Color{ 0,0,0,255 });
	}
	else
	{
		m_selected.setFillColor(s_SELECTED);
	}
	m_text.setPosition(m_buttonPosition.x - m_box.getGlobalBounds().width - (m_text.getGlobalBounds().width / 2), m_buttonPosition.y + 10.0f);
}