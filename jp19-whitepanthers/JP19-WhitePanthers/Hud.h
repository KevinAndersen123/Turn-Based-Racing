#ifndef HUD
#define HUD

#include "SFML/Graphics.hpp"
#include "Controller.h"
#include "Rhombus.h"
#include "ResourceManager.h"

class Hud
{
public:
	Hud(Xbox360Controller & m_controller, LevelData &t_level);
	~Hud();

	void loadAssets();

	void update(sf::Time t_dt);

	void render(sf::RenderWindow & t_window);

	void setView(sf::Vector2f t_center);

	void setViewCentre(sf::Vector2f t_center);

	void updateTimer(sf::Time t_dt);

	void increaseLaps();

	void reset();

	int getTimer();

	int getLap();

	sf::View getView();

	Rhombus m_rhombus;

	sf::View m_playerView;

private:

	Xbox360Controller & m_controller;

	sf::RectangleShape m_bottomRect;

	sf::Text m_lapNumText;

	sf::Text m_lapTimerText;

	sf::Font &m_font;
	
	int m_lapNum;

	sf::Time m_lapTime;
	sf::Texture &m_hudTex;
};
#endif // HUD