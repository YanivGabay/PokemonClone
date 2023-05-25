#pragma once
#include <memory>
#include <vector>
#include "State"
class StateMachine
{
public:
	StateMachine()
	{
	}

	~StateMachine()
	{
	}

private:
	std::vector <std::unique_ptr<State>> m_stateStack;

};
