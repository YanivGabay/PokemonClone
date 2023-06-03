#pragma once
#include "BaseState.h"
#include "FadeInState.h"
#include "FadeOutState.h"
#include "TransitionState.h"
#include "StartMenuState.h"

enum StartMenuOptions
{

};

class StartState : BaseState
{
public:
	StartState(StateMachine& states) :
		BaseState(states)
	{
		entry();
	}

	~StartState ()
	{
	}

	void entry()
	{

		m_states.get().pushState(std::move(std::make_unique<FadeInState>(m_states,Resources::getInstance().getColor(BLACK))));

	}
	void exit()
	{
		
		auto playState = std::make_unique<PlayState>(m_states);
		auto transition = std::make_unique< TransitionState>(std::move(playState), Resources::getInstance().getColor(BLACK));
		m_states.get().pushState(std::move(transition));
		
	}

	void update(float dt) 
	{
		if (choice)
		{
			exit();
		}
	}
	void handleEvents()
	{

	}
	void draw(sf::RenderWindow& window) {

	}
private:
	std::reference_wrapper<StateMachine> m_states{ getStateMachine() };
	std::unique_ptr<StartMenuState> m_startMenu

};
