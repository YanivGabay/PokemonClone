#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Tile.h"
#include "world\TilesMap.h"
#include "Animation.h"
#include "Pokemon/Party.h"
#include "entity\Entity.h"
#include "SoundTon.h"


class Player : public Entity {
public:
    Player(std::unique_ptr<Party> pokemons)
        : Entity("resources/maleSpriteSheet.png"),
          m_isMoving(false),
          m_pokemons(std::move(pokemons))
    {
        setSprite(PlayerID::UP_IDLE);
        setOrigin();
    }

    Player()
        : Entity("resources/maleSpriteSheet.png"),
          m_isMoving(false),
          m_pokemons(std::move(std::make_unique<Party>()))
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
                Entity::setMove(LEFT);
               
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                Entity::setMove(RIGHT);
               
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                Entity::setMove(UP);
                
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                Entity::setMove(DOWN);
               
            }
            else
            {
                return;
            }
           
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
            
            Side side = Entity::getSide();
            
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
                    
                   
                    setTargetPosition(getNextPosition(Entity::getPosition(), Entity::getSide()));
                    setPositions(getTargetPosition());
                }
                else
                {
                    setTargetPosition(getPosition());
                    
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
    sf::Vector2i getNextPosition(sf::Vector2i position,Side side)
    {
        sf::Vector2i new_posi = position;
        switch (side)
        {
            case UP:
                new_posi.y--;
                break;
            case DOWN:
                new_posi.y++;
                break;
            case LEFT:
                new_posi.x--;
                break;
            case RIGHT:
                new_posi.x++;
                break;
            default:
                break;
        }
        return new_posi;

    }
    
    void setSprite(PlayerID desiredSprite)
    {
        m_sprite.setTextureRect(Resources::getInstance().getRect(desiredSprite));
    }
    
    void setIdle()
    {
        Side side = Entity::getSide();
        
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
        m_pokemons->addPokemon(pokemon);
    }
    
    void healPokemons()
    {
        m_pokemons->healPokemon();
    }
    
    bool getIsMoving()
    {
        return m_isMoving;
    }

    void setMoving(bool value)
    {
        m_isMoving = value;
    }

    int getPartySize()
    {
        return  m_pokemons->getPartySize();
    }

private:
    bool m_isMoving;
    PlayerID m_curr{ PlayerID::UP_IDLE };
    std::unique_ptr<Party> m_pokemons;
};
