#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(1920, 1080), "Kocaeli Uni Arkanoid - Taha Celik", sf::Style::Default) {

    srand(static_cast<unsigned>(time(NULL)));
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

    lives = 3;
    score = 0;
    currentLevel = 1;
    isPlusPressed = false;

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

    // ARAYÜZ (UI) RESİMDEKİ GİBİ ÜST ORTAYA ALINDI
    scoreText.setFont(font);
    scoreText.setCharacterSize(26);
    scoreText.setFillColor(sf::Color(135, 206, 250)); // Açık Mavi
    scoreText.setPosition(250.f, 15.f);
    scoreText.setString("Puan: 0");

    levelText.setFont(font); // levelText'i Canlar yazısı için kullanıyoruz
    levelText.setCharacterSize(26);
    levelText.setFillColor(sf::Color(135, 206, 250)); // Açık Mavi
    levelText.setPosition(450.f, 15.f);
    levelText.setString("Canlar: 3");

    loadLevel(currentLevel);
}

void Game::loadLevel(int level) {
    bricks.clear();
    items.clear();

    // TUĞLALAR RESİMDEKİ GİBİ BİRBİRİNE YAKINLAŞTIRILDI
    float startX = 25.f; // Ekranı ortalamak için
    float startY = 80.f; // UI kısmına çarpmamak için aşağıdan başla

    int rows = 4 + (level / 5);
    if (rows > 8) rows = 8;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < 10; ++j) {
            int type = 1;

            if (level > 25 && (rand() % 100 < 10 + (level / 10))) { type = -1; }
            else if (level > 20 && (rand() % 100 < 15 + (level / 5))) { type = 4; }
            else if (level > 10 && (rand() % 100 < 20 + (level / 4))) { type = 3; }
            else if (level >= 3 && (rand() % 100 < 25 + (level / 3))) { type = 2; }

            // 75.f ve 30.f aralıklarla sıkı sıkı diziyoruz
            bricks.push_back(Brick(startX + j * 75.f, startY + i * 30.f, type));
        }
    }
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
        levelText.setString("Canlar: " + std::to_string(lives)); // Arayüzü güncelle
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
            else if (type == 2) { lives++; levelText.setString("Canlar: " + std::to_string(lives)); }
            else if (type == 3) {
                lives--;
                levelText.setString("Canlar: " + std::to_string(lives));
                if (lives <= 0) { paddle.reset(); ball.reset(); }
            }
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

    // Kırmızı can kutucuklarını çizen for döngüsünü tamamen sildik, arayüz daha temiz.

    // UI bölgesini ayırmak için ince bir çizgi (Opsiyonel estetik)
    sf::RectangleShape topBar(sf::Vector2f(800.f, 2.f));
    topBar.setPosition(0.f, 60.f);
    topBar.setFillColor(sf::Color(138, 43, 226, 100)); // Şeffaf Mor
    window.draw(topBar);

    for (auto& brick : bricks) { brick.draw(window); }
    for (auto& item : items) { item.draw(window); }

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
        winText.setString("TEBRIKLER!");
        winText.setCharacterSize(60);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(220.f, 250.f);
        window.draw(winText);
    }

    window.display();
}