#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Tile.h"
#include "world\TilesMap.h"


class Player
{
public:
    Player()
        : m_isMoving(false), m_moveProgress(0.0f), m_moveSpeed(15.0f), m_position(15, 15) {};

    void handleInput()
    {
        if (!m_isMoving)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                m_targetPosition = sf::Vector2i(m_position.x - 1, m_position.y);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                m_targetPosition = sf::Vector2i(m_position.x + 1, m_position.y);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                m_targetPosition = sf::Vector2i(m_position.x, m_position.y - 1);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                m_targetPosition = sf::Vector2i(m_position.x, m_position.y + 1);
            else
                return;

            m_isMoving = true;
        }
    }

    void update(sf::Time dt)
    {
        if (m_isMoving)
        {
            m_moveProgress += (m_moveSpeed * dt.asSeconds());

            if (m_moveProgress >= 1.0f)
            {
                m_position = m_targetPosition;
                m_isMoving = false;
                m_moveProgress = 0.0f;
            }
        }
    }

    void draw(sf::RenderWindow& window)
    {
        sf::Vector2f pixelPosition = gridToPixelPosition(m_position);
        
        if (m_isMoving)
        {
            sf::Vector2f targetPixelPosition = gridToPixelPosition(m_targetPosition);
            
            pixelPosition += ((targetPixelPosition - pixelPosition) * m_moveProgress);
        }

        sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(pixelPosition);
        
        window.draw(shape);
    }

    sf::Vector2i getPosition()
    {
        return m_position;
    }

private:
    sf::Vector2i m_position;
    sf::Vector2i m_targetPosition;

    bool m_isMoving;
    float m_moveProgress;
    float m_moveSpeed;
};
