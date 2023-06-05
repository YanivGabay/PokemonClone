#pragma once

#include <SFML/Graphics.hpp>
#include "Resources.h"
#include <functional>
#include "Stack.h"

class StateMachine;


class BaseState 
{
public:
	virtual void entry() = 0;
	virtual void exit() = 0;
	virtual void update(sf::Time dt) = 0;
	virtual void handleEvents(sf::Event event) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	
	BaseState(Stack<BaseState>& states)
		: m_states(states)
	{}
	
	std::reference_wrapper<Stack<BaseState>> getStateMachine()
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
	Stack<BaseState>& m_states;
	sf::Vector2i m_windowSize {Resources::getInstance().getWindow().getSize()};
};
