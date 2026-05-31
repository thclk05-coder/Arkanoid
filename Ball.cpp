#include "Ball.h"
#include <cmath>

Ball::Ball() {
    shape.setRadius(9.f);

    // Resimdeki gibi içi beyaz, dışı Turkuaz parlamalı
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(sf::Color::Cyan);

    shape.setPosition(390.f, 300.f);
    speedX = 5.0f;
    speedY = -5.0f;
}

void Ball::update(float screenWidth, float screenHeight) {
    shape.move(speedX, speedY);

    if (shape.getPosition().x <= 0 || shape.getPosition().x + (shape.getRadius() * 2) >= screenWidth) {
        speedX = -speedX;
    }
    if (shape.getPosition().y <= 0) {
        speedY = -speedY;
    }
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

void Ball::bounceOffPaddle(float paddleY) {
    speedY = -std::abs(speedY);
    shape.setPosition(shape.getPosition().x, paddleY - (shape.getRadius() * 2));
}

void Ball::reset() {
    shape.setPosition(390.f, 300.f);
    speedX = 5.0f;
    speedY = -5.0f;
}

void Ball::reverseY() { speedY = -speedY; }
void Ball::reverseX() { speedX = -speedX; }