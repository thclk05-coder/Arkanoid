#include "Item.h"
#include <iostream>
#include <string>

Item::Item(float x, float y, int itemType) {
    type = itemType;
    speedY = 3.5f; // Düşme hızı

    updateTexture(); // Tipe göre resmi yükle

    sprite.setPosition(x, y);

    // İtemleri ekranda sırıtmayacak şekilde 35x35 piksel boyutlarına oranlıyoruz
    if (texture.getSize().x > 0 && texture.getSize().y > 0) {
        sprite.setScale(35.f / texture.getSize().x, 35.f / texture.getSize().y);
    }
}

// C++ Vektör Koruyucusu (Oyunun çökmesini veya beyaz kutu çıkmasını engeller)
Item::Item(const Item& other) {
    type = other.type;
    speedY = other.speedY;
    texture = other.texture;
    sprite = other.sprite;
    sprite.setTexture(texture); // Resmi sprite'a yeniden bağlıyoruz
}

void Item::updateTexture() {
    std::string path = "C:\\Users\\thclk\\Desktop\\Arkanoid\\";

    // Tipe göre ilgili PNG dosyasını seçiyoruz
    if (type == 1) path += "yildiz.png";       // Puan itemi
    else if (type == 2) path += "kalp.png";    // Can itemi
    else if (type == 3) path += "bomba.png";   // Tuzak itemi
    else path += "yildiz.png";

    if (!texture.loadFromFile(path)) {
        std::cout << "ITEM RESMI YUKLENEMEDI: " << path << std::endl;
    }
    sprite.setTexture(texture);
}

void Item::update() {
    sprite.move(0.f, speedY);
}

void Item::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Item::getBounds() const {
    return sprite.getGlobalBounds();
}

int Item::getType() const {
    return type;
}