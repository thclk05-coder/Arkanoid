#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape;
    float speedX;
    float speedY;

public:
    Ball();
    void update(float screenWidth, float screenHeight);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void bounceOffPaddle(float paddleY);
    void reset();
};