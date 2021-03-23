#ifndef LABEL
#define LABEL

#include <SFML\Graphics.hpp>
#include <string>
#include "Globals.h"
#include "ResourceManager.h"
#include "LevelLoader.h"

class Label
{
public:
	Label(LevelData &t_level, int t_size = 30, std::string t_labelText = "", sf::Vector2f t_pos = sf::Vector2f{ ScreenSize::s_WIDTH / 2.0f,ScreenSize::s_HEIGHT / 2.0f }, bool t_transparent = false);
	Label() = default;
	~Label();

	virtual void setPosition(sf::Vector2f t_pos);
	void setSize(int t_size);
	void changeTextProperties(bool t_bold, bool t_underlined, bool t_italic);
	void setColour(sf::Color t_colour);

	int getSize();
	virtual sf::Vector2f getPosition();
	sf::Color getColour();
	void setString(std::string t_str);
	std::string getString();
	bool makeTransparent(int t_rate, int t_time);
	bool makeOpaque(int t_rate, int t_time);
	sf::FloatRect getGlobalBounds();

	virtual void render(sf::RenderWindow &t_window);
protected:
	sf::Font& m_font;//The font of the label
	sf::Text m_text;//The label itself

	LevelData &m_levelData;

	int m_rateOfTransparency; //The rate at which it turns transparent
	int m_rateOfOpaqueness; //The rate at which it turn opaque
	int m_charSize; //The size of the label

	bool m_transparent; //checks if the label is transparent

	std::string m_string; //The string of the label

	sf::Vector2f m_position; //the position of the label

private:
	void setupLabel();
};

#endif //!LABEL