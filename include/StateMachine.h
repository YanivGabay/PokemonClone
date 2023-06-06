#pragma once

#include <memory>
#include <vector>
#include <queue>
#include "Resources.h"
#include "states/StartState.h"
#include "Camera.h"
#include "Stack.h"

class StateMachine 
{
public:

	StateMachine()
		: m_window(Resources::getInstance().getWindow())
	{}
	
	~StateMachine() = default;

	void runGame()
	{
		std::cout << "inside rungame of statemachine" << std::endl;
		const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // 60 fps
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Clock clock; // Start a clock for frame timing
		Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		m_stateStack.pushState(std::make_unique<StartState>(getStateStack()));
		m_stateStack.pushState(std::move(std::make_unique<FadeInState>(getStateStack(), Resources::getInstance().getColor(BLACK))));
		std::cout << "afterpushing" << std::endl;
		while (m_window.isOpen())
		{
			this->handleEvents();
			
			sf::Time elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;
			std::cout << "after handleevents,statemachine" << std::endl;
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				this->update(TimePerFrame);		
				std::cout << "afterupdate,inside whiletime,statemachine" << std::endl;
			}

			//sf::Vector2f playerPixelPosition = gridToPixelPosition(myPlayer.getPosition());

			//camera.update(playerPixelPosition.x + TILE_SIZE / 2.0f, playerPixelPosition.y + TILE_SIZE / 2.0f);  // Center camera around the player's center

			m_window.setView(camera.getView());
			m_window.clear();

			this->draw();
			std::cout << "after draw,statemachine" << std::endl;
			// window.draw(shape);
			m_window.display();
		}
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


	bool empty() {
		return m_stateStack.empty();
	}

private:
	Stack<BaseState> m_stateStack;
	
	sf::RenderWindow& m_window;
};
