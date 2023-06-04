#pragma once

#include "BaseState.h"
#include "guis/Gui.h"
#include <optional>
#include "StartState.h"


class StartMenuState : public BaseState
{
public:
	StartMenuState(StateMachine& states)
		: BaseState(states)
	{
		entry();
	}

	~StartMenuState() = default;
	
	void entry()
	{
		sf::Font font = Resources::getInstance().getFont();
		sf::Vector2f buttonSize = sf::Vector2f(m_windowSize.x / 4, m_windowSize.y / 4);
		float x = m_windowSize.x / 2 - (buttonSize.x / 2);
		
		for (size_t i = 0; i < MENU_OPTIONS; i++)
		{
			m_menuSelection[i] = std::move(std::make_unique<Gui>(font, buttonSize, sf::Vector2f(x, 50 + buttonSize.y * i)));
		}
		m_menuSelection[NEW_GAME]->setText("New Game");
		m_menuSelection[LOAD_GAME]->setText("Load Game");
		m_menuSelection[QUIT]->setText("Quit");
	}
	
	void exit() {}
	
	void update(sf::Time dt)
	{
		StartMenuOptions option = m_hover.value();
		for (size_t i = 0; i < MENU_OPTIONS; i++)
		{
			if (i = option)
			{
				m_menuSelection[i]->setHoverColor();
			}
			else
				m_menuSelection[i]->setResetColor();
		}
		if (m_choice != std::nullopt)
		{
			setStatus(false);
		}
	}
	
	void handleEvents(sf::Event event)
	{
		if (event.KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				m_choice = m_hover;
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				m_hover = ++m_hover;
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				m_hover = --m_hover;
			}
		}
	}
	
	void draw(sf::RenderWindow& window)
	{
		for (auto& gui : m_menuSelection)
		{
			gui->draw(window);
		}
	}
	
	std::optional <StartMenuOptions> getChoice()
	{
		return m_choice;
	}

private:
	std::array<std::unique_ptr<Gui>, MENU_OPTIONS> m_menuSelection {};
	std::optional<StartMenuOptions> m_hover{ std::optional<StartMenuOptions>(NEW_GAME) };
	std::optional<StartMenuOptions> m_choice {std::nullopt};
	sf::Vector2i m_windowSize{ Resources::getInstance().getWindow().getSize() };
};
