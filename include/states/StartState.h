#pragma once

#include <optional>

#include "BaseState.h"

#include "FadeInState.h"
#include "FadeOutState.h"


#include "StartMenuState.h"
#include "TransitionState.h"
#include "PlayState.h"




class StartState : public BaseState
{
public:
	StartState(Stack<BaseState>& states)
		: BaseState(states)
	{
		entry();
	}

	~StartState() = default;

	void entry()
	{
		m_startMenu = std::move(std::make_unique<StartMenuState>(m_states));
		
		
	}
	
	void exit()
	{
		auto playstate = std::make_unique<PlayState>(m_states.get());
		auto transition = std::make_unique<TransitionState>(m_states.get(), std::move(playstate), Resources::getInstance().getColor(BLACK));
		m_states.get().pushQueueState(std::move(transition));
	}


	void update(sf::Time dt)
	{
		m_startMenu->update(dt);
		//std::cout << "after startstatemenu->update" << std::endl;
		if (m_startMenu->getChoice() == QUIT)
		{
			m_choice = std::nullopt;
			setStatus(false);
		}
		if (m_startMenu->getChoice()==NEW_GAME)
		{
			m_choice = std::nullopt;
			exit();
			
		}
		
	
	}
	
	void handleEvents(sf::Event event)
	{
		//std::cout << "inside startstate handlevents" << std::endl;
		m_startMenu->handleEvents(event);
	}
	
	void draw(sf::RenderWindow& window)
	{
		m_startMenu->draw(window);
	}

private:
	std::optional<StartMenuOptions> m_choice{ std::nullopt };
	std::reference_wrapper<Stack<BaseState>> m_states{ getStateStack() };
	std::unique_ptr<StartMenuState> m_startMenu;
};
