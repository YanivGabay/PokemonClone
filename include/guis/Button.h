#pragma once

#include "Resources.h"


class Button
{
public:
    Button(sf::Vector2f guiSize,sf::Vector2f position)
        : m_frameBoxRects(Resources::getInstance().getFrameCord()),
          m_size(guiSize),
          m_startPosition(position),
          m_texture(Resources::getInstance().getTexture("resources/framesSpritesheet.png"))
    {
		init();
	}

    void init()
    {
        auto sizeVector = sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2);
        auto middle = createSprite(FrameID::MIDDLE);
        
        middle->setPosition(m_startPosition);
        m_shapes.push_back(std::move(middle));

        auto createSprite = [&](FrameID frameID, const sf::Vector2f& position) {
            auto rect = *m_frameBoxRects[frameID];
           auto sprite = std::make_unique<sf::Sprite>(m_texture, rect);
            sprite->setPosition(position);
            m_shapes.push_back(std::move(sprite));
        };

        // Calculate the position of each part of the frame based on m_startPosition and m_size
        const float startX = m_startPosition.x + sizeVector.x;
        const float startY = m_startPosition.y + sizeVector.y;
        const float endX = m_startPosition.x + m_size.x - sizeVector.x-2;
        const float endY = m_startPosition.y + m_size.y - sizeVector.y;

        // Corners
        createSprite(FrameID::LEFT_UP_CORNER, sf::Vector2f(m_startPosition.x, m_startPosition.y));
        createSprite(FrameID::RIGHT_UP_CORNER, sf::Vector2f(endX, m_startPosition.y));
        createSprite(FrameID::LEFT_DOWN_CORNER, sf::Vector2f(m_startPosition.x, endY));
        createSprite(FrameID::RIGHT_DOWN_CORNER, sf::Vector2f(endX, endY));

        // Horizontal lines
        for (float x = startX; x < endX; x += sizeVector.x)
        {
            createSprite(FrameID::UP_HORIZ, sf::Vector2f(x, m_startPosition.y));
            createSprite(FrameID::DOWN_HORIZ, sf::Vector2f(x, endY));
        }
        
        // Vertical lines
        for (float y = startY; y < endY; y += sizeVector.y)
        {
            createSprite(FrameID::LEFT_VERTICAL, sf::Vector2f(m_startPosition.x, y));
            createSprite(FrameID::RIGHT_VERTICAL, sf::Vector2f(endX, y));
        }
        
        // Fill between the lines
        for (float x = startX; x < endX; x += sizeVector.x)
        {
            for (float y = startY; y < endY; y += sizeVector.y)
            {
                createSprite(FrameID::MIDDLE, sf::Vector2f(x, y));
            }
        }
    }

    ~Button() = default;
    
    void draw(sf::RenderWindow& window)
	{
		for (const auto& shape : m_shapes)
		{
			window.draw(*shape);
		}
	}

private:
    sf::Texture& m_texture;
    std::vector<std::unique_ptr<sf::Sprite>> m_shapes;
	sf::Vector2f m_startPosition;
	sf::Vector2f m_size;
	std::unordered_map<FrameID, std::unique_ptr<sf::IntRect>>& m_frameBoxRects;

    std::unique_ptr<sf::Sprite> createSprite(FrameID frameID)
    {
        auto rect = *m_frameBoxRects[frameID];
        auto sprite = std::make_unique<sf::Sprite>(m_texture, rect);
        return sprite;
    }
};
