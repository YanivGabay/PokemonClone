#include "Camera.h"
#include <iostream>
#include "entity/Player.h"
#include "world/TilesMap.h"
#include "Tile.h"
// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)
int main()
{
    

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Grid Movement Game");
    window.setFramerateLimit(60);
    TilesMap map = TilesMap();
    // Create the camera
    Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  
   
    Player myPlayer = Player();

    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // 60 fps
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    sf::Clock clock; // Start a clock for frame timing
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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
        window.setView(camera.getView());

        window.clear();
        map.draw(window);
        myPlayer.draw(window);
       
       
       // window.draw(shape);
        window.display();
    }

    return 0;
}
