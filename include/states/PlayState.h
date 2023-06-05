#pragma once

#include "BaseState.h"
#include "world/TilesMap.h"


class PlayState : public BaseState
{
public:
	PlayState(Stack<BaseState>& states) :BaseState(states){}

	~PlayState() = default;
	 void entry(){}
	 void exit(){}
	 void update(sf::Time dt){}
	 void handleEvents(sf::Event event){}
	 void draw(sf::RenderWindow& window){}
private:
	//std::unique_ptr<Level> m_currentLevel;
	std::reference_wrapper<Stack<BaseState>> m_states{ getStateStack() };
};
