#pragma once
#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball();
    void update(float screenWidth, float screenHeight);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void bounceOffPaddle(float paddleY);
    void reset();
    void reverseY();
    void reverseX();

private:
    sf::Sprite sprite;   // Artık şekil değil, resim (sprite) kullanıyoruz
    sf::Texture texture; // Resmin dosyadaki hali
    float speedX;
    float speedY;
};