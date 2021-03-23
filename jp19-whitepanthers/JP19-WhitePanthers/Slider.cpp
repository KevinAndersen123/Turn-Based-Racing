#include "Slider.h"

Slider::Slider(LevelData &t_level, bool t_transparent, sf::Vector2f t_buttonSize, sf::Vector2f t_pos, sf::Color t_colour, bool t_highlight) :
	Button(t_pos, t_buttonSize, t_colour, t_transparent),
	Label(t_level, t_transparent),
	m_active(false),
	m_highlight(t_highlight),
	m_sliderTimer(0)
{
	setupShape();
}

Slider::Slider(LevelData &t_level, int t_size, sf::Vector2f t_buttonSize, std::string t_string, bool t_transparent, sf::Vector2f t_pos, sf::Color t_colour, bool t_highlight) :
	Button(t_pos, t_buttonSize, t_colour, t_transparent),
	Label(t_level, t_size, t_string, t_pos, t_transparent),
	m_active(false),
	m_highlight(t_highlight),
	m_velocity(0),
	m_sliderTimer(0)
{
	setupShape();
}

Slider::~Slider()
{
}

void Slider::draw(sf::RenderWindow & t_window)
{
	t_window.draw(m_box);
	t_window.draw(m_selected);
	t_window.draw(m_text);
}

bool Slider::makeSliderOpaque(int t_rate, int t_time)
{
	m_rateOfOpaqueness++;
	if (m_rateOfOpaqueness >= t_time)
	{
		if (m_box.getOutlineColor().a < 255)
		{
			m_box.setOutlineColor(m_box.getOutlineColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_selected.setOutlineColor(m_selected.getOutlineColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_selected.setFillColor(m_selected.getFillColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_text.setFillColor(m_text.getFillColor() + sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
		}
		else if (m_box.getOutlineColor().a >= 225)
		{
			return true;
		}
		m_rateOfOpaqueness = 0;
	}
	return false;
}

bool Slider::makeSliderTransparent(int t_rate, int t_time)
{
	m_rateOfTransparency++;
	if (m_rateOfTransparency >= t_time)
	{
		if (m_box.getOutlineColor().a > 0)
		{
			m_box.setOutlineColor(m_box.getOutlineColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
			m_selected.setOutlineColor(m_selected.getOutlineColor() - sf::Color{ 0,0,0,static_cast<sf::Uint8>(t_rate) });
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

void Slider::setHighlighted(bool t_highlighted)
{
	m_highlight = t_highlighted;
	if (m_highlight)
	{
		m_selected.setOutlineColor(s_SELECTED);
	}
	else
	{
		m_selected.setOutlineColor(s_UN_SELECTED);
	}
}

bool Slider::getHighlighted()
{
	return m_highlight;
}

void Slider::setActive(bool t_active)
{
	m_active = t_active;
	if (m_active)
	{
		m_selected.setFillColor(s_SELECTED);
	}
	else
	{
		m_selected.setFillColor(s_UN_SELECTED);
	}
}

bool Slider::getActive()
{
	return m_active;
}

/// <summary>
/// moves the slider when it is pressed
/// </summary>
/// <param name="t_timer"></param>
/// <param name="t_game"></param>
void Slider::move(int t_timer, Game&t_game)
{
	m_sliderTimer++;
	if (t_game.m_controller.m_currentState.DpadLeft && m_sliderTimer >= 3 || t_game.m_controller.m_currentState.LeftThumbStick.x <= -50 && m_sliderTimer >= 3)
	{
		if (m_selected.getPosition().x - m_selected.getGlobalBounds().width/2 >=
			m_box.getPosition().x)
		{
			if (m_sliderTimer >= t_timer)
			{
				if (m_velocity <= 5)
				{
					m_velocity += m_ACCEL;
				}
				m_selected.move(sf::Vector2f{ -m_velocity,0.0f });
				m_sliderTimer = 0;
			}
		}
	}
	else if (t_game.m_controller.m_currentState.DpadRight && m_sliderTimer >= 3 || t_game.m_controller.m_currentState.LeftThumbStick.x >= 50 && m_sliderTimer >= 3)
	{
		if (m_selected.getPosition().x + m_selected.getGlobalBounds().width /2 <=
			m_box.getPosition().x + m_box.getGlobalBounds().width)
		{
			if (m_sliderTimer >= t_timer)
			{
				if (m_velocity <= 5)
				{
					m_velocity += m_ACCEL;
				}
				m_selected.move(sf::Vector2f{ m_velocity,0.0f });
				m_sliderTimer = 0;
			}
		}
	}
	changeVolume();
}

/// <summary>
/// changes the volume
/// </summary>
void Slider::changeVolume()
{
	float m_start = m_box.getPosition().x - m_box.getGlobalBounds().width / 2;
	float m_volume = ((m_selected.getPosition().x - m_selected.getGlobalBounds().width / 2 - m_start) /
		(m_selected.getGlobalBounds().width / 2 - m_box.getSize().x) * 100);
	s_currentVolume = static_cast<int>(-m_volume);
}

void Slider::setVolume(float t_volume)
{
	float divider = t_volume / 100;
	m_selected.setPosition(sf::Vector2f(m_selected.getPosition().x + m_box.getGlobalBounds().width * divider,m_selected.getPosition().y));
	changeVolume();
}

/// <summary>
/// sets up the shape
/// </summary>
void Slider::setupShape()
{
	m_selected.setSize(m_buttonSize - sf::Vector2f{ m_buttonSize.x / 1.05f,-m_buttonSize.y * 3.0f });
	m_selected.setOrigin(m_selected.getGlobalBounds().width / 2, m_selected.getGlobalBounds().height / 2);
	m_selected.setOutlineThickness(4);
	m_selected.setPosition(sf::Vector2f{ m_buttonPosition.x,m_buttonPosition.y });
	if (m_transparentButton)
	{
		m_selected.setOutlineColor(m_selected.getFillColor() - sf::Color{ 0,0,0,255 });
		m_selected.setFillColor(m_selected.getFillColor() - sf::Color{ 0,0,0,255 });
	}
	else
	{
		m_selected.setOutlineColor(sf::Color::White);
		m_selected.setFillColor(sf::Color::White);
	}
	m_text.setPosition(m_buttonPosition.x+350.0f, m_buttonPosition.y + 50.0f);
}