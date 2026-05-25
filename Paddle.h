#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape shape;
    float speed;

public:
    Paddle();
    void moveLeft();
    void moveRight();
    void update(float screenWidth);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void reset();
};