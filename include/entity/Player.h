#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Tile.h"
#include "world\TilesMap.h"
#include "PhysicsMove.h"


class Player
{
public:
    Player()
        : m_isMoving(false), m_moveProgress(0.0f), m_moveSpeed(15.0f), m_position(15, 15), m_shape(sf::Vector2f(TILE_SIZE, TILE_SIZE)), m_targetPixelPosition(gridToPixelPosition(m_targetPosition))
    {
        m_shape.setFillColor(sf::Color::Red);
    }

    void handleInput()
    {
        if (!m_isMoving)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                m_movingObj.setMove();

                m_targetPosition = sf::Vector2i(m_movingObj.getPos().x - 1, m_movingObj.getPos().y);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                m_movingObj.setMove();

                m_targetPosition = sf::Vector2i(m_movingObj.getPos().x + 1, m_movingObj.getPos().y);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                m_movingObj.setMove();

                m_targetPosition = sf::Vector2i(m_movingObj.getPos().x, m_movingObj.getPos().y - 1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                m_movingObj.setMove();

                m_targetPosition = sf::Vector2i(m_movingObj.getPos().x, m_movingObj.getPos().y + 1);
            }
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
            //sf::Vector2f targetPixelPosition = gridToPixelPosition(m_targetPosition);
            
            pixelPosition += ((m_targetPixelPosition - pixelPosition) * m_moveProgress);
        }

        m_shape.setPosition(m_movingObj.getPos().x, m_movingObj.getPos().y);
        m_shape.setRotation(m_movingObj.getAngle());
        
        window.draw(m_shape);
    }

    sf::Vector2i getPosition()
    {
        return m_position;
    }

private:
    sf::Vector2i m_position;
    sf::Vector2i m_targetPosition;

    sf::Vector2f m_targetPixelPosition;

    bool m_isMoving;
    float m_moveProgress;
    float m_moveSpeed;

    PhysicsMove m_movingObj;

    sf::RectangleShape m_shape;
};
