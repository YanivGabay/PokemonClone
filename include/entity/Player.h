#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Tile.h"
#include "world\TilesMap.h"
#include "world\TilesMap.h"
#include "PhysicsMove.h"
#include "Animation.h"
#include "Pokemon/Party.h"

#include "entity\Entity.h"
#include "SoundTon.h"


class Player : public Entity
{
public:
    Player()
        : Entity("resources/maleSpriteSheet.png"),
          m_isMoving(false)
    {
    }
    
    virtual ~Player() = default;
    
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

    virtual void update(sf::Time dt, const std::map<Side, bool>& directionMap) override
    {
        if (m_isMoving)
        {
            addMoveProgress(getMoveSpeed(), dt);
            // m_moveProgress += (m_moveSpeed * dt.asSeconds());
            
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
            
            if (getMoveProgress() >= 1.0f)
            {
                //check upper level and npc for collisions
                bool isValidPosition = !checkUppers(directionMap, side);
                if (isValidPosition)
                {
                    std::cout << "valid position" << std::endl;
                    b2Vec2 newPos = m_movingObj.getPos();
                    
                    setTargetPosition(sf::Vector2i(newPos.x, newPos.y));
                    setPosition(getTargetPosition());
                }
                else
                {
                    std::cout << "not valid position" << std::endl;
                    setTargetPosition(getPosition());
                    m_movingObj.setPosition(getPosition());
                }
                
                m_isMoving = false;
                setMoveProgress(0.0f);
            }
        }
        else
        {
            //we are not moving
        }
    }

    virtual void draw(sf::RenderWindow& window) override
    {
        sf::Vector2f pixelPosition = gridToPixelPosition(getPosition());
      
        m_sprite.setPosition(pixelPosition);


       // m_shape.setPosition(pixelPosition);
       // m_shape.setRotation(m_movingObj.getAngle());
        
        window.draw(m_sprite);
    }

private:
    bool m_isMoving;

    std::unique_ptr<Party> m_pokemons;
};
