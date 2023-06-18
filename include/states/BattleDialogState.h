#pragma once
#include "BaseState.h"
#include "../Resources.h"

class BattleDialogState : public BaseState
{
public:
	BattleDialogState(Stack<BaseState>& states)
		: BaseState(states)
	{
	}

	~BattleDialogState()
	{
	};

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
