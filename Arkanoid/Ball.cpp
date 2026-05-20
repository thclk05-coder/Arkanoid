#include "Ball.h"

Ball::Ball() {
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(390.f, 300.f);
    speedX = 5.0f;
    speedY = -5.0f;
}

void Ball::update(float screenWidth, float screenHeight) {
    shape.move(speedX, speedY);

    // sag veya sol duvara carparsa x hizini tersine cevir
    if (shape.getPosition().x <= 0 || shape.getPosition().x + (shape.getRadius() * 2) >= screenWidth) {
        speedX = -speedX;
    }

    // SADECE UST DUVARA CARPARSA SEKSIN
    // alt duvardan sekme kodunu sildim ki top asagi dusup can eksiltebilsin
    if (shape.getPosition().y <= 0) {
        speedY = -speedY;
    }
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

void Ball::bounceOffPaddle(float paddleY) {
    speedY = -speedY;
    shape.setPosition(shape.getPosition().x, paddleY - (shape.getRadius() * 2));
}

void Ball::reset() {
    shape.setPosition(390.f, 300.f); // top merkeze dondu
    speedX = 5.0f;
    speedY = -5.0f; // hiz sifirlandi
}