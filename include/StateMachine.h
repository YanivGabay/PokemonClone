#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include "Resources.h"
#include "states/StartState.h"
#include "Camera.h"
#include "Stack.h"
#include "SoundTon.h"


class StateMachine 
{
public:
	StateMachine()
		: m_window(Resources::getInstance().getWindow()) {}
	
	~StateMachine() = default;
	
	void runGame()
	{
		const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // 60 fps
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Clock clock; // Start a clock for frame timing
	
		m_stateStack.pushState(std::make_unique<StartState>(getStateStack()));
		
		m_stateStack.pushState(std::move(std::make_unique<FadeInState>(getStateStack(), Resources::getInstance().getColor(BLACK))));
		
		while (m_window.isOpen()&&!m_stateStack.checkQuitStatus())
		{
			this->handleEvents();
			
			sf::Time elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;
		
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				this->update(TimePerFrame);
			}
			
			m_window.clear();

			this->draw();
			
			m_window.display();
		}
		
		return;
	}
	
	void handleEvents()
	{
		m_stateStack.handleEvents();
	}
	
	void update(sf::Time dt)
	{
		m_stateStack.update(dt);
	}
	
	void draw() 
	{
		m_stateStack.draw();
	}
	
	sf::RenderWindow& getWindow() 
	{
		return m_window;
	}

	Stack<BaseState>& getStateStack()
	{
		return m_stateStack;
	}

	void pushState(std::unique_ptr<BaseState> state)
	{
		m_stateStack.pushState(std::move(state));
	}

	void popState()
	{
		m_stateStack.popState();
	}
	
	bool empty()
	{
		return m_stateStack.empty();
	}

private:
	sf::RenderWindow& m_window;
	
	Stack<BaseState> m_stateStack;
};
