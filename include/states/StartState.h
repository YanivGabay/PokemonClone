#pragma once

#include <optional>
#include <iostream>

#include "BaseState.h"
#include "FadeInState.h"
#include "FadeOutState.h"
#include "StartMenuState.h"
#include "TransitionState.h"
#include "PlayState.h"
#include <future>


class StartState : public BaseState
{
public:
	StartState(Stack<BaseState>& states)
		: BaseState(states)
	{
		entry();
	}

	~StartState() = default;

	void entry() override
	{
		m_startMenu = std::move(std::make_unique<StartMenuState>(m_states));
	}
	
	void exit() override
	{
		auto playstate = std::make_unique<PlayState>(m_states.get());
		auto transition = std::make_unique<TransitionState>(m_states.get(), std::move(playstate), Resources::getInstance().getColor(BLACK));
		m_states.get().pushQueueState(std::move(transition));
		m_startMenu->resetText();
		m_loadingStarted = false;

	}
	
	void update(sf::Time dt) override
	{
		m_startMenu->update(dt);
		
		if (m_startMenu->getChoice() == QUIT)
		{
			m_choice = std::nullopt;
			setStatus(false);
		}
		
		if (m_startMenu->getChoice()==NEW_GAME&&!m_loadingStarted)
		{
			m_choice = std::nullopt;
			m_loadingStarted = true;
			m_loadingFuture = std::async(std::launch::async, &StartState::exit, this);
			m_startMenu->setLoadingText();
		}
		
		
	}

	
	void handleEvents(sf::Event event) override
	{
		m_startMenu->handleEvents(event);
	}
	
	void draw(sf::RenderWindow& window) override
	{
		m_startMenu->draw(window);
	}

private:
	std::optional<StartMenuOptions> m_choice{ std::nullopt };
	std::reference_wrapper<Stack<BaseState>> m_states{ getStateStack() };
	std::unique_ptr<StartMenuState> m_startMenu;

	std::future<void> m_loadingFuture;
	std::atomic<bool> m_loadingStarted {false};
};
