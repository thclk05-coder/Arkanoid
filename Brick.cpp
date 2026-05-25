#include "Brick.h"

Brick::Brick(float x, float y) {
    shape.setSize(sf::Vector2f(65.f, 25.f)); // senin boyutlar
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);
    shape.setPosition(x, y);
    destroyed = false; // basta hepsi sapasaglam
}

void Brick::draw(sf::RenderWindow& window) {
    if (!destroyed) {
        window.draw(shape); // sadece kirilmadiysa ekrana ciz
    }
}

sf::FloatRect Brick::getBounds() const {
    return shape.getGlobalBounds();
}

bool Brick::isDestroyed() const {
    return destroyed;
}

void Brick::destroy() {
    destroyed = true; // top carpinca kirildi isaretliyoruz
}