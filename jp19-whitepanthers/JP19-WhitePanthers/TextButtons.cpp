#include "TextButtons.h"

/// <summary>
/// Simple constructor for a text button that defaults the label
/// </summary>
/// <param name="t_font"></param>
/// <param name="t_pos"></param>
/// <param name="t_transparency"></param>
/// <param name="t_size"></param>
/// <param name="t_text"></param>
TextButtons::TextButtons(LevelData&t_level, sf::Vector2f t_pos, bool t_transparency, int t_size, std::string t_text) :
	Label(t_level, t_size, t_text, t_pos,false),
	m_colour(sf::Color::White),
	m_outline(sf::Color::White)
{
	setupText();
}

/// <summary>
/// Advanced constructor for Text Button that sets up the label
/// </summary>
/// <param name="t_font"></param>
/// <param name="t_pos"></param>
/// <param name="t_outline"></param>
/// <param name="t_size"></param>
/// <param name="t_text"></param>
/// <param name="t_colour"></param>
/// <param name="t_transparency"></param>
TextButtons::TextButtons(LevelData&t_level, sf::Vector2f t_pos, sf::Color t_outline, int t_size, std::string t_text,sf::Color t_colour, bool t_transparency) :
	Label(t_level, t_size, t_text, t_pos,t_transparency),
	m_colour(t_colour),
	m_outline(t_outline)
{
	setupText();
}

/// <summary>
/// Deconstructor
/// </summary>
TextButtons::~TextButtons()
{
}

/// <summary>
/// Draws the label and the highlighted text
/// </summary>
/// <param name="t_window"></param>
void TextButtons::draw(sf::RenderWindow & t_window)
{
	m_highlightText.setPosition(m_text.getPosition());

	if (m_text.getFillColor().a >= 200)
	{
		t_window.draw(m_highlightText);
	}
	t_window.draw(m_text);
}

/// <summary>
/// changes if the text is highlighted or not
/// </summary>
/// <param name="t_highlight"></param>
void TextButtons::setHighlighted(bool t_highlight)
{
	m_highlighted = t_highlight;
	makeTextGlow();
}

/// <summary>
/// Makes the text behind the main text seem like it is glowing
/// </summary>
void TextButtons::makeTextGlow()
{
	if (m_highlighted)
	{
		if (m_highlightText.getOutlineColor().a < 200)
		{
			m_highlightText.setOutlineColor(m_highlightText.getOutlineColor() + sf::Color{ 0,0,0,5 });
		}
	}
	else
	{
		m_highlightText.setOutlineColor(m_outline - sf::Color{ 0,0,0,255 });
	}
}

void TextButtons::setOutlineColour(sf::Color t_new)
{
	m_outline = t_new;
	m_text.setOutlineColor(m_outline);
}

void TextButtons::setTextColour(sf::Color t_new)
{
	m_colour = t_new;
	m_text.setFillColor(m_colour);
}

/// <summary>
/// sets up the text 
/// </summary>
void TextButtons::setupText()
{
	m_highlightText.setFont(m_font);
	m_highlightText.setString(m_string);
	m_highlightText.setCharacterSize(m_charSize);
	m_highlightText.setOrigin(m_highlightText.getGlobalBounds().width / 2, m_highlightText.getGlobalBounds().height / 2);
	m_highlightText.setFillColor(m_colour - sf::Color{ 0,0,0,255 });
	m_highlightText.setPosition(m_position);
	m_highlightText.setOutlineThickness(5);
	m_highlightText.setOutlineColor(m_outline - sf::Color{ 0,0,0,255 });
}
