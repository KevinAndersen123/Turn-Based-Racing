#ifndef  UPGRADESTAB
#define UPGRADESTAB

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Label.h"

class Game;

class UpgradesTab : public Label
{
public:
	UpgradesTab(Game & t_game);
	UpgradesTab(Game & t_game, int t_size, std::string t_string, sf::Vector2f t_position, bool t_transparent);
	~UpgradesTab();

	void render(sf::RenderWindow &t_window);

	bool makeTabTransparent(int t_rate, int t_time);
	bool makeTabOpaque(int t_rate, int t_time);

	void setPosition(sf::Vector2f t_position);
	sf::Vector2f getPosition();
private:

	//hidden copy construtor to avoid copy construction
	UpgradesTab(UpgradesTab &t_tab); 
	//the tabs sprite
	sf::Sprite m_tab;
	sf::Texture &m_texture;

	sf::Vector2f m_tabPosition; //the position of the tab

	bool m_transparent; //checks if its transparent


	Game &m_game;
	sf::Font m_font;

	void loadAssets();
};
#include "Game.h"
#endif // ! UPGRADESTAB