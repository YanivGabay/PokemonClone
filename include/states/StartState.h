#pragma once

#include <optional>

#include "BaseState.h"
#include "StateMachine.h" 
#include "FadeInState.h"
#include "FadeOutState.h"
#include "PlayState.h"
#include "TransitionState.h"
#include "StartMenuState.h"


const int MENU_OPTIONS = 3;
enum StartMenuOptions
{
	NEW_GAME,
	LOAD_GAME,
	QUIT
};

std::optional<StartMenuOptions> operator++(std::optional<StartMenuOptions> option)
{
	if (option)
	{
		*option = static_cast<StartMenuOptions>((static_cast<int>(*option) + 1) % MENU_OPTIONS);
	}
	return option;
}
std::optional<StartMenuOptions> operator--(std::optional<StartMenuOptions> option)
{
	if (option)
	{
		int value = static_cast<int>(*option) - 1;
		if (value < 0)
			value = MENU_OPTIONS - 1;
		*option = static_cast<StartMenuOptions>(value);
	}
	return option;
}


class StartState : public BaseState
{
public:
	StartState(StateMachine& states)
		: BaseState(states)
	{
		entry();
	}

	~StartState() = default;

	void entry()
	{
		m_states.get().pushState(std::move(std::make_unique<FadeInState>(m_states,Resources::getInstance().getColor(BLACK))));
		m_startMenu = std::move(std::make_unique<StartMenuState>(m_states));
	}
	
	void exit()
	{
		auto playState = std::make_unique<PlayState>(m_states);
		auto transition = std::make_unique< TransitionState>(std::move(playState), Resources::getInstance().getColor(BLACK));
		m_states.get().pushState(std::move(transition));
	}

	void update(sf::Time dt)
	{
		m_startMenu->update(dt);
		if (m_startMenu->getChoice()==NEW_GAME)
		{
			m_choice = std::nullopt;
			exit();
		}
	}
	
	void handleEvents(sf::Event event)
	{
		m_startMenu->handleEvents(event);
	}
	
	void draw(sf::RenderWindow& window)
	{
		m_startMenu->draw(window);
	}

private:
	std::optional<StartMenuOptions> m_choice{ std::nullopt };
	std::reference_wrapper<StateMachine> m_states{ getStateMachine() };
	std::unique_ptr<StartMenuState> m_startMenu;
};
