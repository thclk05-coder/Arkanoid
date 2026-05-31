#include "Brick.h"
#include <iostream>
#include <string>

Brick::Brick(float x, float y, int type) {
    hp = type;
    destroyed = false;

    updateTexture(); // Başlangıç canına göre ilk resmi yükle

    sprite.setPosition(x, y);
    // Eski tuğla boyutlarına (70x25) oranlıyoruz
    sprite.setScale(70.f / texture.getSize().x, 25.f / texture.getSize().y);
}

// C++ Vektör Koruyucusu (Beyaz kutu hatasını önler)
Brick::Brick(const Brick& other) {
    hp = other.hp;
    destroyed = other.destroyed;
    texture = other.texture;
    sprite = other.sprite;
    sprite.setTexture(texture);
}

void Brick::updateTexture() {
    std::string path = "C:\\Users\\thclk\\Desktop\\Arkanoid\\";

    if (hp == 1) path += "tugla1.png";
    else if (hp == 2) path += "tugla2.png";
    else if (hp == 3) path += "tugla3.png";
    else if (hp == 4) path += "tugla3.png"; // tugla4.png eklersen burayı değiştir
    else path += "tugla1.png"; // Kırılamaz veya hata durumu

    if (!texture.loadFromFile(path)) {
        std::cout << "TUGLA RESMI YUKLENEMEDI: " << path << std::endl;
    }
    sprite.setTexture(texture);
}

void Brick::hit() {
    if (hp == -1) return;
    hp--;
    if (hp <= 0) {
        destroyed = true;
    }
    else {
        updateTexture(); // Canı azalınca anında resmini değiştir!
    }
}

void Brick::draw(sf::RenderWindow& window) {
    if (!destroyed) window.draw(sprite);
}

sf::FloatRect Brick::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Brick::isDestroyed() const { return destroyed; }
int Brick::getHp() const { return hp; }