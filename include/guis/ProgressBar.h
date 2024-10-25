#pragma once

#include "../Resources.h"




class ProgressBar {
public:
    ProgressBar(float x, float y, float width, float height, sf::Color backgroundColor, sf::Color barColor)
        : position(x, y), size(width, height)
    {
        m_text.setFont(Resources::getInstance().getFont());
        background.setFillColor(backgroundColor);
        background.setPosition(position);
        background.setSize(size);

        bar.setFillColor(barColor);
        bar.setPosition(position);
        bar.setSize(sf::Vector2f(0, height));
    }
    void setFraction(float progress)
    {
        m_fraction = progress / 100.0f;
    }
    float getFraction()
    {
        return m_fraction;
    }
    void setProgress(float progress)
    {
        setFraction(progress);
        if (progress == 0.0f)
        {
            m_text.setString("Empty");
            m_text.setFillColor(sf::Color::Yellow);
        }
        // Modify the bar size based on the fraction
        bar.setSize(sf::Vector2f(size.x * m_fraction, size.y));
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(background);
        window.draw(bar);
        if (m_fraction == 0.0f)
        {

        }
    }

private:
    float m_fraction = 0;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape background;
    sf::RectangleShape bar;
    sf::Text m_text;

    
};
