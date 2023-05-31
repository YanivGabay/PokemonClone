#pragma once

#include <memory>
#include <vector>
#include "states/PlayState.h"
#include "states/StartState.h"
#include "states/State.h"
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/deep_history.hpp>
#include <boost/mpl/list.hpp>



struct StateMachine : public boost::statechart::state_machine<StateMachine, StartState>
{
public:
	StateMachine(){}

	~StateMachine(){}

	typedef boost::statechart::deep_history<PlayState> InitialState;
private:
	
};
