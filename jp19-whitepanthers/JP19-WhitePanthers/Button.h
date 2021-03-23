#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include "Globals.h"

class Button
{
public:
	Button(sf::Vector2f t_pos = { ScreenSize::s_WIDTH/ 2,ScreenSize::s_HEIGHT / 2 }, sf::Vector2f t_size = {30.0f,30.0f}, sf::Color t_color = sf::Color::White, bool t_transparent = false);
	~Button();
protected:
	sf::Vector2f m_buttonPosition; //The position of the button
	sf::Vector2f m_buttonSize; //The size of the button

	sf::Color m_buttonColour; //The color of the button

	sf::RectangleShape m_box; //the button

	bool m_transparentButton; //Checks if the button is transparent

	virtual void render(sf::RenderWindow &t_window);

private:
	void setupShapes();
};

#endif //!BUTTON
