#include "Camera.h"
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pokemon Game");

    // Create the camera
    Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sf::RectangleShape player(sf::Vector2f(50, 50));
    sf::RectangleShape test(sf::Vector2f(50, 50));
    test.setPosition(sf::Vector2f(1000, 1000));

    sf::RectangleShape test2(sf::Vector2f(50, 50));
    test2.setPosition(sf::Vector2f(900, 600));

    float playerX = SCREEN_WIDTH / 2 ;
    float playerY = SCREEN_HEIGHT / 2;
    player.setOrigin(player.getSize()/2.0f);
    player.setPosition(playerX, playerY);
    player.setFillColor(sf::Color::Red);

    test.setFillColor(sf::Color::Green);
    test2.setFillColor(sf::Color::Green);
    // Load your map, player, and other game objects here

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle player movement (example: arrow keys)
        float playerSpeed = 2.0f;
       

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            playerX -= playerSpeed;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            playerX += playerSpeed;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            playerY -= playerSpeed;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            playerY += playerSpeed;
        std::cout << "x:" << playerX << "y:" << playerY << std::endl;
        // Update the camera
      
        player.setPosition(playerX, playerY);
        
        camera.update(playerX + player.getSize().x / 2, playerY + player.getSize().y / 2);  // Center camera around the player's center

        // Set the active view to the camera's view
        window.setView(camera.getView());

        // Clear the window
        window.clear();

        // Render the visible area of the map and game objects
        // ...
        window.draw(test);
        window.draw(test2);
        window.draw(player);

        // Display everything
        window.display();
    }

    return 0;
}