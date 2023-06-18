#pragma once
#include "BaseState.h"

class BattleState : public BaseState
{
public:
	BattleState : 
	{
	}

	~BattleState : 
	{
	}

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
};
