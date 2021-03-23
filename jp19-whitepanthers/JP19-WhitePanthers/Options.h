#ifndef OPTIONS
#define OPTIONS

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Game.h"
#include "SelectBox.h"
#include "Slider.h"
#include "ResourceManager.h"

class Game;

class Options
{
public:
	Options(Game & t_game, sf::Sound &t_backSound,sf::Sound &t_selectSound, sf::Sound &t_moveSound,sf::Music&t_bgMusic);
	~Options();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);

	void setupOptions();
private:
	Slider m_volume;

	std::vector<std::shared_ptr<SelectBox>> m_audioCheckboxes;

	sf::RectangleShape m_box;

	Label m_heading;

	int m_sliderTimer;
	int m_checkboxTimer;
	int m_optionTimer;
	int m_screenTimer;

	int m_currentCheckbox;
	int m_currentOption;

	sf::Time m_cumalativeTime;

	AnimationMode m_currentMode{ AnimationMode::Appear };

	sf::Font& m_font;
	Game &m_game;
	sf::Music &m_bgMusic;
	sf::Sound &m_backSound;
	sf::Sound &m_moveSound;
	sf::Sound &m_selectSound;
	sf::Text m_text;

	sf::Sprite m_bg;
	sf::Texture &m_texture;

	void setup();
	void highlightVolumeSlider();
	void highlightCheckbox();
	void changeOptions();
	void alterCheckboxes();
};

#endif //!OPTIONS