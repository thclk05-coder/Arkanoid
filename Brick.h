#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, int type);
    Brick(const Brick& other); // Vektör hatalarını önleyen Kopya Oluşturucu
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isDestroyed() const;
    int getHp() const;
    void hit();

private:
    sf::Sprite sprite;
    sf::Texture texture;
    int hp;
    bool destroyed;
    void updateTexture(); // Can azaldıkça yeni rengi (resmi) yükler
};