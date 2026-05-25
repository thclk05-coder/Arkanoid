#include "Game.h"
#include <iostream>

// Ana oyun penceresi oluşturuluyor
Game::Game() : window(sf::VideoMode(800, 600), "Kocaeli Uni Arkanoid - Taha Celik") {

    window.setFramerateLimit(60);
    lives = 3;
    score = 0;
    currentLevel = 1; // Başlangıç seviyesi

    if (!font.loadFromFile("C:\\Users\\thclk\\Desktop\\Arkanoid\\font.ttf")) {
        std::cout << "FONT YUKLENEMEDI" << std::endl;
    }

    // Skor metni ayarları (Sol üst)
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineThickness(2.f);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setPosition(20.f, 20.f);
    scoreText.setString("Skor: 0");

    // Level metni ayarları (Sağ üst)
    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::Yellow);
    levelText.setOutlineThickness(2.f);
    levelText.setOutlineColor(sf::Color::Black);
    levelText.setPosition(650.f, 20.f);
    levelText.setString("Level: 1");

    float startX = 50.f;
    float startY = 80.f;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            int type = (i == 0) ? 2 : 1;
            bricks.push_back(Brick(startX + j * 70.f, startY + i * 30.f, type));
        }
    }
}

// Ana oyun döngüsü
void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

// Klavye ve pencere olayları
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if (lives > 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            paddle.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paddle.moveRight();
        }
    }
}

// Oyun içi güncellemeler
void Game::update() {
    if (lives <= 0) return;

    bool allDestroyed = true;
    for (auto& brick : bricks) {
        if (!brick.isDestroyed() && brick.getHp() != -1) {
            allDestroyed = false;
            break;
        }
    }

    if (allDestroyed) return;

    paddle.update(800.f);
    ball.update(800.f, 600.f);

    if (ball.getBounds().intersects(paddle.getBounds())) {
        ball.bounceOffPaddle(paddle.getBounds().top);
    }

    for (size_t i = 0; i < bricks.size(); ++i) {
        if (!bricks[i].isDestroyed() && ball.getBounds().intersects(bricks[i].getBounds())) {
            bricks[i].hit();
            ball.reverseY();

            if (bricks[i].isDestroyed()) {
                score += 10;
                scoreText.setString("Skor: " + std::to_string(score));
            }
            break;
        }
    }

    if (ball.getBounds().top > 600.f) {
        lives--;
        if (lives > 0) {
            paddle.reset();
            ball.reset();
        }
    }
}

// Çizim işlemleri
void Game::render() {
    window.clear(sf::Color(30, 30, 30));

    for (auto& brick : bricks) {
        brick.draw(window);
    }

    for (int i = 0; i < lives; i++) {
        sf::RectangleShape lifeIcon(sf::Vector2f(15.f, 15.f));
        lifeIcon.setFillColor(sf::Color::Red);
        lifeIcon.setPosition(20.f + (i * 25.f), 550.f); // Canları alta aldım
        window.draw(lifeIcon);
    }

    // Skor ve Level göstergeleri
    window.draw(scoreText);
    window.draw(levelText);

    paddle.draw(window);
    ball.draw(window);

    if (lives <= 0) {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(60);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(220.f, 250.f);
        window.draw(gameOverText);
    }
    else {
        bool allDestroyed = true;
        for (auto& brick : bricks) {
            if (!brick.isDestroyed() && brick.getHp() != -1) {
                allDestroyed = false;
                break;
            }
        }
        if (allDestroyed) {
            sf::Text winText;
            winText.setFont(font);
            winText.setString("TEBRIKLER KAZANDIN!");
            winText.setCharacterSize(50);
            winText.setFillColor(sf::Color::Green);
            winText.setPosition(150.f, 250.f);
            window.draw(winText);
        }
    }
    window.display();
}