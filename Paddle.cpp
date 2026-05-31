#include "Paddle.h"
#include <iostream>

Paddle::Paddle() {
    if (!texture.loadFromFile("C:\\Users\\thclk\\Desktop\\Arkanoid\\cubuk.png")) {
        std::cout << "CUBUK RESMI YUKLENEMEDI!" << std::endl;
    }
    sprite.setTexture(texture);

    // Eski boyut 100x18'di. Fizik motoru için o boyuta ayarlıyoruz.
    sprite.setScale(100.f / texture.getSize().x, 18.f / texture.getSize().y);
    sprite.setPosition(350.f, 550.f);
    speed = 9.0f;
}

void Paddle::moveLeft() { sprite.move(-speed, 0.f); }
void Paddle::moveRight() { sprite.move(speed, 0.f); }

void Paddle::update(float screenWidth) {
    if (sprite.getPosition().x < 0) {
        sprite.setPosition(0.f, sprite.getPosition().y);
    }
    if (sprite.getPosition().x + sprite.getGlobalBounds().width > screenWidth) {
        sprite.setPosition(screenWidth - sprite.getGlobalBounds().width, sprite.getPosition().y);
    }
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Paddle::getBounds() const {
    return sprite.getGlobalBounds();
}

void Paddle::reset() {
    sprite.setPosition(350.f, 550.f);
}