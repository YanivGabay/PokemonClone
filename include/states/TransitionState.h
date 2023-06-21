#pragma once

#include "BaseState.h"
#include "FadeInState.h"
#include "FadeOutState.h"
#include "Stack.h"


class TransitionState : public BaseState
{
public:
    TransitionState(Stack<BaseState>& states, std::unique_ptr<BaseState> nextState, sf::Color color)
        : BaseState(states),
          m_nextState(std::move(nextState)),
          m_fadeOutState(std::make_unique<FadeOutState>(states,color)),
          m_fadeInState(std::make_unique<FadeInState>(states,color)) {}
    
    ~TransitionState() = default;
    
    std::unique_ptr<BaseState> getNextState()
    {
        return std::move(m_nextState);
    }
    
    std::unique_ptr<BaseState> getFadeIn()
    {
        return std::move(m_fadeInState);
    }
    
    void update (sf::Time dt) override
    {
        if (m_fadeOutState->getStatus())
        {
            m_fadeOutState->update(dt);
        }
        else
        {
           
            exit();
        }
    }
    
    void draw (sf::RenderWindow& window) override
    {
        m_fadeOutState->draw(window);
    }
    
    void entry() override {}
    void exit() override {
      
        getStateStack().get().pushQueueState(getNextState());
        getStateStack().get().pushQueueState(getFadeIn());
        setStatus(false);
        getStateStack().get().printTypeOf();
    }
    
    void handleEvents(sf::Event event) override {}

private:
    std::unique_ptr<BaseState> m_currState;
    std::unique_ptr<BaseState> m_nextState;
    std::unique_ptr<BaseState> m_fadeOutState;
    std::unique_ptr<BaseState> m_fadeInState;
};
