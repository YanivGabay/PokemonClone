#include "Camera.h"
#include <iostream>
#include "entity/Player.h"



int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Grid Movement Game");
    window.setFramerateLimit(60);

    // Create the camera
    Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    sf::RectangleShape shape(sf::Vector2f(50, 50));
    shape.setPosition(1000, 800);
    shape.setFillColor(sf::Color::Green);
    Grid grid;
    Player player(grid);

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

            player.handleInput();
            player.update(TimePerFrame);
        }

        sf::Vector2f playerPixelPosition = grid.gridToPixelPosition(player.getPosition());

        camera.update(playerPixelPosition.x + TILE_SIZE / 2.0f, playerPixelPosition.y + TILE_SIZE / 2.0f);  // Center camera around the player's center
        window.setView(camera.getView());

        window.clear();
        grid.draw(window);
        player.draw(window);
        window.draw(shape);
        window.display();
    }

    return 0;
}
