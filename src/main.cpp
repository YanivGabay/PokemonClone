#include <iostream>

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)

#include "Camera.h"
#include "entity/Player.h"
#include "world/TilesMap.h"
#include "Tile.h"
#include "Resources.h"


int main()
{
    sf::RenderWindow& m_window = Resources::getInstance().getWindow();

    TilesMap map = TilesMap();
    
    // Create the camera
    Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    Player myPlayer = Player();

    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // 60 fps
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Clock clock; // Start a clock for frame timing

    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }
        
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            myPlayer.handleInput();
            myPlayer.update(TimePerFrame);
        }
        
        sf::Vector2f playerPixelPosition = gridToPixelPosition(myPlayer.getPosition());

        camera.update(playerPixelPosition.x + TILE_SIZE / 2.0f, playerPixelPosition.y + TILE_SIZE / 2.0f);  // Center camera around the player's center

        m_window.setView(camera.getView());
        m_window.clear();

        map.draw(m_window);
        myPlayer.draw(m_window);
        
        // window.draw(shape);
        m_window.display();
    }

    return 0;
}
