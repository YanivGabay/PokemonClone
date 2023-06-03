#pragma once
#include "StateMachine.h"
#include <functional>

class BaseState 
{

public:
	virtual void entry() = 0;
	virtual void exit() = 0;

	virtual void update(float dt) = 0;
	virtual void handleEvents() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;


	BaseState(StateMachine& states) : m_states(states)
	{

	}
	

	std::reference_wrapper<StateMachine> getStateMachine()
	{
		return std::ref(m_states);
	}

	void setStatus(bool value)
	{
		m_status = value;
	}

	const bool getStatus() const
	{
		return m_status;
	}
	const sf::Vector2i getWindowSize() const
	{
		return m_windowSize;
	}
private:
	bool m_status {true};
	StateMachine& m_states;
	sf::Vector2i m_windowSize {Resources::getInstance().getWindow().getSize()};


	
};
