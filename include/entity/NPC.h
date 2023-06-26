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
        : Entity("resources/maleSpriteSheet.png")
       
    {}
    virtual ~NPC() = default;
    
    void setMovable(bool value)
    {
        m_movable = value;
    }
   
    bool checkUppers(const std::map<Side, bool>& directionMap, Side side)
    {
        return directionMap.at(side);
    }

    virtual void update(sf::Time dt, const std::map<Side, bool>& directionMap) override
    {
       
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
   
    bool m_movable{ true };
    // Party m_pokemons;
};
