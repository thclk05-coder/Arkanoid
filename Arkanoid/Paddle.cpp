#include "Paddle.h"

Paddle::Paddle() {
    // raketin boyutu ve rengini ayarladim
    shape.setSize(sf::Vector2f(120.f, 20.f));
    shape.setFillColor(sf::Color::Green);
    // baslangic konumu ekranin alt ortasi olsun
    shape.setPosition(340.f, 550.f);
    speed = 9.0f; // hizini 9 yaptim fena durmuyor
}

void Paddle::moveLeft() {
    shape.move(-speed, 0.f); // eksi yonde gitcek
}

void Paddle::moveRight() {
    shape.move(speed, 0.f); // arti yonde gitcek
}

void Paddle::update(float screenWidth) {
    // raket soldan disari cikarsa sifira sabitle
    if (shape.getPosition().x < 0) {
        shape.setPosition(0.f, shape.getPosition().y);
    }
    // sagdan cikmaya calisirsa ekran genisliginden raketin boyutunu cikarip oraya sabitle
    if (shape.getPosition().x + shape.getSize().x > screenWidth) {
        shape.setPosition(screenWidth - shape.getSize().x, shape.getPosition().y);
    }
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape); // ekrana basiyoruz
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds(); // carpismalar icin sinirlari donduruyor
}