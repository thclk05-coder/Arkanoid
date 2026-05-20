#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Kocaeli Uni Arkanoid - Parcali Sistem") {
    window.setFramerateLimit(60);
    lives = 3; // baslangic cani 3

    float startX = 50.f;
    float startY = 80.f;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            bricks.push_back(Brick(startX + j * 70.f, startY + i * 30.f));
        }
    }
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        paddle.moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        paddle.moveRight();
    }
}

void Game::update() {
    paddle.update(800.f);
    ball.update(800.f, 600.f);

    if (ball.getBounds().intersects(paddle.getBounds())) {
        ball.bounceOffPaddle(paddle.getBounds().top);
    }

    for (size_t i = 0; i < bricks.size(); ++i) {
        if (!bricks[i].isDestroyed() && ball.getBounds().intersects(bricks[i].getBounds())) {
            bricks[i].destroy();
            ball.bounceOffPaddle(bricks[i].getBounds().top + 40.f);
            break;
        }
    }

    // Top asagi dustu mu kontrolu
    if (ball.getBounds().top > 600.f) {
        lives--; // cani 1 azalt
        if (lives > 0) {
            paddle.reset();
            ball.reset();
        }
        else {
            window.close(); // can bittiyse simdilik kapansin
        }
    }
}

void Game::render() {
    window.clear(sf::Color(30, 30, 30));

    for (auto& brick : bricks) {
        brick.draw(window);
    }

    paddle.draw(window);
    ball.draw(window);

    // CAN GOSTERGESI 
    for (int i = 0; i < lives; i++) {
        sf::RectangleShape lifeIcon(sf::Vector2f(15.f, 15.f));
        lifeIcon.setFillColor(sf::Color::Red);
        lifeIcon.setPosition(20.f + (i * 25.f), 20.f);
        window.draw(lifeIcon);
    }

    window.display();
}