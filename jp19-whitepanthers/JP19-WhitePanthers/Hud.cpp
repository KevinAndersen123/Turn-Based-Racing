#include "Hud.h"

Hud::Hud(Xbox360Controller & t_controller,LevelData &t_level) :
	m_controller(t_controller),
	m_rhombus(t_controller),
	m_lapNum(1),
	m_lapTime(sf::Time::Zero),
	m_hudTex(ResourceManager::m_textureHolder[t_level.m_myTextures.m_hudID]),
	m_font(ResourceManager::m_fontHolder[t_level.m_myFonts.m_neonFont])
{
	loadAssets();

	m_playerView.setCenter(1800, 450);
	m_playerView.setSize(1600, 900);

	m_bottomRect.setSize(sf::Vector2f(1600,300));
	m_bottomRect.setFillColor(sf::Color{ 102, 255, 255, 155 });

	m_lapNumText.setFillColor(sf::Color{ 255, 255, 255, 255 });
	m_lapNumText.setString(" Lap : " + std::to_string( m_lapNum));
	m_lapNumText.setPosition(sf::Vector2f(m_playerView.getCenter() + sf::Vector2f(300.0f, 300)));
	m_lapNumText.setCharacterSize(50);

	m_lapTimerText.setFillColor(sf::Color{ 255, 255, 255, 255 });
	m_lapTimerText.setString(" Current Time : " + std::to_string(static_cast<int>(m_lapTime.asSeconds())));
	m_lapTimerText.setPosition(sf::Vector2f(m_playerView.getCenter() + sf::Vector2f(300.0f, 350)));
	m_lapTimerText.setCharacterSize(50);
}

Hud::~Hud()
{
}

void Hud::loadAssets()
{
	m_bottomRect.setTexture(&m_hudTex);
	m_lapNumText.setFont(m_font);
	m_lapTimerText.setFont(m_font);
}

void Hud::update(sf::Time t_dt)
{
	m_rhombus.update();	
}

void Hud::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_bottomRect);
	t_window.draw(m_lapNumText);
	t_window.draw(m_lapTimerText);
	m_rhombus.render(t_window);
}

void Hud::setView(sf::Vector2f t_center)
{
	m_playerView.setCenter(t_center);
	m_bottomRect.setPosition(m_playerView.getCenter() + sf::Vector2f(-800.0f, 150));
	m_rhombus.setPosition(m_playerView.getCenter() + sf::Vector2f(-600, 300));
	m_lapNumText.setPosition(sf::Vector2f(m_playerView.getCenter() + sf::Vector2f(300.0f, 300)));
	m_lapTimerText.setPosition(sf::Vector2f(m_playerView.getCenter() + sf::Vector2f(300.0f, 350)));
}

void Hud::setViewCentre(sf::Vector2f t_center)
{
	m_playerView.setCenter(t_center);
}

void Hud::updateTimer(sf::Time t_dt)
{
	m_lapTime += t_dt;
	m_lapTimerText.setString(" Current Time : " + std::to_string(static_cast<int>(m_lapTime.asSeconds())));
}

void Hud::increaseLaps()
{
	m_lapNum++;
	m_lapNumText.setString("Lap : " + std::to_string(m_lapNum));
}

void Hud::reset()
{
	m_lapNum = 1;
	m_lapTime = sf::Time::Zero;
	m_lapNumText.setString(" Lap : " + std::to_string(m_lapNum));
	m_lapTimerText.setString(" Current Time : " + std::to_string(static_cast<int>(m_lapTime.asSeconds())));
}

int Hud::getTimer()
{
	return static_cast<int>(m_lapTime.asSeconds());
}

int Hud::getLap()
{
	return m_lapNum;
}

sf::View Hud::getView()
{
	return m_playerView;
}

