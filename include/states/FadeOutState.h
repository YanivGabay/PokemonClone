#pragma once

#include <iostream>
#include "FadeInState.h"
#include "BaseState.h"
#include "Utilities/Fades.h"


class FadeOutState : public BaseState
{
public:
    FadeOutState(Stack<BaseState>& states, sf::Color color, bool withTransition)
        : BaseState(states), m_color(color), m_transition(withTransition)
    {
        m_color.a = 0;
        
        m_fadeShape.setSize(sf::Vector2f(getWindowSize().x*3, getWindowSize().y * 3));
        
        m_fadeShape.setFillColor(m_color);
    }

    virtual ~FadeOutState() = default;

    void entry() override {}
    void exit() override {}
    
    void update(sf::Time dt) override
    {
        float increment = MaxProgress / (FrameDuration * FramesPerSecond);
        
        m_progress += increment;
        
        sf::Color shapeColor = m_fadeShape.getFillColor();

        if (m_progress > 65535.0f)
        {
            m_progress = 65535.0f;
            if (!m_transition)
            {
                getStateStack().get().pushQueueState(std::move(std::make_unique<FadeInState>(getStateStack().get(), m_color)));
            }
            
            setStatus(false); // Set the status to false to indicate that the fade-in is complete
        }

        shapeColor.a = static_cast<sf::Uint8>(m_progress / 257.0f);
        
        m_fadeShape.setFillColor(shapeColor);
    }
    
    void handleEvents(sf::Event event) override {}
    
    void draw(sf::RenderWindow& window) override
    {
        window.draw(m_fadeShape);
    }

private:
    bool m_transition;
    float m_progress{ 0 };
    
    sf::RectangleShape m_fadeShape;
    sf::Color m_color;
};
