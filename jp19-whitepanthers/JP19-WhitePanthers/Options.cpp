#include "Options.h"

Options::Options(Game & t_game, sf::Sound &t_backSound,sf::Sound &t_selectSound, sf::Sound &t_moveSound, sf::Music &t_bgMusic) :
	m_game(t_game),
	m_font(ResourceManager::m_fontHolder[t_game.m_levelData.m_myFonts.m_neonFont]),
	m_sliderTimer(0),
	m_backSound(t_backSound),
	m_volume(Slider(t_game.m_levelData, 30, { 750.0f,10.0f }, "Min                                                                Max", true, { 430.0f,530.0f }, sf::Color::White, true)),
	m_checkboxTimer(0),
	m_currentCheckbox(0),
	m_optionTimer(0),
	m_currentOption(0),
	m_screenTimer(0),
	m_heading(t_game.m_levelData, 45, "Options", {800.0f,75.0f},true),
	m_moveSound(t_moveSound),
	m_selectSound(t_selectSound),
	m_bgMusic(t_bgMusic),
	m_texture(ResourceManager::m_textureHolder[t_game.m_levelData.m_myTextures.m_bGFiveID])
{
	setupOptions();
	setup();
}

Options::~Options()
{
}

void Options::update(sf::Time t_deltaTime)
{
	m_cumalativeTime += t_deltaTime;

	if (m_currentMode == AnimationMode::Appear)
	{
		for (auto  & checkbox : m_audioCheckboxes)
		{
			checkbox->makeCheckboxOpaque(7, 2);
		}
		m_heading.makeOpaque(7, 2);
		m_volume.makeSliderOpaque(7, 2);
		if (m_cumalativeTime.asSeconds() > 2)
		{
			m_currentMode = AnimationMode::None;
		}
	}
	if (m_currentMode == AnimationMode::None)
	{
		m_screenTimer++;
		changeOptions();
		if (m_game.m_controller.m_currentState.B && m_screenTimer >= 10)
		{
			if (s_audioActive && s_sfxActive)
			{
				m_backSound.play();
			}
			m_currentMode = AnimationMode::Disappear;
			m_cumalativeTime = sf::seconds(0);
		}
	}
	if (m_currentMode == AnimationMode::Disappear)
	{
		for (auto & checkbox : m_audioCheckboxes)
		{
			checkbox->makeCheckboxTransparent(7, 2);
		}
		m_heading.makeTransparent(7, 2);
		m_volume.makeSliderTransparent(7, 2);
		if (m_cumalativeTime.asSeconds() > 2)
		{
			m_cumalativeTime = sf::seconds(0);
			m_currentMode = AnimationMode::Appear;
			m_game.m_currentMode = GameMode::MainMenu;
		}
	}
}

void Options::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color::Black);

	t_window.draw(m_bg);
	m_heading.render(t_window);

	t_window.draw(m_box);

	for (auto & checkbox : m_audioCheckboxes)
	{
		checkbox->draw(t_window);
	}

	m_volume.draw(t_window);

	t_window.display();
}

void Options::setupOptions()
{
	m_volume.setVolume(50.0f);
	m_audioCheckboxes.push_back(std::make_shared<SelectBox>(SelectBox(m_game.m_levelData, 30, { 30.0f,30.0f }, "Audio", true, { 550.0f,420.0f }, sf::Color::White, true, false)));
	m_audioCheckboxes.push_back(std::make_shared<SelectBox>(SelectBox(m_game.m_levelData, 30, { 30.0f,30.0f }, "Sfx", true, { 800.0f,420.0f }, sf::Color::White, true, false)));
	m_audioCheckboxes.push_back(std::make_shared<SelectBox>(SelectBox(m_game.m_levelData, 30, { 30.0f,30.0f }, "Music", true, { 1100.0f,420.0f }, sf::Color::White, true, false)));
}

void Options::setup()
{
	m_bg.setTexture(m_texture);
	m_bg.setPosition({ 0.0f,0.0f });

	m_box.setFillColor(sf::Color(0, 0, 0, 200));
	m_box.setSize({ 800.0f, 300.0f });
	m_box.setPosition({300.0f,400.0f});
}

void Options::highlightVolumeSlider()
{
	for (int i = 0; i < 3; i++)
	{
		m_audioCheckboxes[i]->setHighlighted(false);
	}
	m_volume.setHighlighted(true);
	m_sliderTimer++;

	if (m_sliderTimer >= 10 && m_game.m_controller.m_currentState.A)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_selectSound.play();
		}
		m_volume.setActive(true);
		m_sliderTimer = 0;
	}
	if (m_volume.getActive())
	{
		if (m_sliderTimer >= 10 && m_game.m_controller.m_currentState.B)
		{
			m_volume.setActive(false);
			m_screenTimer = 0;
			m_sliderTimer = 0;
		}
		m_volume.move(3, m_game);
	}
}

void Options::highlightCheckbox()
{
	m_volume.setHighlighted(false);
	for (int i = 0; i < 3; i++)
	{
		m_audioCheckboxes[i]->setHighlighted(false);
	}
	m_audioCheckboxes[m_currentCheckbox]->setHighlighted(true);
	m_checkboxTimer++;

	if (m_checkboxTimer >= 10 && m_game.m_controller.m_currentState.DpadRight && m_checkboxTimer >= 10
		|| m_game.m_controller.m_currentState.LeftThumbStick.x > 50 && m_checkboxTimer >= 10)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_currentCheckbox = ((m_currentCheckbox + 1) % 3);
		m_checkboxTimer = 0;
	}
	else if (m_checkboxTimer >= 10 && m_game.m_controller.m_currentState.DpadLeft
		|| m_checkboxTimer >= 10 && m_game.m_controller.m_currentState.LeftThumbStick.x < -50)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_currentCheckbox = (m_currentCheckbox == 0 ? (3 - 1) : m_currentCheckbox - 1);
		m_checkboxTimer = 0;
	}

	if (m_checkboxTimer >= 10 && m_game.m_controller.m_currentState.A)
	{
		if (s_audioActive && s_sfxActive)
		{
			m_selectSound.play();
		}
		if (m_audioCheckboxes[m_currentCheckbox]->getHighlighted())
		{
			if (!m_audioCheckboxes[m_currentCheckbox]->getActive())
			{
				m_audioCheckboxes[m_currentCheckbox]->setActive(true);
				m_checkboxTimer = 0;
			}
			else if (m_audioCheckboxes[m_currentCheckbox]->getActive())
			{
				m_audioCheckboxes[m_currentCheckbox]->setActive(false);
				m_checkboxTimer = 0;
			}
		}
		alterCheckboxes();
	}
}

void Options::changeOptions()
{
	m_optionTimer++;
	if (m_optionTimer >= 20 && m_game.m_controller.m_currentState.DpadDown && !m_volume.getActive() ||
		m_optionTimer >= 20 && m_game.m_controller.m_currentState.LeftThumbStick.y >50 && !m_volume.getActive())
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_currentOption = (m_currentOption + 1) % 2;
		m_optionTimer = 0;
	}
	else if (m_optionTimer >= 20 && m_game.m_controller.m_currentState.DpadUp && !m_volume.getActive() ||
		m_optionTimer >= 20 && m_game.m_controller.m_currentState.LeftThumbStick.y < -50 && !m_volume.getActive())
	{
		if (s_audioActive && s_sfxActive)
		{
			m_moveSound.play();
		}
		m_currentOption = m_currentOption == 0 ? (2 - 1) : m_currentOption - 1;
		m_optionTimer = 0;
	}

	if (m_currentOption == 0)
	{
		highlightCheckbox();
	}
	else if (m_currentOption == 1)
	{
		highlightVolumeSlider();

	}
}

void Options::alterCheckboxes()
{
	if (m_audioCheckboxes[0]->getActive())
	{
		s_audioActive = true;
		if (s_musicActive) {
			m_bgMusic.play();
		}
	}
	else
	{
		s_audioActive = false;
		m_bgMusic.stop();
	}
	if (m_audioCheckboxes[1]->getActive())
	{
		s_sfxActive = true;
	}
	else
	{
		s_sfxActive = false;
	}
	if (m_audioCheckboxes[2]->getActive())
	{
		s_musicActive = true;
		if (s_audioActive) 
		{
			m_bgMusic.play();
		}
	}
	else
	{
		s_musicActive = false;
		m_bgMusic.stop();
	}
}
