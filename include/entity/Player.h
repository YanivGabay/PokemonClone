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
          m_isMoving(false),m_pokemons(std::move(std::make_unique<Party>()))
    {
        setSprite(PlayerID::UP_IDLE);
        setOrigin();
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
           
            
            Side side = m_movingObj.getSide();
            if (side == UP)
            {
                setSprite(nextFrame(m_curr));
            }
            else if (side==DOWN)
            {
                setSprite(nextFrame(m_curr));
            }
            else if (side == RIGHT)
            {
                setSprite(nextFrame(m_curr));
            }
            else if (side == LEFT)
            {
                setSprite(nextFrame(m_curr));
            }
            
            if (getMoveProgress() >= 1.0f)
            {
                //check upper level and npc for collisions
                bool isValidPosition = !checkUppers(directionMap, side);
                if (isValidPosition)
                {
                   
                    b2Vec2 newPos = m_movingObj.getPos();
                    std::cout << "good movment" << std::endl;
                    setTargetPosition(sf::Vector2i(newPos.x, newPos.y));
                    setPositions(getTargetPosition());
                }
                else
                {
                    std::cout << "bad movment" << std::endl;
                    setTargetPosition(getPosition());
                    m_movingObj.setPosition(getPosition());
                }
                
                m_isMoving = false;
                setIdle();
                setMoveProgress(0.0f);
            }
        }
        else
        {
            //we are not moving
        }
    }
    void setSprite(PlayerID desiredSprite)
    {
        m_sprite.setTextureRect(Resources::getInstance().getRect(desiredSprite));
    }
    void setIdle()
    {
        Side side = m_movingObj.getSide();
        if (side == UP)
        {
            m_curr = PlayerID::UP_IDLE;
            
        }
        else if (side == DOWN)
        {
           
            m_curr = PlayerID::DOWN_IDLE;
            
        }
        else if (side == RIGHT)
        {
           
            m_curr = PlayerID::RIGHT_IDLE;
            
        }
        else if (side == LEFT)
        {
           
            m_curr = PlayerID::LEFT_IDLE;
            
        }
        setSprite(m_curr);
    }
    virtual void draw(sf::RenderWindow& window) override
    {
        sf::Vector2f pixelPosition = gridToPixelPosition(getPosition());
      
        m_sprite.setPosition(pixelPosition);
             
        
        window.draw(m_sprite);
    }
    std::shared_ptr<Pokemon> getPokemon(int index)
    {
        return m_pokemons->getPokemon(index);
    }
    std::shared_ptr<Pokemon> getStarterPokemon()
    {
        return m_pokemons->getStarterPokemon();
    }
    void addPokemon(std::shared_ptr<Pokemon> pokemon)
    {
        std::cout << "before add pokemon in player" << std::endl;
        m_pokemons->addPokemon(pokemon);
    }

    

    bool getIsMoving()
    {
        return m_isMoving;
    }
    void setMoving(bool value)
    {
        m_isMoving = value;
    }
private:
    bool m_isMoving;
    PlayerID m_curr{ PlayerID::UP_IDLE };
    std::unique_ptr<Party> m_pokemons;
};
