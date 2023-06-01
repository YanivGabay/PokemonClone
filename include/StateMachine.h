#pragma once

#include <memory>
#include <vector>
#include "states/PlayState.h"
#include "states/StartState.h"
#include "states/State.h"
#include "Tile.h"



class StateMachine 
{
public:
	StateMachine() : m_window(Resources::getInstance().getWindow())
	{
	};
	~StateMachine() {};
	void pushState(std::unique_ptr<BaseState> state)
	{
		m_states.push_back(std::move(state));
	}

	void popState()
	{
		if (!m_states.empty())
		{
			m_states.pop_back();
		}
	}

	void update()
	{
		if (!m_states.empty())
		{
			m_states.back()->update();
		}
	}

	

	void draw() 
	{
		for (auto& state : m_states)
		{
			state->draw(getWindow());
		}
	}
	sf::RenderWindow& getWindow() 
	{
		return m_window;
	}
private:
	std::vector <std::unique_ptr<BaseState>> m_states;
	sf::RenderWindow& m_window;
};
