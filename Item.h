#pragma once
#include <SFML/Graphics.hpp>

class Item {
public:
    Item(float x, float y, int itemType);
    Item(const Item& other); // Kopyalama hatasını önleyen sistem
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    int getType() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speedY;
    int type; // 1: Yıldız (Puan), 2: Kalp (Can), 3: Bomba (Tuzak)
    void updateTexture();
};