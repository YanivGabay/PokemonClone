#pragma once
#include <SFML/Graphics.hpp>

const int TILE_SIZE = 32;
const float SCREEN_WIDTH = 800;
const float SCREEN_HEIGHT = 600;

class Camera
{
public:
    Camera(float x, float y, float width, float height)
    {
        view.reset(sf::FloatRect(x, y, width, height));
    }

    void update(float playerX, float playerY)
    {
        // Set the center of the view to the player's position
        view.setCenter(playerX, playerY);
    }

    sf::View& getView()
    {
        return view;
    }

private:
    sf::View view;
};