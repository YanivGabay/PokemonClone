#pragma once


#include "Resources.h"
#include "states/StartState.h"
#include <memory>
#include <vector>
#include "Camera.h"

class StateMachine 
{
public:

	StateMachine() : m_window(Resources::getInstance().getWindow())
	{
	};
	~StateMachine() {};

	
	void runGame()
	{
		const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // 60 fps
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Clock clock; // Start a clock for frame timing
		Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		this->pushState(std::make_unique<StartState>(*this));

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
	void pushFadeOut(std::unique_ptr<BaseState> nextstate, std::unique_ptr<BaseState> fadein)
	{
		this->popState();
		this->popState();
		this->pushState(std::move(nextstate));
		this->pushState(std::move(fadein));
	}

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
	void handleEvents()
	{
		if (!m_states.empty())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();
				else
				{
					m_states.back()->handleEvents(event);

				}
			}
		}
	}
	void update(sf::Time dt)
	{
		if (!m_states.empty())
		{
			m_states.back()->update(dt);
			if (!m_states.back()->getStatus())
				this->popState();
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
