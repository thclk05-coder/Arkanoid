#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Kocaeli Uni Arkanoid - Taha Celik") {

    srand(static_cast<unsigned>(time(NULL)));
    window.setFramerateLimit(60);

    lives = 3;
    score = 0;
    currentLevel = 1;
    isPlusPressed = false;

    if (!font.loadFromFile("C:\\Users\\thclk\\Desktop\\Arkanoid\\font.ttf")) {
        std::cout << "FONT YUKLENEMEDI" << std::endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineThickness(2.f);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setPosition(20.f, 20.f);
    scoreText.setString("Skor: 0");

    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::Yellow);
    levelText.setOutlineThickness(2.f);
    levelText.setOutlineColor(sf::Color::Black);
    levelText.setPosition(650.f, 20.f);
    levelText.setString("Level: 1");

    loadLevel(currentLevel);
}

// BÖLÜM YÜKLEME VE YENİ DENGELİ ZORLUK ALGORİTMASI 
void Game::loadLevel(int level) {
    bricks.clear();
    items.clear(); // YENİ: Yeni levele geçerken eski itemleri ekrandan temizle

    float startX = 50.f;
    float startY = 80.f;

    int rows = 4 + (level / 5);
    if (rows > 8) rows = 8;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < 10; ++j) {

            int type = 1; // Varsayılan: Normal kırmızı tuğla

            // Zorluk motoru (En zor ihtimalden geriye doğru kontrol ediyoruz):

            // 1. Kırılamaz Duvar (Gri): Level 25'ten sonra ortaya çıkar
            if (level > 25 && (rand() % 100 < 10 + (level / 10))) {
                type = -1;
            }
            // 2. Mavi Tuğla (4 Can): Level 20'den sonra ortaya çıkar
            else if (level > 20 && (rand() % 100 < 15 + (level / 5))) {
                type = 4;
            }
            // 3. Yeşil Tuğla (3 Can): Level 10'dan sonra ortaya çıkar
            else if (level > 10 && (rand() % 100 < 20 + (level / 4))) {
                type = 3;
            }
            // 4. Mor Tuğla (2 Can): Level 3'ten sonra ortaya çıkar
            else if (level >= 3 && (rand() % 100 < 25 + (level / 3))) {
                type = 2;
            }

            bricks.push_back(Brick(startX + j * 70.f, startY + i * 30.f, type));
        }
    }

    levelText.setString("Level: " + std::to_string(level));
    paddle.reset();
    ball.reset();
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

    // LEVEL ATLAMA HİLESİ
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) || sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
        if (!isPlusPressed) {
            currentLevel++;
            if (currentLevel <= 100) {
                loadLevel(currentLevel);
            }
            isPlusPressed = true;
        }
    }
    else {
        isPlusPressed = false;
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

void Game::update() {
    if (lives <= 0) return;

    bool allDestroyed = true;
    for (auto& brick : bricks) {
        if (!brick.isDestroyed() && brick.getHp() != -1) {
            allDestroyed = false;
            break;
        }
    }

    if (allDestroyed) {
        currentLevel++;
        if (currentLevel > 100) {
            return;
        }
        loadLevel(currentLevel);
        return;
    }

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

                // YENİ: İtem düşürme mantığı (%25 ihtimal)
                if (rand() % 100 < 25) {
                    int randomType = (rand() % 3) + 1; // 1, 2 veya 3
                    sf::FloatRect brickBounds = bricks[i].getBounds();
                    // Tuğlanın ortasından düşsün
                    float dropX = brickBounds.left + (brickBounds.width / 2.f) - 10.f;
                    float dropY = brickBounds.top;

                    items.push_back(Item(dropX, dropY, randomType));
                }
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

    // YENİ: İtem hareketleri ve raketle çarpışma kontrolü
    for (int i = 0; i < items.size(); i++) {
        items[i].update(); // İtemi aşağı kaydır

        // İtem ekrandan aşağı düştüyse listeden sil
        if (items[i].getBounds().top > 600.f) {
            items.erase(items.begin() + i);
            i--;
            continue;
        }

        // İtem çubuğa çarptıysa
        if (items[i].getBounds().intersects(paddle.getBounds())) {
            int type = items[i].getType();

            if (type == 1) {
                // Tip 1 (Yeşil): Ekstra puan
                score += 50;
                scoreText.setString("Skor: " + std::to_string(score));
            }
            else if (type == 2) {
                // Tip 2 (Mavi): Ekstra can
                lives++;
            }
            else if (type == 3) {
                // Tip 3 (Kırmızı): Can azaltır
                lives--;
                if (lives <= 0) {
                    paddle.reset();
                    ball.reset();
                }
            }

            // İtemi yakaladık, etkisini uyguladık, ekrandan siliyoruz
            items.erase(items.begin() + i);
            i--;
        }
    }
}

void Game::render() {
    window.clear(sf::Color(30, 30, 30));

    for (auto& brick : bricks) {
        brick.draw(window);
    }

    // YENİ: İtemleri çizdir
    for (auto& item : items) {
        item.draw(window);
    }

    for (int i = 0; i < lives; i++) {
        sf::RectangleShape lifeIcon(sf::Vector2f(15.f, 15.f));
        lifeIcon.setFillColor(sf::Color::Red);
        lifeIcon.setPosition(20.f + (i * 25.f), 550.f);
        window.draw(lifeIcon);
    }

    window.draw(scoreText);
    window.draw(levelText);

    paddle.draw(window);
    ball.draw(window);

    if (lives <= 0) {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("OYUN BITTI!");
        gameOverText.setCharacterSize(60);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(220.f, 250.f);
        window.draw(gameOverText);
    }
    else if (currentLevel > 100) {
        sf::Text winText;
        winText.setFont(font);
        winText.setString("TEBRIKLER 100 LEVEL GECILDI!");
        winText.setCharacterSize(45);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(80.f, 250.f);
        window.draw(winText);
    }

    window.display();
}