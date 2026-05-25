#pragma once
#include <SFML/Graphics.hpp>

class Brick {
private:
    sf::RectangleShape shape;
    bool destroyed; // tugla kirildi mi kirilmadi mi onu tutuyor

public:
    Brick(float x, float y); // tuglayi olustururken kordinatlarini vercez
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isDestroyed() const;
    void destroy(); // tuglaya top carpinca bu caliscak
};