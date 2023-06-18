#pragma once
#include "BaseState.h"
#include "../entity/Player.h"
#include "../Battle.h"
class EncounterBattleState : public BaseState
{
public:
	EncounterBattleState(Stack<BaseState>& states, Player& player)
		: BaseState(states), m_player(std::ref(player))
	{
	}

	~EncounterBattleState() = default;

	 void entry() override {
	 }
	 void exit()override {
	 }
	 void update(sf::Time dt)override {
	 }
	 void handleEvents(sf::Event event)override {
	 }
	 void draw(sf::RenderWindow& window)override {
	 }

private:
	std::reference_wrapper<Stack<BaseState>> m_states{ getStateStack() };
	Battle m_battle;
	std::reference_wrapper<Player> m_player;
};
