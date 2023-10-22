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
        
       // m_view.setSize()
        m_view.setCenter(x, y);
    }

    Camera(float x, float y, float width, float height)
        : m_view(sf::FloatRect(x, y, width, height)) {}
    
    void update(float playerX, float playerY)
    {
        // Set the center of the view to the player's position
        m_view.setCenter(playerX, playerY);
      
       
    }
    void setSize(std::pair<int, int> mapSize)
    {
        //m_view.setSize(sf::Vector2f(mapSize.first*16.65 , mapSize.second*15.65));
        
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
