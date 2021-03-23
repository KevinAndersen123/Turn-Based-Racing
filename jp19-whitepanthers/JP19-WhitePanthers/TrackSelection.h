#ifndef TRACKSELECTION
#define TRACKSELECTION

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Game.h"
#include "UpgradesTab.h"
#include "GamePlay.h"

class Game;
class GamePlay;

class TrackSelection
{
public:

	TrackSelection(Game & t_game, std::shared_ptr<GamePlay> t_gameplay, sf::Music &t_bgMusic, sf::Music &t_gameplayMusic,
		sf::Sound &t_backSound, sf::Sound&t_moveSound, sf::Sound&t_selectSound);

	~TrackSelection();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);

	void loadAssets();

	void resetGame();

private:
	sf::Font& m_font;
	Game &m_game;

	int m_inputTimer;

	std::shared_ptr<GamePlay> m_gameplay;

	sf::Text m_text;

	sf::Sprite m_bgSprite;
	sf::Texture &m_bgText;

	sf::Texture &m_trackText1;
	sf::RectangleShape m_track;

	sf::CircleShape m_selection;

	std::vector<std::shared_ptr<UpgradesTab>> m_trackTab;

	int currentTrack;
	sf::Music &m_bgMusic;
	sf::Music &m_gameplayMusic;
	sf::Sound &m_backSound;
	sf::Sound &m_selectSound;
	sf::Sound &m_moveSound;
};

#endif //!TRACKSELECTION