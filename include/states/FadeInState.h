#pragma once
#include "BaseState.h"

class FadeInState : public BaseState
{
public:
    FadeInState(StateMachine& states, sf::Color color) : BaseState(states)
    {
        m_fadeShape.setSize(sf::Vector2f(getWindowSize()));
        m_fadeShape.setFillColor(color);
    }

    ~FadeInState() {}

    void entry() {}

    void exit() {}

    void update(sf::Time dt)
    {
        float increment = 255.0f / 1.0f * dt; // Adjust the fade-in speed as needed

        m_progress += static_cast<sf::Uint8>(increment);

        if (m_progress >= 255)
        {
            m_progress = 255;
            setStatus(false); // Set the status to false to indicate that the fade-in is complete
        }
    }

    void handleEvents(sf::Event event) {}

    void draw(sf::RenderWindow& window)
    {
        window.draw(m_fadeShape);
    }

private:
    sf::RectangleShape m_fadeShape;
    sf::Uint8 m_progress{ 0 };
  
};
