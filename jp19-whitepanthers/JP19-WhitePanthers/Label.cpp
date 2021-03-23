#include "Label.h"

Label::Label(LevelData &t_level, int t_size, std::string t_labelText, sf::Vector2f t_pos, bool t_transparent) :
	m_levelData(t_level),
	m_charSize(t_size),
	m_string(t_labelText),
	m_position(t_pos),
	m_transparent(t_transparent),
	m_rateOfOpaqueness(0),
	m_rateOfTransparency(0),
	m_font(ResourceManager::m_fontHolder[t_level.m_myFonts.m_neonFont])
{
	setupLabel();
}

Label::~Label()
{
}

void Label::setSize(int t_size)
{
	m_charSize = t_size;
	m_text.setCharacterSize(t_size);
}

int Label::getSize()
{
	return m_charSize;
}

void Label::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
	m_text.setPosition(m_position);
}

///returns the position of the label
sf::Vector2f Label::getPosition()
{
	return m_position;
}

///draws the label
void Label::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_text);
}

/// <summary>
///This function makes the text transparent at a rate of t_rate
///and it takes t_takes to decrease by t_rate. Then when the text
///is fully transparent it returns true.
/// </summary>
/// <param name="t_rate"></param>
/// <param name="t_time"></param>
/// <returns></returns>
bool Label::makeTransparent(int t_rate, int t_time)
{
	m_rateOfTransparency++;
	if (m_rateOfTransparency >= t_time)
	{
		if (m_text.getFillColor().a > 0)
		{
			m_text.setFillColor(m_text.getFillColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
		}
		else if(m_text.getFillColor().a <= 0)
		{
			return true;
		}
		m_rateOfTransparency = 0;
	}
	return false;
}

/// <summary>
/// This function makes the text opaque at a rate of t_rate
///and it takes t_takes to decrease by t_rate. Then when the text
///is fully opaque it returns true.
/// </summary>
/// <param name="t_rate"></param>
/// <param name="t_time"></param>
/// <returns></returns>
bool Label::makeOpaque(int t_rate, int t_time)
{
	m_rateOfOpaqueness++;
	if (m_rateOfOpaqueness >= t_time)
	{
		if (m_text.getFillColor().a < 225)
		{
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

sf::FloatRect Label::getGlobalBounds()
{
	return m_text.getGlobalBounds();
}

/// <summary>
/// sets weither the label is in bold, underlined or italic
/// </summary>
/// <param name="t_bold"></param>
/// <param name="t_underlined"></param>
/// <param name="t_italic"></param>
void Label::changeTextProperties(bool t_bold, bool t_underlined, bool t_italic)
{
	if (t_bold && !t_underlined && !t_italic)
	{
		m_text.setStyle(sf::Text::Bold);
	}
	else if (t_underlined && !t_bold && !t_italic)
	{
		m_text.setStyle(sf::Text::Underlined);
	}
	else if (t_italic && !t_underlined && !t_bold)
	{
		m_text.setStyle(sf::Text::Italic);
	}
	else if (!t_bold && !t_underlined && !t_italic)
	{
		m_text.setStyle(sf::Text::Regular);
	}
	else if (t_bold && t_underlined && !t_italic)
	{
		m_text.setStyle(sf::Text::Bold| sf::Text::Underlined);
	}
	else if (t_bold && !t_underlined && t_italic)
	{
		m_text.setStyle(sf::Text::Bold | sf::Text::Italic);
	}
	else if (!t_bold && t_underlined && t_italic)
	{
		m_text.setStyle(sf::Text::Italic | sf::Text::Underlined);
	}
	else if (t_bold && t_underlined && t_italic)
	{
		m_text.setStyle(sf::Text::Bold | sf::Text::Underlined | sf::Text::Italic);
	}
}

void Label::setColour(sf::Color t_colour)
{
	m_text.setFillColor(t_colour);
}

sf::Color Label::getColour()
{
	return m_text.getFillColor();
}

void Label::setString(std::string t_str)
{
	m_string = t_str;
	m_text.setString(m_string);
}

std::string Label::getString()
{
	return m_string;
}

/// <summary>
/// sets the text for the label
/// </summary>
void Label::setupLabel()
{
	m_text.setFont(m_font);
	m_text.setCharacterSize(m_charSize);
	m_text.setString(m_string);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	m_text.setPosition(m_position);
	if (m_transparent)
	{
		m_text.setFillColor(m_text.getFillColor() - sf::Color{ 0,0,0,255 });
	}
}
