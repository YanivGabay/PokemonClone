#pragma once

#include <SFML/Graphics.hpp>

#include "utilities.h"
#include "Camera.h"
#include "Tile.h"
#include "world\TilesMap.h"
#include "world\TilesMap.h"
#include "PhysicsMove.h"
#include "Animation.h"
#include "Pokemon/Party.h"
#include "entity\Entity.h"


class NPC : public Entity
{
public:
    NPC()
        : Entity("resources/maleSpriteSheet.png"),
        m_isMoving(false)
    {}
    virtual ~NPC() = default;
    
    void AIMoving()
    {
        Side newSide = static_cast<Side>(rand() % (Side::RIGHT+1));
        
        switch (newSide)
        {
        case UP:
            m_movingObj.setMove(UP);
            break;
        case DOWN:
            m_movingObj.setMove(DOWN);
            break;
        case LEFT:
            m_movingObj.setMove(LEFT);
            break;
        case RIGHT:
            m_movingObj.setMove(RIGHT);
            break;
        default:
            break;
        }
    }

    bool checkUppers(const std::map<Side, bool>& directionMap, Side side)
    {
        return directionMap.at(side);
    }

    virtual void update(sf::Time dt, const std::map<Side, bool>& directionMap) override
    {
        addMoveProgress(getMoveSpeed(), dt);
        // m_moveProgress += (m_moveSpeed * dt.asSeconds());
        Side side = m_movingObj.getSide();
        if (side == UP)
        {
            setSprite(PlayerID::UP_IDLE);
        }
        else if (side == DOWN)
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
            
            setMoveProgress(0.0f);
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

    // Party m_pokemons;
};
