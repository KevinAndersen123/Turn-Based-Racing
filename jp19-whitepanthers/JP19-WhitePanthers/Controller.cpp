//mohammad alhourani


#include "Controller.h"

Xbox360Controller::Xbox360Controller()
{
}

Xbox360Controller::~Xbox360Controller()
{
}

bool Xbox360Controller::isConnected()
{
	return sf::Joystick::isConnected(sf_Joystick_index);
}

bool Xbox360Controller::connect()
{
	//checking all ports for the controller 
	for (int index = 0; index < sf::Joystick::Count; index++)
	{
		if (sf::Joystick::isConnected(index) == true)
		{
			sf_Joystick_index = index;
			return true;
		}
	}

	//if there is no controller connected return false
	return false;
}

void Xbox360Controller::update(sf::Time t_dt)
{
	

	if(m_updateTimer <= sf::seconds(1))
	{
		m_updateTimer += t_dt;

		analog();

		Dpad();

		triggers();

		buttons();
	}
	else
	{
		m_buttonPressed = false;

		m_updateTimer = sf::Time::Zero;
	}

	
}

void Xbox360Controller::analog()
{
	//variables to set the left analog stick 
	float LeftX = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::X);
	float LeftY = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Y);

	if (LeftX < 15.0 && LeftX > -15.0)
	{
		LeftX = 0.0;
	}

	if (LeftY < 15.0 && LeftY > -15.0)
	{
		LeftY = 0.0;
	}
		
	m_currentState.LeftThumbStick = sf::Vector2f(LeftX, LeftY);

	//variable for the right analog stick
	float RightX = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::U);
	float RightY = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::V);

	if (RightX < 15.0 && RightX > -15.0)
	{
		RightX = 0.0;
	}

	if (RightY < 15.0 && RightY > -15.0)
	{
		RightY = 0.0;
	}

	m_currentState.RightThumbStick = sf::Vector2f(RightX, RightY);
}

void Xbox360Controller::Dpad()
{
	float dPadX = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovX);
	float dPadY = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovY);

	//checking if down on the dpad is true
	if (dPadY > dpadThreshold )
	{
		m_currentState.DpadUp = true;
	}
	else
	{
		m_currentState.DpadUp= false;
	}

	//checking if the dpad up is true
	if (dPadY < -(dpadThreshold) )
	{
		m_currentState.DpadDown = true;
	}
	else
	{
		m_currentState.DpadDown = false;
	}

	//checking if dpad right is true 
	//right direction is positive
	if (dPadX > dpadThreshold)
	{
		m_currentState.DpadRight = true;
	}
	else
	{
		m_currentState.DpadRight = false;
	}

	//checking if dpad left is true
	//left direction is negative
	if (dPadX < -(dpadThreshold))
	{
		m_currentState.DpadLeft = true;
	}
	else
	{
		m_currentState.DpadLeft = false;
	}
}

void Xbox360Controller::triggers()
{
	float ZAxis = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z);

	if (ZAxis > 0.0)
	{
		m_currentState.LTrigger = ZAxis;
	}
	else if (ZAxis < 0.0)
	{
		m_currentState.RTrigger = -(ZAxis);
	}

	if(ZAxis < 1.0 && ZAxis > -1.0)
	{
		ZAxis = 0.0;
		m_currentState.LTrigger = ZAxis;
		m_currentState.RTrigger = ZAxis;
	}
}

void Xbox360Controller::buttons()
{
	//the A button
	if (sf::Joystick::isButtonPressed(sf_Joystick_index, 0) == true && m_buttonPressed == false)
	{
		m_currentState.A = true;
		m_buttonPressed = true;
	}
	else
	{
		m_currentState.A = false;
	}

	//the B button
	if (sf::Joystick::isButtonPressed(sf_Joystick_index, 1) == true && m_buttonPressed == false)
	{
		m_currentState.B = true;
		m_buttonPressed = true;
	}
	else
	{
		m_currentState.B = false;
	}

	//the X button
	if (sf::Joystick::isButtonPressed(sf_Joystick_index, 2) == true && m_buttonPressed == false)
	{
		m_currentState.X = true;
		m_buttonPressed = true;
	}
	else
	{
		m_currentState.X = false;
	}

	// the Y button
	if (sf::Joystick::isButtonPressed(sf_Joystick_index, 3) == true && m_buttonPressed == false)
	{
		m_currentState.Y = true;
		m_buttonPressed = true;
	}
	else
	{
		m_currentState.Y = false;
	}

	//the LB button
	if (sf::Joystick::isButtonPressed(sf_Joystick_index, 4) == true && m_buttonPressed == false)
	{
		m_currentState.LB = true;
		m_buttonPressed = true;
	}
	else
	{
		m_currentState.LB = false;
	}

	//the RB button
	if (sf::Joystick::isButtonPressed(sf_Joystick_index, 5) == true && m_buttonPressed == false)
	{
		m_currentState.RB = true;
		m_buttonPressed = true;
	}
	else
	{
		m_currentState.RB = false;
	}

	//the Back button
	if (sf::Joystick::isButtonPressed(sf_Joystick_index, 6) == true && m_buttonPressed == false)
	{
		m_currentState.Back = true;
		m_buttonPressed = true;
	}
	else
	{
		m_currentState.Back = false;
	}

	//the Start button
	if (sf::Joystick::isButtonPressed(sf_Joystick_index, 7) == true && m_buttonPressed == false)
	{
		m_currentState.Start = true;
		m_buttonPressed = true;
	}
	else
	{
		m_currentState.Start = false;
	}

	//the left thumb stick button
	if (sf::Joystick::isButtonPressed(sf_Joystick_index, 8) == true && m_buttonPressed == false)
	{
		m_currentState.LeftThumbStickClick = true;
		m_buttonPressed = true;
	}
	else
	{
		m_currentState.LeftThumbStickClick = false;
	}

	//the right thumb stick button
	if (sf::Joystick::isButtonPressed(sf_Joystick_index, 9) == true && m_buttonPressed == false )
	{
		m_currentState.RightThumbStickClick = true;
		m_buttonPressed = true;
	}
	else
	{
		m_currentState.RightThumbStickClick = false;
	}
}

