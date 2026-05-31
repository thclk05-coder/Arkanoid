#include "Game.h"
#include <iostream>
#include <fstream>  // Dosya okuma kütüphanesi
#include <sstream>  // Metin parçalama kütüphanesi
#include <string>

Game::Game() : window(sf::VideoMode(1920, 1080), "Kocaeli Uni Arkanoid - Taha Celik", sf::Style::Default) {

    srand(static_cast<unsigned>(time(NULL)));
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

    lives = 3;
    score = 0;
    currentLevel = 1;
    isPlusPressed = false;

    // ARKA PLAN
    if (!bgTexture.loadFromFile("C:\\Users\\thclk\\Desktop\\Arkanoid\\arkaplan.jpg")) {
        std::cout << "ARKA PLAN BULUNAMADI!" << std::endl;
    }
    else {
        bgSprite.setTexture(bgTexture);
        bgSprite.setScale(800.f / bgTexture.getSize().x, 600.f / bgTexture.getSize().y);
    }

    if (!font.loadFromFile("C:\\Users\\thclk\\Desktop\\Arkanoid\\font.ttf")) {
        std::cout << "FONT YUKLENEMEDI" << std::endl;
    }

    // PUAN YAZISI
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(135, 206, 250));
    scoreText.setPosition(100.f, 15.f);
    scoreText.setString("Puan: 0");

    // LEVEL YAZISI
    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color(138, 43, 226));
    levelText.setPosition(600.f, 15.f);
    levelText.setString("Level: 1");

    loadLevel(currentLevel);
}

// HİBRİT LEVEL YÜKLEME (Dosya + Otomatik Üretim)
void Game::loadLevel(int level) {
    bricks.clear();
    items.clear();

    float startX = 25.f;
    float startY = 80.f;

    // Önce dosya var mı diye bakıyoruz
    std::string filename = "C:\\Users\\thclk\\Desktop\\Arkanoid\\level" + std::to_string(level) + ".txt";
    std::ifstream file(filename);

    if (file.is_open()) {
        // 1. DURUM: DOSYA BULUNDU (Hocanın istediği dosya okuma işlemi)
        std::string line;
        int row = 0;

        while (std::getline(file, line) && row < 8) {
            std::stringstream ss(line);
            int type;
            int col = 0;

            while (ss >> type && col < 10) {
                if (type != 0) {
                    bricks.push_back(Brick(startX + col * 75.f, startY + row * 30.f, type));
                }
                col++;
            }
            row++;
        }
        file.close();
    }
    else {
        // 2. DURUM: DOSYA YOKSA (Algoritmik olarak otomatik üret!)
        int rows = 4 + (level / 5);
        if (rows > 8) rows = 8;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < 10; ++j) {
                int type = 1;

                if (level > 25 && (rand() % 100 < 10 + (level / 10))) { type = -1; }
                else if (level > 20 && (rand() % 100 < 15 + (level / 5))) { type = 4; }
                else if (level > 10 && (rand() % 100 < 20 + (level / 4))) { type = 3; }
                else if (level >= 3 && (rand() % 100 < 25 + (level / 3))) { type = 2; }

                bricks.push_back(Brick(startX + j * 75.f, startY + i * 30.f, type));
            }
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
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) || sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
        if (!isPlusPressed) {
            currentLevel++;
            if (currentLevel <= 100) loadLevel(currentLevel);
            isPlusPressed = true;
        }
    }
    else {
        isPlusPressed = false;
    }

    if (lives > 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) paddle.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) paddle.moveRight();
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
        if (currentLevel > 100) return;
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
                scoreText.setString("Puan: " + std::to_string(score));

                if (rand() % 100 < 25) {
                    int randomType = (rand() % 3) + 1;
                    sf::FloatRect brickBounds = bricks[i].getBounds();
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

    for (int i = 0; i < items.size(); i++) {
        items[i].update();

        if (items[i].getBounds().intersects(paddle.getBounds())) {
            int type = items[i].getType();
            if (type == 1) { score += 50; scoreText.setString("Puan: " + std::to_string(score)); }
            else if (type == 2) { lives++; }
            else if (type == 3) { lives--; if (lives <= 0) { paddle.reset(); ball.reset(); } }

            items.erase(items.begin() + i);
            i--;
        }
        else if (items[i].getBounds().top > 600.f) {
            items.erase(items.begin() + i);
            i--;
        }
    }
}

void Game::render() {
    window.clear();

    window.draw(bgSprite);

    sf::RectangleShape topBar(sf::Vector2f(800.f, 2.f));
    topBar.setPosition(0.f, 60.f);
    topBar.setFillColor(sf::Color(138, 43, 226, 100));
    window.draw(topBar);

    for (auto& brick : bricks) { brick.draw(window); }
    for (auto& item : items) { item.draw(window); }

    window.draw(scoreText);
    window.draw(levelText);

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color(135, 206, 250));
    livesText.setPosition(350.f, 15.f);
    livesText.setString("Canlar: " + std::to_string(lives));
    window.draw(livesText);

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
        winText.setString("TEBRIKLER!");
        winText.setCharacterSize(60);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(220.f, 250.f);
        window.draw(winText);
    }

    window.display();
}