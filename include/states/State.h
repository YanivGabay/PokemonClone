#pragma once
#include "StateMachine.h"

class BaseState 
{

public:
	virtual void entry() = 0;
	virtual void exit() = 0;

	virtual bool update() = 0;
	virtual void handleEvents() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;


	BaseState() = default;


	void setStatus(bool value)
	{
		m_status = value;
	}

	const bool getStatus() const
	{
		return m_status;
	}
private:
	bool m_status {true};


	
};
