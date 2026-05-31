#include "Item.h"

Item::Item(float x, float y, int itemType) {
    type = itemType;
    speedY = 3.5f; // İtemin aşağı düşme hızı

    // Küçük bir kare şeklinde düşsün
    shape.setSize(sf::Vector2f(20.f, 20.f));
    shape.setPosition(x, y);

    // Türüne göre renk verelim ki oyuncu ne tuttuğunu bilsin
    if (type == 1) {
        shape.setFillColor(sf::Color::Green); // İyi özellik
    }
    else if (type == 2) {
        shape.setFillColor(sf::Color::Blue); // Can artırıcı
    }
    else if (type == 3) {
        shape.setFillColor(sf::Color::Red); // Tuzak
    }
}

void Item::update() {
    shape.move(0.f, speedY); // Sadece Y ekseninde aşağı düşer
}

void Item::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Item::getBounds() const {
    return shape.getGlobalBounds();
}

int Item::getType() const {
    return type;
}