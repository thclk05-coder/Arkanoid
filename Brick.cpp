#include "Brick.h"
#include <iostream>
#include <string>

Brick::Brick(float x, float y, int type) {
    hp = type;
    destroyed = false;

    updateTexture();

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
    std::string path = "C:\\Users\\thclk\\Desktop\\Arkanoid\\";

    // YENİ EKLENEN KISIM: -1 için duvar.png yüklenecek!
    if (hp == 1) path += "tugla1.png";
    else if (hp == 2) path += "tugla2.png";
    else if (hp == 3) path += "tugla3.png";
    else if (hp == -1) path += "duvar.png"; // Kırılamaz blok resmi
    else path += "tugla1.png"; // Ne olur ne olmaz güvenlik duvarı

    if (!texture.loadFromFile(path)) {
        std::cout << "TUGLA RESMI YUKLENEMEDI: " << path << std::endl;
    }
    sprite.setTexture(texture);
}

void Brick::hit() {
    if (hp == -1) return; // -1 ise canı hiç azaltma, kırılmasın
    hp--;
    if (hp <= 0) {
        destroyed = true;
    }
    else {
        updateTexture();
    }
}

void Brick::draw(sf::RenderWindow& window) {
    if (!destroyed) window.draw(sprite);
}

sf::FloatRect Brick::getBounds() const { return sprite.getGlobalBounds(); }
bool Brick::isDestroyed() const { return destroyed; }
int Brick::getHp() const { return hp; }