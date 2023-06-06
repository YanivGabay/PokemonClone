#pragma once

#include "BaseState.h"


class FadeInState : public BaseState
{
public:
    FadeInState(Stack<BaseState>& states, sf::Color color)
        : BaseState(states),m_color(color)
    {
        m_fadeShape.setSize(sf::Vector2f(getWindowSize()));
        m_fadeShape.setFillColor(color);
    }

    ~FadeInState() = default;

    void entry()override {}
    void exit() override{}
    void update(sf::Time dt) override
    {
        float increment = 255.0f / 5.0f * dt.asSeconds(); // Adjust the fade-in speed as needed

        sf::Color shapeColor = m_fadeShape.getFillColor();
        shapeColor.a += static_cast<sf::Uint8>(increment);
        std::cout << "inside FFF fadeout ->update, alpha = " << static_cast<int>(shapeColor.a) << std::endl;

        if (shapeColor.a >= 255)
        {
            shapeColor.a = 255;
            setStatus(false); // Set the status to false to indicate that the fade-in is complete
        }

        m_fadeShape.setFillColor(shapeColor);
    }


    void handleEvents(sf::Event event) override {}

    void draw(sf::RenderWindow& window) override
    {
        std::cout << "inside FFF fateout ->draw" << std::endl;
        window.draw(m_fadeShape);
    }

private:
    sf::RectangleShape m_fadeShape;
    sf::Color m_color;
  float m_progress{ 0 };
  
};
