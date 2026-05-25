#pragma once
#include <SFML/Graphics.hpp>

class Brick {
private:
    sf::RectangleShape shape;
    int hp;            // Tuğlanın canı (1: Normal, 2: Sert, -1: Kırılamaz Duvar)
    bool destroyed;    // Kırıldı mı kontrolü

public:
    // Kurucu fonksiyona artık 'type' parametresi ekledik
    Brick(float x, float y, int type);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isDestroyed() const;

    // Top tuğlaya vurunca canını azaltacak fonksiyon
    void hit();

    // Tuğlanın can tipini veren fonksiyon (Level geçişlerinde lazım olacak)
    int getHp() const;
};