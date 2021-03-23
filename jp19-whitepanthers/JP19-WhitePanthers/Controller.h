//mohammad alhourani

#ifndef XBOX360CONTROLLER
#define XBOX360CONTROLLER

#include <SFML/Graphics.hpp>
#include <iostream>


struct GamePadState
{
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbStickClick;
	bool RightThumbStickClick;
	bool DpadUp;
	bool DpadDown;
	bool DpadLeft;
	bool DpadRight;
	bool Start;
	bool Back;
	bool Xbox;
	float RTrigger;
	float LTrigger;
	sf::Vector2f RightThumbStick;
	sf::Vector2f LeftThumbStick;
};


class Xbox360Controller
{
private:
	// deadzone for the dpad 
	const int dpadThreshold = 50;
public:
	// newly added for multiple controller support not required in your project
	// number of connected controllers
	static int s_noOfControllers;
	// index count for multiple controllers if connected
	int sf_Joystick_index{ 0 };
	// the current state of all the buttons
	GamePadState m_currentState;
	// the previous state to use to check for the moment a button is pressed
	GamePadState m_previousState;

	bool m_buttonPressed{ false };

	Xbox360Controller();
	~Xbox360Controller();

	sf::Time m_updateTimer{ sf::Time::Zero };

	bool isConnected();
	bool connect();

	void update(sf::Time t_dt);
	void analog();

	void Dpad();

	void triggers();

	void buttons();
};
#endif // !XBOX360CONTROLLER