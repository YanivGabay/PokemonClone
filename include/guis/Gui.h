#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include "Resources.h"


class Gui
{
public:

    Gui(const sf::Font& font) : m_font(font), m_frameBoxRects(Resources::getInstance().getFrameCord()) , m_frameTexture(Resources::getInstance().getTexture("framesSpritesheet.png"))
    {
        m_text.setFont(m_font);
        m_text.setCharacterSize(30);
        m_text.setFillColor(sf::Color::White);
    }

    void setText(const std::string& text)
    {
        m_text.setString(text);
        // Adjust the position of the text if needed
        m_text.setPosition(m_position.x, m_position.y);
    }

    void setPosition(float x, float y)
    {
        m_position.x = x;
        m_position.y = y;
        m_text.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(m_text);
    }

private:
    sf::Text m_text;
    sf::Texture& m_frameTexture;
    std::unordered_map<FrameID, sf::IntRect>& m_frameBoxRects;
    sf::Vector2f m_position;
    const sf::Font& m_font;
};
