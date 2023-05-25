#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"
const float TILE_SIZE = 50.0f;

class Grid
{
public:
    Grid()
    {
        for (int j = 0; j < 20; j++)
        {
            for (int i = 0; i < 20; i++)
            {
                sf::RectangleShape shape(sf::Vector2f(50, 50));
                shape.setPosition(i * 50, j * 50);
                shape.setFillColor(sf::Color::White);
                shapes.push_back(shape);

            }
        }

    }
    void draw(sf::RenderWindow& window)
    {
        for (auto& shape : shapes)
        {
            window.draw(shape);
        }
    }
    sf::Vector2f gridToPixelPosition(sf::Vector2i gridPosition)
    {
        return sf::Vector2f(gridPosition.x * TILE_SIZE, gridPosition.y * TILE_SIZE);
    }
private:
    std::vector <sf::RectangleShape> shapes;
};

class Player
{
public:
    Player(Grid& grid) : grid(grid), isMoving(false), moveProgress(0.0f), moveSpeed(55.0f), position(0, 0) {}

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
        sf::Vector2f pixelPosition = grid.gridToPixelPosition(position);

        if (isMoving)
        {
            sf::Vector2f targetPixelPosition = grid.gridToPixelPosition(targetPosition);
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
    Grid& grid;
    sf::Vector2i position;
    sf::Vector2i targetPosition;
    bool isMoving;
    float moveProgress;
    float moveSpeed;
};