#pragma once
#include <SFML/Graphics.hpp>

class Item {
private:
    sf::RectangleShape shape;
    float speedY;
    int type; // 1: İyi (Yeşil), 2: Ekstra Can (Mavi), 3: Kötü/Tuzak (Kırmızı)

public:
    Item(float x, float y, int itemType);
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    int getType() const;
}
