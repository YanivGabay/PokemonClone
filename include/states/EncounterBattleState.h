#pragma once
#include "BaseState.h"
#include "../entity/Player.h"
#include "../Battle.h"
class EncounterBattleState : public BaseState
{
public:
	EncounterBattleState(Stack<BaseState>& states, Player& player,Pokemon& enemy)
		: BaseState(states), m_player(player),m_battle(std::move(std::make_unique<Battle>(player.getPokemon(0), enemy)))
	{
		entry();
	}

	~EncounterBattleState() = default;

	 void entry() override {
		
	 }
	 void exit()override {
		 m_window.setView(m_originalView);
	 }
	 void update(sf::Time dt)override {
	 }
	 void handleEvents(sf::Event event)override {
		 if (event.type == sf::Event::KeyReleased)
		 {
			 if (event.key.code == sf::Keyboard::Enter)
			 {
				 setStatus(false);
				 exit();
			 }
			
		 }
	 }
	 void draw(sf::RenderWindow& window)override {
		 m_window.setView(m_window.getDefaultView());
		 m_battle->draw(window);
	 }

private:
	sf::RenderWindow& m_window{ Resources::getInstance().getWindow() };
	sf::View m_originalView{ m_window.getView() };

	std::reference_wrapper<Stack<BaseState>> m_states{ getStateStack() };
	std::unique_ptr<Battle> m_battle;
	std::reference_wrapper<Player> m_player;
};
