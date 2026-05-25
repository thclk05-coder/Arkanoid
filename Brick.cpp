#include "Brick.h"

// Tuğla oluşturulurken pozisyonunu ve can tipini belirliyoruz
Brick::Brick(float x, float y, int type) {
    shape.setSize(sf::Vector2f(60.f, 20.f));
    shape.setPosition(x, y);
    hp = type;
    destroyed = false;

    // Can tipine göre ilk renkleri atıyoruz
    if (hp == 1) {
        shape.setFillColor(sf::Color::Red);       // 1 Can: Kırmızı
    }
    else if (hp == 2) {
        shape.setFillColor(sf::Color::Magenta);   // 2 Can: Mor
    }
    else if (hp == 3) {
        shape.setFillColor(sf::Color::Green);     // 3 Can: Yeşil
    }
    else if (hp == 4) {
        shape.setFillColor(sf::Color::Blue);      // 4 Can: Mavi
    }
    else if (hp == -1) {
        shape.setFillColor(sf::Color(128, 128, 128)); // Kırılamaz: Gri
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

    // Kırılmadıysa yeni canına göre rengini güncelle (Görsel tatmin)
    if (hp <= 0) {
        destroyed = true;
    }
    else if (hp == 1) {
        shape.setFillColor(sf::Color::Red);
    }
    else if (hp == 2) {
        shape.setFillColor(sf::Color::Magenta);
    }
    else if (hp == 3) {
        shape.setFillColor(sf::Color::Green);
    }
}