#include "Brick.h"
#include <iostream>
#include <string>

Brick::Brick(float x, float y, int type) {
    hp = type;
    destroyed = false;

    updateTexture(); // Başlangıç canına göre resmi yükle

    sprite.setPosition(x, y);

    if (texture.getSize().x > 0 && texture.getSize().y > 0) {
        sprite.setScale(70.f / texture.getSize().x, 25.f / texture.getSize().y);
    }
}

Brick::Brick(const Brick& other) {
    hp = other.hp;
    destroyed = other.destroyed;
    texture = other.texture;
    sprite = other.sprite;
    sprite.setTexture(texture);
}

void Brick::updateTexture() {
    std::string path = "assets/";

    // TÜM RESİMLER VE 4. CAN DESTEĞİ AKTİF
    if (hp == 1) path += "tugla1.png";
    else if (hp == 2) path += "tugla2.png";
    else if (hp == 3) path += "tugla3.png";
    else if (hp == 4) path += "tugla4.png"; // <-- Yeni eklediğin resim burada devreye giriyor!
    else if (hp == -1) path += "duvar.png"; // Kırılamaz blok
    else path += "tugla1.png";

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
        updateTexture(); // Canı her azaldığında bir alt canın rengine (resmine) bürünür
    }
}

void Brick::draw(sf::RenderWindow& window) {
    if (!destroyed) {
        sprite.setTexture(texture); // Beyaz kare hatası olmaması için adres tazelemesi
        window.draw(sprite);
    }
}

sf::FloatRect Brick::getBounds() const { return sprite.getGlobalBounds(); }
bool Brick::isDestroyed() const { return destroyed; }
int Brick::getHp() const { return hp; }