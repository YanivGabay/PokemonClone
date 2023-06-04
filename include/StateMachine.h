#pragma once

#include <memory>
#include <vector>

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
		const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // 60 fps
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Clock clock; // Start a clock for frame timing
		Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		m_states.pushState(std::make_unique<StartState>(*this));
		
		while (m_window.isOpen())
		{
			this->handleEvents();
			
			sf::Time elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;

			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				this->update(TimePerFrame);				
			}

			//sf::Vector2f playerPixelPosition = gridToPixelPosition(myPlayer.getPosition());

			//camera.update(playerPixelPosition.x + TILE_SIZE / 2.0f, playerPixelPosition.y + TILE_SIZE / 2.0f);  // Center camera around the player's center

			m_window.setView(camera.getView());
			m_window.clear();

			this->draw();

			// window.draw(shape);
			m_window.display();
		}
	}
	
	

	void handleEvents()
	{
		m_states.handleEvents();
	}
	
	void update(sf::Time dt)
	{
		m_states.update(dt);
	}
	
	void draw() 
	{
		m_states.draw();
	}
	
	sf::RenderWindow& getWindow() 
	{
		return m_window;
	}

private:
	// std::vector <std::unique_ptr<BaseState>> m_states;
	Stack<BaseState> m_states;
	sf::RenderWindow& m_window;
};
