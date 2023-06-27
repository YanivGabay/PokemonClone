#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include "ProgressBar.h"
#include "Resources.h"
#include "Button.h"


class Gui {
public:
    Gui(const sf::Font& font, sf::Vector2f buttonSize, sf::Vector2f buttonPosition)
        : m_font(font),
          m_button(std::move(std::make_unique<Button>(buttonSize,buttonPosition))),
          m_color(sf::Color::Black)
    {
        m_text.setFont(m_font);
        m_text.setCharacterSize(30);
        setPosition(buttonPosition.x + TILE_SIZE, buttonPosition.y+TILE_SIZE);
    }
    
    void setResetColor()
    {
        m_text.setFillColor(m_color);
    }
    
    void setHoverColor()
    {
        m_text.setFillColor(sf::Color::Blue);
    }
    
    void setText(const std::string& text)
    {
        m_text.setString(text);
        
        // Adjust the position of the text if needed
        m_text.setPosition(m_position.x, m_position.y);
    }
    
    void setSize(unsigned int size)
    {
        m_text.setCharacterSize(size);
    }
    
    void setPosition(float x, float y)
    {
        m_position.x = x;
        m_position.y = y;
        m_text.setPosition(x, y);
    }
    
    void setTextSize(unsigned int value)
    {
        m_text.setCharacterSize(value);
    }
    
    void addProgressBar(float x, float y, float width, float height, sf::Color backgroundColor, sf::Color barColor,float progressValue)
    {
        m_progressBar = std::make_unique<ProgressBar>(x, y, width, height, backgroundColor, barColor);
        m_hasProgressBar = true;
        m_progressBar->setProgress(progressValue);
    }
    
    void draw(sf::RenderWindow& window)
    {
        m_button->draw(window);
       
        window.draw(m_text);

        if (m_hasProgressBar)
        {
            m_progressBar->draw(window);
        }
    }
    
    sf::Vector2f getSize()
    {
       return m_button->getSize();
    }
    
    sf::Vector2f getPosition()
    {
        return m_position;
    }
    
    void setProgress(float progress)
    {
        if (progress > 100 || progress < 0)
        {
            throw std::runtime_error("progress out of range.");
        }
        
        m_progressBar->setProgress(progress);
    }

private:
    sf::Color m_color;
    sf::Text m_text;

    //progress bar
    std::unique_ptr<ProgressBar> m_progressBar;
    bool m_hasProgressBar{ false };

    std::unique_ptr<Button> m_button;
    sf::Vector2f m_position;
    const sf::Font& m_font;
};
