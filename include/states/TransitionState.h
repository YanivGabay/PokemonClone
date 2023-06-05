#pragma once

#include "BaseState.h"

#include "FadeInState.h"
#include "FadeOutState.h"
#include "Stack.h"

class TransitionState : public BaseState
{
public:
    TransitionState(Stack<BaseState>& states, std::unique_ptr<BaseState> nextState,sf::Color color)
        : BaseState(states),
          m_nextState(std::move(nextState)),
          m_fadeOutState(std::make_unique<FadeOutState>(states,color)),
          m_fadeInState(std::make_unique<FadeInState>(states,color))
    {}
    
    std::unique_ptr<BaseState> getNextState()
    {
        return std::move(m_nextState);
    }
    
    std::unique_ptr<BaseState> getFadeIn()
    {
        return std::move(m_fadeInState);
    }
    
    void update (sf::Time dt)override
    {
        if (m_fadeOutState->getStatus())
        {
            m_states.get().pushQueueState(getNextState());
            m_states.get().pushQueueState(getFadeIn());
            setStatus(false);
            exit();
        }
        else
        {
            m_fadeOutState->update(dt);
        }
    }
    
    void draw (sf::RenderWindow& window)override
    {
       
        m_fadeOutState->draw(window);
    }
    void entry()override
    {

     }
    void exit()override
    {

     }
  
     void handleEvents(sf::Event event)override
    {
         
    }
   

private:
    std::reference_wrapper<Stack<BaseState>> m_states{ getStateStack() };
    std::unique_ptr<BaseState> m_nextState;
    std::unique_ptr<BaseState> m_fadeOutState;
    std::unique_ptr<BaseState> m_fadeInState;
};
