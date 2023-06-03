#pragma once
#include "BaseState.h"
#include "guis/Gui.h"
#include <optional>
#include "StartState.h"
class StartMenuState : public BaseState
{
public:
	StartMenuState(StateMachine& states) : BaseState(states)
	{
		entry();
	}

	~StartMenuState ()
	{
	}
	 void entry() 
	 {
		//initilize guis

	 }
	 void exit() 
	 {
		 
	 }

	 void update(float dt) 
	 {
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
	 
	 }
	 std::optional <StartMenuOptions> getChoice()
	 {
		 return m_choice;
	 }
private:
	std::array<std::unique_ptr<Gui>, MENU_OPTIONS> m_menuSelection {};
	std::optional<StartMenuOptions> m_hover{ NEW_GAME };
	std::optional<StartMenuOptions> m_choice {std::nullopt};
	sf::Vector2i m_windowSize{ Resources::getInstance().getWindow().getSize() };
};
