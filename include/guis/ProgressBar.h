#pragma once
#include "../Resources.h"

class ProgressBar {
public:
    ProgressBar(float x, float y, float width, float height,
        sf::Color backgroundColor, sf::Color barColor)
        : position(x, y), size(width, height)
    {
        background.setFillColor(backgroundColor);
        background.setPosition(position);
        background.setSize(size);

        bar.setFillColor(barColor);
        bar.setPosition(position);
        bar.setSize(sf::Vector2f(0, height));
    }
  

    void setProgress(float progress) {
        float fraction = progress / 100.0f;

        // Modify the bar size based on the fraction
        bar.setSize(sf::Vector2f(size.x * fraction, size.y));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(bar);
    }

private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape background;
    sf::RectangleShape bar;

    //need to add the functionality to add text, and print it on top of the progress bars

};
