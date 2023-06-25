#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Tile.h"
#include "world\TilesMap.h"
#include "world\TilesMap.h"
#include "PhysicsMove.h"
#include "Animation.h"
#include "Pokemon/Party.h"


sf::Vector2f gridToPixelPosition(sf::Vector2i gridPosition)
{
    return sf::Vector2f(gridPosition.x * TILE_SIZE, gridPosition.y * TILE_SIZE);
}

class Entity {
public:
    Entity(const std::string myTexture)
        : m_moveProgress(0.0f),
          m_moveSpeed(15.0f),
          m_position(11, 48),
          m_targetPixelPosition(gridToPixelPosition(m_targetPosition)),
          m_movingObj(11, 48),
          m_sprite(Resources::getInstance().getTexture(myTexture))
         
    {
        m_sprite.setOrigin(0, m_sprite.getTextureRect().height / 2);
    }
    
    virtual ~Entity() = default;

    virtual void draw(sf::RenderWindow&) = 0;
    virtual void update(sf::Time, const std::map<Side, bool>&) = 0;
    
    void setSprite(PlayerID desiredSprite)
    {
        m_sprite.setTextureRect(Resources::getInstance().getRect(desiredSprite));
    }

    sf::Vector2i getPosition()
    {
        return m_position;
    }

    const float getMoveProgress()
    {
        return m_moveProgress;
    }

    void setMoveProgress(float progress)
    {
        m_moveProgress = progress;
    }

    void setTargetPosition(sf::Vector2i target)
    {
        m_targetPosition = target;
    }

    void setPosition(sf::Vector2i targetPos)
    {
        m_position = targetPos;
    }

    sf::Vector2i getTargetPosition()
    {
        return m_targetPosition;
    }

    void addMoveProgress(float progress,  sf::Time dt)
    {
        m_moveProgress += (m_moveSpeed * dt.asSeconds());
    }

    float getMoveSpeed()
    {
        return m_moveSpeed;
    }

protected:
    PhysicsMove m_movingObj;
    sf::Sprite m_sprite;

private:
    sf::Vector2i m_position;
    sf::Vector2i m_targetPosition;
    
    sf::Vector2f m_targetPixelPosition;

    float m_moveProgress;
    float m_moveSpeed;
};
