#pragma once

#include "BaseState.h"


class FadeOutState : public BaseState
{
public:
    FadeOutState(Stack<BaseState>& states, sf::Color color)
        : BaseState(states), m_color(color)
    {
        m_fadeShape.setSize(sf::Vector2f(getWindowSize()));
        m_fadeShape.setFillColor(sf::Color::Transparent);
    }

    ~FadeOutState() = default;

    void entry()override {}
    void exit() override {}
    void update(sf::Time dt) override
    {
        float increment = 255.0f / 200.0f * dt.asSeconds(); // Adjust the fade-in speed as needed
        m_progress += increment;
        sf::Color shapeColor = sf::Color::Transparent;
        shapeColor.r = static_cast<sf::Uint8>(m_progress * m_color.r);
        shapeColor.g = static_cast<sf::Uint8>(m_progress * m_color.g);
        shapeColor.b = static_cast<sf::Uint8>(m_progress * m_color.b);
        shapeColor.a = static_cast<sf::Uint8>(255.0f - m_progress * 255.0f);
        if (m_progress > 5)
        {
            shapeColor = m_color;
            setStatus(false); // Set the status to false to indicate that the fade-in is complete
        }

        m_fadeShape.setFillColor(shapeColor);
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
