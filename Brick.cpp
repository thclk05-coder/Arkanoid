#include "Brick.h"

Brick::Brick(float x, float y, int type) {
    // Tuğlaları resimdeki gibi daha kalın yaptık
    shape.setSize(sf::Vector2f(70.f, 25.f));
    shape.setPosition(x, y);
    hp = type;
    destroyed = false;

    // Tamamen boşaltmak yerine içine çok hafif karanlık bir cam efekti veriyoruz
    shape.setFillColor(sf::Color(20, 20, 30, 180));
    shape.setOutlineThickness(2.f);

    // Resimdeki renk paleti (Mor, Turkuaz, Pembe)
    if (hp == 1) {
        shape.setOutlineColor(sf::Color(138, 43, 226)); // Mor
    }
    else if (hp == 2) {
        shape.setOutlineColor(sf::Color(0, 255, 255));   // Turkuaz
    }
    else if (hp == 3) {
        shape.setOutlineColor(sf::Color(255, 20, 147));  // Derin Pembe
    }
    else if (hp == 4) {
        shape.setOutlineColor(sf::Color(148, 0, 211));   // Koyu Mor
    }
    else if (hp == -1) {
        shape.setOutlineColor(sf::Color(100, 100, 100)); // Kırılamaz Gri
    }
}

void Brick::draw(sf::RenderWindow& window) {
    if (!destroyed) window.draw(shape);
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

void Brick::hit() {
    if (hp == -1) return;
    hp--;
    if (hp <= 0) {
        destroyed = true;
    }
    else if (hp == 1) {
        shape.setOutlineColor(sf::Color(138, 43, 226));
    }
    else if (hp == 2) {
        shape.setOutlineColor(sf::Color(0, 255, 255));
    }
    else if (hp == 3) {
        shape.setOutlineColor(sf::Color(255, 20, 147));
    }
}