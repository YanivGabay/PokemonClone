#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "Resources.h"
#include "Stack.h"


class BaseState
{
public:
	BaseState(Stack<BaseState>& states)
		: m_states(states)
	{}

	virtual void entry() = 0;
	virtual void exit() = 0;
	virtual void update(sf::Time dt) = 0;
	virtual void handleEvents(sf::Event event) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	virtual ~BaseState() = default;
	
	std::reference_wrapper<Stack<BaseState>> getStateStack()
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
