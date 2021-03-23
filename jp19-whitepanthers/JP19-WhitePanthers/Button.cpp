#include "Button.h"

/// <summary>
/// Constructor for Button,
/// Sets the position, size , color, and transparency of the button
/// </summary>
/// <param name="t_pos"></param>
/// <param name="t_size"></param>
/// <param name="t_color"></param>
/// <param name="t_transparent"></param>
Button::Button(sf::Vector2f t_pos, sf::Vector2f t_size, sf::Color t_color, bool t_transparent) :
	m_buttonPosition(t_pos),
	m_buttonColour(t_color),
	m_transparentButton(t_transparent),
	m_buttonSize(t_size)
{
	setupShapes();
}

Button::~Button()
{
}

/// <summary>
/// the render function for the button
/// </summary>
/// <param name="t_window"></param>
void Button::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_box);
}

/// <summary>
/// The initialisation for the buttons box
/// </summary>
void Button::setupShapes()
{
	m_box.setSize(m_buttonSize);
	m_box.setPosition(m_buttonPosition);
	m_box.setOutlineThickness(5);
	m_box.setFillColor(sf::Color{ 0,0,0,0 });
	if (m_transparentButton)
	{
		m_box.setOutlineColor(m_box.getOutlineColor() - sf::Color{ 0,0,0,255 });
	}
	else
	{
		m_box.setOutlineColor(m_buttonColour);
	}
}
