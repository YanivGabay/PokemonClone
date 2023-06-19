#pragma once
#include "BaseState.h"
#include "../entity/Player.h"
#include "../Battle.h"
class EncounterBattleState : public BaseState
{
public:
	EncounterBattleState(Stack<BaseState>& states, Player& player,Pokemon& enemy)
		: BaseState(states), m_player(player),m_battle(std::move(std::make_unique<Battle>(player.getPokemon(1), enemy)))
	{
		
	}

	~EncounterBattleState() = default;

	 void entry() override {}
	 void exit()override {}
	 void update(sf::Time dt)override {
	 }
	 void handleEvents(sf::Event event)override {
	 }
	 void draw(sf::RenderWindow& window)override {
		 m_battle->draw(window);
	 }

private:
	std::reference_wrapper<Stack<BaseState>> m_states{ getStateStack() };
	std::unique_ptr<Battle> m_battle;
	std::reference_wrapper<Player> m_player;
};
