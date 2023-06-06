#pragma once

#include "BaseState.h"
#include "Utilities/Fades.h"

class FadeOutState : public BaseState
{
public:
    FadeOutState(Stack<BaseState>& states, sf::Color color)
        : BaseState(states), m_color(color)
    {
        m_color.a = 0;
        m_fadeShape.setSize(sf::Vector2f(getWindowSize()));
        m_fadeShape.setFillColor(m_color);
    }

    ~FadeOutState() = default;

    void entry()override {}
    void exit() override {}
    void update(sf::Time dt) override
    {
        float increment = MaxProgress / (FrameDuration * FramesPerSecond);
        m_progress += increment;

        sf::Color shapeColor = m_fadeShape.getFillColor();

        if (m_progress > 65535.0f)
        {
            m_progress = 65535.0f;
            setStatus(false); // Set the status to false to indicate that the fade-in is complete
        }

        shapeColor.a = static_cast<sf::Uint8>(m_progress / 257.0f);
        m_fadeShape.setFillColor(shapeColor);

        // Print out debug information
        std::cout << "Alpha value: " << (int)shapeColor.a << std::endl;
        std::cout << "Increment: " << increment << std::endl;
    }




    void handleEvents(sf::Event event) override {}

    void draw(sf::RenderWindow& window) override
    {
        std::cout << "inside FFF fadeout->draw" << std::endl;
        window.draw(m_fadeShape);
    }

private:
    sf::RectangleShape m_fadeShape;
    sf::Color m_color;
    float m_progress{ 0 };

};
