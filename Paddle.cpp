#include "Paddle.h"

Paddle::Paddle() {
    shape.setSize(sf::Vector2f(100.f, 18.f)); // Biraz daraltıp kalınlaştırdık

    // Siyah/Saydam iç ve Turkuaz kalın çerçeve
    shape.setFillColor(sf::Color(20, 20, 30, 200));
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(sf::Color::Cyan);

    shape.setPosition(350.f, 550.f);
    speed = 9.0f;
}

void Paddle::moveLeft() { shape.move(-speed, 0.f); }
void Paddle::moveRight() { shape.move(speed, 0.f); }

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
    shape.setPosition(350.f, 550.f);
}