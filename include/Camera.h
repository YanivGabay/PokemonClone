#pragma once

#include <SFML/Graphics.hpp>

#include "Resources.h"
#include "utilities.h"


class Camera
{
public:
    Camera(float x, float y)
        : m_view(sf::FloatRect(x, y, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        m_view.setCenter(x, y);
    }

    Camera(float x, float y, float width, float height)
        : m_view(sf::FloatRect(x, y, width, height)) {}
    
    void update(float playerX, float playerY)
    {
        // Set the center of the view to the player's position
        m_view.setCenter(playerX, playerY);
    }

    void setView(sf::View& view)
    {
        m_view = view;
    }

    sf::View& getView()
    {
        return m_view;
    }

private:
    sf::View m_view;
};
