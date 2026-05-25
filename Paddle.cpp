#include "Paddle.h"

Paddle::Paddle() {
    shape.setSize(sf::Vector2f(120.f, 20.f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(340.f, 550.f);
    speed = 9.0f;
}

void Paddle::moveLeft() {
    shape.move(-speed, 0.f);
}

void Paddle::moveRight() {
    shape.move(speed, 0.f);
}

void Paddle::update(float screenWidth) {
    if (shape.getPosition().x < 0) {
        shape.setPosition(0.f, shape.getPosition().y);
    }
    if (shape.getPosition().x + shape.getSize().x > screenWidth) {
        shape.setPosition(screenWidth - shape.getSize().x, shape.getPosition().y);
    }
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

void Paddle::reset() {
    shape.setPosition(340.f, 550.f); // raket basa dondu
}