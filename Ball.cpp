#include "Ball.h"
#include <cmath>
#include <iostream>

Ball::Ball() {
    // Resmi Yüklüyoruz
    if (!texture.loadFromFile("C:\\Users\\thclk\\Desktop\\Arkanoid\\top.png")) {
        std::cout << "TOP RESMI YUKLENEMEDI!" << std::endl;
    }
    sprite.setTexture(texture);

    // Eski yarıçap 9'du (Çap 18x18 yapar). Resmi bu boyuta sıkıştırıyoruz ki fizik bozulmasın.
    sprite.setScale(18.f / texture.getSize().x, 18.f / texture.getSize().y);
    sprite.setPosition(390.f, 300.f);

    speedX = 5.0f;
    speedY = -5.0f;
}

void Ball::update(float screenWidth, float screenHeight) {
    sprite.move(speedX, speedY);

    if (sprite.getPosition().x <= 0 || sprite.getPosition().x + sprite.getGlobalBounds().width >= screenWidth) {
        speedX = -speedX;
    }
    if (sprite.getPosition().y <= 0) {
        speedY = -speedY;
    }
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Ball::getBounds() const {
    return sprite.getGlobalBounds();
}

void Ball::bounceOffPaddle(float paddleY) {
    speedY = -std::abs(speedY);
    sprite.setPosition(sprite.getPosition().x, paddleY - sprite.getGlobalBounds().height);
}

void Ball::reset() {
    sprite.setPosition(390.f, 300.f);
    speedX = 5.0f;
    speedY = -5.0f;
}

void Ball::reverseY() { speedY = -speedY; }
void Ball::reverseX() { speedX = -speedX; }