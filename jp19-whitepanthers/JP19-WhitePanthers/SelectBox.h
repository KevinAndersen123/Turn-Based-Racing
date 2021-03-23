#ifndef SELECTBOX
#define SELECTBOX

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Button.h"
#include "Label.h"

class SelectBox : public Button, public Label
{
public:
	SelectBox(LevelData &t_level, bool t_transparent, sf::Vector2f t_buttonSize, sf::Vector2f t_pos, sf::Color t_colour, bool t_active = false, bool t_highlight = false);
	SelectBox(LevelData &t_level, int t_size, sf::Vector2f t_buttonSize, std::string t_string, bool t_transparent, sf::Vector2f t_pos, sf::Color t_colour, bool t_active = false, bool t_highlight = false);
	~SelectBox();
	void draw(sf::RenderWindow &t_window);
	bool makeCheckboxOpaque(int t_rate, int t_time);
	bool makeCheckboxTransparent(int t_rate, int t_time);
	void setHighlighted(bool t_highlighted);
	bool getHighlighted();
	void setActive(bool t_active);
	bool getActive();
private:
	bool m_active;
	bool m_highlight;

	sf::RectangleShape m_selected;

	void setupShape();
};

#endif