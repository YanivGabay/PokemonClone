#pragma once

#include <optional>
#include "BaseState.h"
#include "guis/Gui.h"
#include "StartState.h"
#include "Utilities/StartMenuOptions.h"
#include "SoundTon.h"


class StartMenuState : public BaseState
{
public:
	StartMenuState(Stack<BaseState>& states)
		: BaseState(states)
	{
		entry();
	}
	
	virtual ~StartMenuState() = default;
	
	void entry() override
	{
		sf::Vector2f buttonSize = sf::Vector2f(m_windowSize.x / 4, m_windowSize.y / 4);
		
		float x = (static_cast<float>(m_windowSize.x / 2) - (buttonSize.x / 2));
		
		for (size_t i = 0; i < MENU_OPTIONS; i++)
		{
			m_menuSelection[i] = std::move(std::make_unique<Gui>(Resources::getInstance().getFont() , buttonSize, sf::Vector2f(x, 50 + buttonSize.y * i)));
		}
		
		resetText();
	}
	
	void exit() override {}
	
	void update(sf::Time dt) override
	{
		StartMenuOptions option = m_hover.value();
		
		for (int i = 0; i < MENU_OPTIONS; i++)
		{
			if (i == option)
			{
				m_menuSelection[i]->setHoverColor();
			}
			else
			{
				m_menuSelection[i]->setResetColor();
			}
		}
		
		if (m_choice != std::nullopt)
		{
			setStatus(false);
		}
	}
	
	void handleEvents(sf::Event event) override
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				m_choice = m_hover;
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				SoundTon::getInstance().playSound(soundNames::MENU);
				m_hover = ++m_hover;
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				SoundTon::getInstance().playSound(soundNames::MENU);
				m_hover = --m_hover;
			}
		}
	}
	
	void draw(sf::RenderWindow& window) override
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

	void setLoadingText()
	{
		m_menuSelection[NEW_GAME]->setText("Loading...");
		m_menuSelection[LOAD_GAME]->setText("Loading..");
		m_menuSelection[QUIT]->setText("Loading.");
	}
	
	void resetText()
	{
		m_menuSelection[NEW_GAME]->setText("New Game");
		m_menuSelection[LOAD_GAME]->setText("Load Game");
		m_menuSelection[QUIT]->setText("Quit");
	}

private:
	std::array<std::unique_ptr<Gui>, MENU_OPTIONS> m_menuSelection {};

	std::optional<StartMenuOptions> m_hover{ NEW_GAME };
	std::optional<StartMenuOptions> m_choice {std::nullopt};
	
	sf::Vector2i m_windowSize{ Resources::getInstance().getWindow().getSize() };
};
