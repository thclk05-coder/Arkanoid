#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape shape; // raketin sekli
    float speed; // raketin hizi

public:
    Paddle();
    void moveLeft();
    void moveRight();
    void update(float screenWidth); // sinir kontrolu icin ekran genisligini parametre alcaz
    void draw(sf::RenderWindow& window); // cizim isleri

    sf::FloatRect getBounds() const; // ileride topun carpmasini algilamak icin hitbox lazim
};