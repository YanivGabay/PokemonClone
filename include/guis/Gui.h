#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include "Resources.h"
#include "Button.h"

class Gui
{
public:

    Gui(const sf::Font& font,
        sf::Vector2f buttonSize,sf::Vector2f buttonPosition) : m_font(font),m_frameTexture(Resources::getInstance().getTexture("framesSpritesheet.png")),
                                                                                    m_button(std::move(std::make_unique<Button>(buttonSize,buttonPosition,m_frameTexture))),
                                                                                    m_color(sf::Color::Black)
    {
        m_text.setFont(m_font);
        m_text.setCharacterSize(30);
        m_text.setFillColor(sf::Color::Black);
        setPosition(buttonPosition.x, buttonPosition.y+TILE_SIZE);
        
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

    void draw(sf::RenderWindow& window)
    {
        m_button->draw(window);
        window.draw(m_text);
    }

private:
    sf::Color m_color;
    sf::Text m_text;
    sf::Texture m_frameTexture;
    std::unique_ptr<Button> m_button;
    sf::Vector2f m_position;
    const sf::Font& m_font;
};
