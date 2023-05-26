#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Tile.h"
#include "world\TilesMap.h"




class Player
{
public:
    Player() : isMoving(false), moveProgress(0.0f), moveSpeed(55.0f), position(0, 300) {};

    void handleInput()
    {
        if (!isMoving)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                targetPosition = sf::Vector2i(position.x - 1, position.y);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                targetPosition = sf::Vector2i(position.x + 1, position.y);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                targetPosition = sf::Vector2i(position.x, position.y - 1);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                targetPosition = sf::Vector2i(position.x, position.y + 1);
            else
                return;

            isMoving = true;
        }
    }

    void update(sf::Time dt)
    {
        if (isMoving)
        {
            moveProgress += moveSpeed * dt.asSeconds();

            if (moveProgress >= 1.0f)
            {
                position = targetPosition;
                isMoving = false;
                moveProgress = 0.0f;
            }
        }
    }

    void draw(sf::RenderWindow& window)
    {
        sf::Vector2f pixelPosition = gridToPixelPosition(position);

        if (isMoving)
        {
            sf::Vector2f targetPixelPosition = gridToPixelPosition(targetPosition);
            pixelPosition += (targetPixelPosition - pixelPosition) * moveProgress;
        }

        sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(pixelPosition);
        window.draw(shape);
    }
    sf::Vector2i getPosition()
    {
        return position;
    }

private:
    
    sf::Vector2i position;
    sf::Vector2i targetPosition;
    bool isMoving;
    float moveProgress;
    float moveSpeed;
};