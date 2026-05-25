#include "Brick.h"

// Tuğla oluşturulurken pozisyonunu ve can tipini belirliyoruz
Brick::Brick(float x, float y, int type) {
    shape.setSize(sf::Vector2f(60.f, 20.f)); // Sabit tuğla boyutu
    shape.setPosition(x, y);
    hp = type;
    destroyed = false;

    // Can tipine göre ilk renkleri atıyoruz
    if (hp == 1) {
        shape.setFillColor(sf::Color::Red); // Normal tuğla kırmızı
    }
    else if (hp == 2) {
        shape.setFillColor(sf::Color::Magenta); // Sert tuğla mor
    }
    else if (hp == -1) {
        shape.setFillColor(sf::Color(128, 128, 128)); // Kırılamaz duvar gri
    }
}

void Brick::draw(sf::RenderWindow& window) {
    if (!destroyed) {
        window.draw(shape);
    }
}

sf::FloatRect Brick::getBounds() const {
    return shape.getGlobalBounds();
}

bool Brick::isDestroyed() const {
    return destroyed;
}

int Brick::getHp() const {
    return hp;
}

// Top çarptığında çalışacak yer
void Brick::hit() {
    if (hp == -1) return; // Kırılamaz duvarda hiçbir şey yapma

    hp--; // Canı 1 azalt

    if (hp <= 0) {
        destroyed = true; // Can bittiyse tuğlayı yok et
    }
    else if (hp == 1) {
        shape.setFillColor(sf::Color::Red); // 2 canlı tuğla darbe alınca kırmızıya dönsün
    }
}