#pragma once
#include "BaseState.h"
#include "FadeInState.h"
#include "FadeOutState.h"
#include <boost/signals2.hpp>

class TransitionState : public BaseState
{
public:
    TransitionState(StateMachine& states, std::unique_ptr<BaseState> nextState,sf::Color color) :
        BaseState(states),
        m_nextState(std::move(nextState)),
        m_fadeOutState(std::make_unique<FadeOutState>(states,color)),
        m_fadeInState(std::make_unique<FadeInState>(states,color))
    {
        
    }
    std::unique_ptr<BaseState> getNextState()
    {
        return std::move(m_nextState);
    }
    std::unique_ptr<BaseState> getFadeIn()
    {
        return std::move(m_fadeInState);
    }
    void update(float dt)
    {
        if (m_fadeOutState->getStatus())
        {
           
            m_states.get().pushFadeOut(getNextState(),getFadeIn());
        }
        else
        {
            m_fadeOutState->update(dt);
        }
    }
    void draw(sf::RenderWindow& window) {
       
        m_fadeOutState->draw(window);
    }
   

private:
    std::reference_wrapper<StateMachine> m_states{ getStateMachine() };
    std::unique_ptr<BaseState> m_nextState;
    std::unique_ptr<BaseState> m_fadeOutState;
    std::unique_ptr<BaseState> m_fadeInState;
  
    
public:
      
};
