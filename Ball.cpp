#include "Ball.h"

// Top oluşturuluyor
Ball::Ball() {

    // Topun yarıçapı
    shape.setRadius(10.f);

    // Top rengi
    shape.setFillColor(sf::Color::White);

    // Başlangıç konumu
    shape.setPosition(390.f, 300.f);

    // Başlangıç hızları
    speedX = 5.0f;
    speedY = -5.0f;
}

// Top hareketi ve duvar çarpışmaları
void Ball::update(float screenWidth, float screenHeight) {

    // Topu hareket ettir
    shape.move(speedX, speedY);

    // Sağ veya sol duvara çarparsa yön değiştir
    if (shape.getPosition().x <= 0 ||
        shape.getPosition().x + (shape.getRadius() * 2) >= screenWidth) {

        speedX = -speedX;
    }

    // Sadece üst duvardan sekme
    if (shape.getPosition().y <= 0) {

        speedY = -speedY;
    }
}

// Topu ekrana çiz
void Ball::draw(sf::RenderWindow& window) {

    window.draw(shape);
}

// Çarpışma kontrolü için sınır döndür
sf::FloatRect Ball::getBounds() const {

    return shape.getGlobalBounds();
}

// Rakete çarpınca sekme işlemi
void Ball::bounceOffPaddle(float paddleY) {

    // Top her zaman yukarı doğru gitsin
    speedY = -std::abs(speedY);

    // Topu raketin üstüne yerleştir
    shape.setPosition(
        shape.getPosition().x,
        paddleY - (shape.getRadius() * 2)
    );
}

// Topu başlangıç konumuna sıfırla
void Ball::reset() {

    shape.setPosition(390.f, 300.f);

    speedX = 5.0f;
    speedY = -5.0f;
}

// ================= EKSTRA FONKSİYONLAR ================= //

// Y eksenindeki yönü tersine çevir
void Ball::reverseY() {

    // Tuğla çarpışmalarında kullanılıyor
    speedY = -speedY;
}

// X eksenindeki yönü tersine çevir
void Ball::reverseX() {

    // Yan çarpmalar için kullanılabilir
    speedX = -speedX;
}