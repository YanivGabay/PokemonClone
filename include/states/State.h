#pragma once
#include "StateMachine.h"

class BaseState : boost::statechart::simple_state<BaseState, StateMachine>
{

	
	virtual void entry() = 0;
	virtual void exit() = 0;

	virtual void update() = 0;
	virtual void handleEvents() = 0;
	virtual void draw(sf::RenderWindow window) = 0;
};
