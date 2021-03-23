#ifndef UPGRADEITEM
#define UPGRADEITEM

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Label.h"
#include "LevelLoader.h"

class UpgradeItem : public Button, public Label
{
public:
	UpgradeItem(LevelData &t_data, std::string t_string, int t_price,int t_modifier, sf::Vector2f t_position,
		sf::Color t_color = sf::Color::White, bool t_transparent = false, bool t_highlighted=false);
	UpgradeItem() = default;
	~UpgradeItem();

	void render(sf::RenderWindow &t_window);

	bool makeItemOpaque(int t_rate, int t_time);
	bool makeItemTransparent(int t_rate, int t_time);

	void highlighted(bool t_highlighted);
	void purchase(bool t_bool);
	bool getPurchase();
	int getPrice();
	void setPosition(sf::Vector2f t_position);
	int m_modifier; //the amount it upgrdaes the car
private:
	//the sprite for the money
	sf::Sprite m_coin;
	sf::Texture &m_texture;

	LevelData &m_data; //The data for this level

	bool m_highlighted; //checks if selected
	bool m_purchased; //checks if purchased

	int m_price; //price of upgrade item

	void setupAssets();
};

#endif //!UPGRADEITEM
