#ifndef TEXTBUTTONS
#define TEXTBUTTONS

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Label.h"

class TextButtons : public Label
{
public:
	TextButtons(LevelData&t_level, sf::Vector2f t_pos, bool t_transparency = false, int t_size = 30, std::string t_text = "");
	TextButtons(LevelData&t_level, sf::Vector2f t_pos, sf::Color t_outline = sf::Color{255,255,255,255}, int t_size = 30, std::string t_text = "",
		sf::Color t_colour = sf::Color(255, 255, 255, 255), bool t_transparency = false);
	TextButtons() = default;
	~TextButtons();

	void draw(sf::RenderWindow &t_window);
	void setHighlighted(bool t_highlight);
	void makeTextGlow();
	void setOutlineColour(sf::Color t_new);
	void setTextColour(sf::Color t_new);
private:
	sf::Text m_highlightText; //The glow of the text

	sf::Color m_colour; //The fill colour of the text
	sf::Color m_outline; //The outline colour of the text

	bool m_highlighted{ false }; //if the text is highlighted

	void setupText();
};

#endif //!TEXTBUTTONS
