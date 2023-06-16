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

class Player
{
public:
    Player()
        : m_isMoving(false),
          m_moveProgress(0.0f),
          m_moveSpeed(15.0f),
          m_position(11, 48),
          m_targetPixelPosition(gridToPixelPosition(m_targetPosition)),
          m_movingObj(11,48),
          m_sprite(Resources::getInstance().getTexture("resources/maleSpriteSheet.png"), Resources::getInstance().getRect(PlayerID::UP_IDLE)) {

       
        m_sprite.setOrigin(0, m_sprite.getTextureRect().height/2);
    }
    
    void handleInput()
    {
        if (!m_isMoving)
        {
          
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                m_movingObj.setMove(LEFT);
               
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                m_movingObj.setMove(RIGHT);
               
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                m_movingObj.setMove(UP);
                
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                m_movingObj.setMove(DOWN);
               
            }
            else
                return;
          
            m_isMoving = true;
        }
    }
    bool checkUppers(const std::map<Side, bool>& directionMap,Side side)
    {
        return directionMap.at(side);
    }
    void update(sf::Time dt, const std::map<Side, bool>& directionMap)
    {
        if (m_isMoving)
        {
            m_moveProgress += (m_moveSpeed * dt.asSeconds());
            
            Side side = m_movingObj.getSide();
            if (side == UP)
            {
                setSprite(PlayerID::UP_IDLE);
            }
            else if (side==DOWN)
            {
                setSprite(PlayerID::DOWN_IDLE);
            }
            else if (side == RIGHT)
            {
                setSprite(PlayerID::RIGHT_IDLE);
            }
            else if (side == LEFT)
            {
                setSprite(PlayerID::LEFT_IDLE);
            }
            
            if (m_moveProgress >= 1.0f)
            {
                //check upper level and npc for collisions
                bool isValidPosition = !checkUppers(directionMap, side);
                if (isValidPosition)
                {
                    std::cout << "valid position" << std::endl;
                    b2Vec2 newPos = m_movingObj.getPos();
                    m_targetPosition = sf::Vector2i(newPos.x, newPos.y);
                    m_position = m_targetPosition;
                   
                }
                else
                {
                    std::cout << "not valid position" << std::endl;
                    m_targetPosition = m_position;
                    m_movingObj.setPosition(m_position);
                }
               
                
                m_isMoving = false;
                m_moveProgress = 0.0f;
            }
        }
        else
        {
           
            //we are not moving
        }
    }

    void draw(sf::RenderWindow& window)
    {
        sf::Vector2f pixelPosition = gridToPixelPosition(m_position);
      
        m_sprite.setPosition(pixelPosition);

       // m_shape.setPosition(pixelPosition);
      //  m_shape.setRotation(m_movingObj.getAngle());
        
        window.draw(m_sprite);
    }
    
    sf::Vector2i getPosition()
    {
        return m_position;
    }
    
    void setSprite(PlayerID desiredSprite)
    {
        m_sprite.setTextureRect(Resources::getInstance().getRect(desiredSprite));
    }

private:
    sf::Vector2i m_position;
    sf::Vector2i m_targetPosition;
    sf::Sprite m_sprite;
    sf::Vector2f m_targetPixelPosition;

    bool m_isMoving;
    float m_moveProgress;
    float m_moveSpeed;
   
    PhysicsMove m_movingObj;

   // Party m_pokemons;
};
