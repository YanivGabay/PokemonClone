#pragma once

#include <iostream>

#include "BaseState.h"
#include "Utilities/Fades.h"


class FadeInState : public BaseState
{
public:
    FadeInState(Stack<BaseState>& states, sf::Color color)
        : BaseState(states),m_color(color)
    {
        std::cout << "FadeInState c-tor" << std::endl;

        m_fadeShape.setSize(sf::Vector2f(getWindowSize()));
        m_fadeShape.setFillColor(color);
    }

    ~FadeInState() = default;

    void entry() override {}
    void exit() override {}
    
    void update(sf::Time dt) override
    {
        std::cout << "FadeInState update" << std::endl;

        float increment = MaxProgress / (FrameDuration * FramesPerSecond);

        m_progress -= increment;
        m_color.a = static_cast<sf::Uint8>(m_progress / 257.0f);
        m_fadeShape.setFillColor(m_color);
        
        if (m_progress <= 0.0f)
        {
            m_color.a = 0;
            setStatus(false); // Set the status to false to indicate that the fade-in is complete
        }
    }
    
    void handleEvents(sf::Event event) override {}
    
    void draw(sf::RenderWindow& window) override
    {
        std::cout << "FadeInState draw" << std::endl;
        window.draw(m_fadeShape);
    }

private:
    sf::RectangleShape m_fadeShape;
    sf::Color m_color;
    float m_progress{ 65535.0f };
};
