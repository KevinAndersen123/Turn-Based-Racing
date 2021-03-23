#ifndef SLIDER
#define SLIDER

/// Author: Francis Carroll

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "Label.h"

class Game;

class Slider : public Button, public Label
{
public:
	Slider(LevelData &t_level, bool t_transparent, sf::Vector2f t_buttonSize, sf::Vector2f t_pos, sf::Color t_colour, bool t_highlight = false);
	Slider(LevelData &t_level, int t_size, sf::Vector2f t_buttonSize, std::string t_string, bool t_transparent, sf::Vector2f t_pos, sf::Color t_colour, bool t_highlight = false);
	~Slider();
	void draw(sf::RenderWindow &t_window);
	bool makeSliderOpaque(int t_rate, int t_time);
	bool makeSliderTransparent(int t_rate, int t_time);
	void setHighlighted(bool t_highlighted);
	bool getHighlighted();
	void setActive(bool t_active);
	bool getActive();
	void move(int t_timer, Game& t_game);
	void changeVolume();
	void setVolume(float t_volume);
private:
	bool m_active;
	bool m_highlight;
	float m_velocity;
	const float m_ACCEL = 0.1f;

	int m_sliderTimer;

	sf::RectangleShape m_selected;//the slider shape

	void setupShape();
};

#include "Game.h"

#endif //!SLIDER