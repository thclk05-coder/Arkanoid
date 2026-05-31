#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(1920, 1080), "Kocaeli Uni Arkanoid - Taha Celik", sf::Style::Default) {
    srand(static_cast<unsigned>(time(NULL)));
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

    state = MENU;
    lives = 3;
    score = 0;
    currentLevel = 1;
    isPlusPressed = false;
    menuSelectedIndex = 0; // Başlangıçta 0. seçenek (Yeni Oyun) seçili

    if (!bgTexture.loadFromFile("C:\\Users\\thclk\\Desktop\\Arkanoid\\arkaplan.jpg")) {
        std::cout << "ARKA PLAN BULUNAMADI!" << std::endl;
    }
    else {
        bgSprite.setTexture(bgTexture);
        bgSprite.setScale(800.f / bgTexture.getSize().x, 600.f / bgTexture.getSize().y);
    }

    font.loadFromFile("C:\\Users\\thclk\\Desktop\\Arkanoid\\font.ttf");

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(135, 206, 250));
    scoreText.setPosition(100.f, 15.f);

    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color(138, 43, 226));
    levelText.setPosition(600.f, 15.f);

    centerText.setFont(font);
    centerText.setCharacterSize(40);
    centerText.setFillColor(sf::Color::White);

    // ==========================================
    // YENİ: ANA MENÜ TASARIMI VE YERLEŞİMİ
    // ==========================================
    menuTitle.setFont(font);
    menuTitle.setString("ARKANOID");
    menuTitle.setCharacterSize(75);
    menuTitle.setFillColor(sf::Color(138, 43, 226)); // Neon Mor
    menuTitle.setPosition(210.f, 100.f); // Ekranı ortalayacak şekilde

    menuOpt1.setFont(font);
    menuOpt1.setString("YENI OYUN");
    menuOpt1.setCharacterSize(35);
    menuOpt1.setPosition(300.f, 300.f);

    menuOpt2.setFont(font);
    menuOpt2.setString("DEVAM ET");
    menuOpt2.setCharacterSize(35);
    menuOpt2.setPosition(310.f, 360.f);

    menuOpt3.setFont(font);
    menuOpt3.setString("CIKIS");
    menuOpt3.setCharacterSize(35);
    menuOpt3.setPosition(345.f, 420.f);
}

void Game::loadLevel(int level) {
    bricks.clear();
    items.clear();
    float startX = 25.f;
    float startY = 80.f;

    std::string filename = "C:\\Users\\thclk\\Desktop\\Arkanoid\\level" + std::to_string(level) + ".txt";
    std::ifstream file(filename);

    if (file.is_open()) {
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
    scoreText.setString("Puan: " + std::to_string(score));
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

        // ESC TUŞU İLE OYUNU DURDURUP MENÜYE DÖNME
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (state == PLAYING) state = MENU; // Oyunu Pause'a al
            else if (state == MENU) window.close(); // Menüdeyken basarsa kapat
        }

        // MENÜ İÇİ YÖNLENDİRME (YUKARI, AŞAĞI, ENTER)
        if (state == MENU && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                menuSelectedIndex--;
                if (menuSelectedIndex < 0) menuSelectedIndex = 2; // En üste gelince alta dön
            }
            else if (event.key.code == sf::Keyboard::Down) {
                menuSelectedIndex++;
                if (menuSelectedIndex > 2) menuSelectedIndex = 0; // En alta gelince üste dön
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                if (menuSelectedIndex == 0) { // YENİ OYUN
                    lives = 3;
                    score = 0;
                    currentLevel = 1;
                    state = PLAYING;
                    loadLevel(currentLevel);
                }
                else if (menuSelectedIndex == 1) { // DEVAM ET
                    if (lives <= 0 || currentLevel > 100) { // Oyun bitmişse mecbur sıfırdan başlat
                        lives = 3;
                        score = 0;
                        currentLevel = 1;
                        loadLevel(currentLevel);
                    }
                    state = PLAYING; // Kaldığı yerden devam
                }
                else if (menuSelectedIndex == 2) { // ÇIKIŞ
                    window.close();
                }
            }
        }

        // LEVEL GEÇİŞİ VE DİĞER DURUMLAR İÇİN SPACE
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            if (state == TRANSITION) {
                currentLevel++;
                if (currentLevel > 100) { state = WIN; }
                else { state = PLAYING; loadLevel(currentLevel); }
            }
            else if (state == GAMEOVER || state == WIN) {
                state = MENU; // Bittiğinde menüye dön
                menuSelectedIndex = 0;
            }
        }
    }

    if (state == PLAYING && (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) || sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))) {
        if (!isPlusPressed) {
            state = TRANSITION;
            isPlusPressed = true;
        }
    }
    else {
        isPlusPressed = false;
    }

    if (state == PLAYING && lives > 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) paddle.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) paddle.moveRight();
    }
}

void Game::update() {
    if (state != PLAYING) return;

    bool allDestroyed = true;
    for (auto& brick : bricks) {
        if (!brick.isDestroyed() && brick.getHp() != -1) {
            allDestroyed = false;
            break;
        }
    }

    if (allDestroyed) {
        state = TRANSITION;
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
                    sf::FloatRect bB = bricks[i].getBounds();
                    items.push_back(Item(bB.left + bB.width / 2.f, bB.top, randomType));
                }
            }
            break;
        }
    }

    if (ball.getBounds().top > 600.f) {
        lives--;
        if (lives > 0) { paddle.reset(); ball.reset(); }
        else { state = GAMEOVER; }
    }

    for (int i = 0; i < items.size(); i++) {
        items[i].update();
        if (items[i].getBounds().intersects(paddle.getBounds())) {
            int type = items[i].getType();
            if (type == 1) { score += 50; scoreText.setString("Puan: " + std::to_string(score)); }
            else if (type == 2) { lives++; }
            else if (type == 3) { lives--; if (lives <= 0) { state = GAMEOVER; } }
            items.erase(items.begin() + i); i--;
        }
        else if (items[i].getBounds().top > 600.f) { items.erase(items.begin() + i); i--; }
    }
}

void Game::render() {
    window.clear();
    window.draw(bgSprite);

    if (state == MENU) {
        // Hangi seçenekteysek onun rengini Sarı yapıyoruz, diğerleri Beyaz kalıyor
        menuOpt1.setFillColor(menuSelectedIndex == 0 ? sf::Color::Yellow : sf::Color::White);
        menuOpt2.setFillColor(menuSelectedIndex == 1 ? sf::Color::Yellow : sf::Color::White);
        menuOpt3.setFillColor(menuSelectedIndex == 2 ? sf::Color::Yellow : sf::Color::White);

        window.draw(menuTitle);
        window.draw(menuOpt1);
        window.draw(menuOpt2);
        window.draw(menuOpt3);
    }
    else if (state == TRANSITION) {
        centerText.setString("BOLUM " + std::to_string(currentLevel) + " TAMAMLANDI!\n\nDevam Etmek Icin SPACE'e Bas");
        centerText.setPosition(130.f, 250.f);
        window.draw(centerText);
    }
    else if (state == GAMEOVER) {
        centerText.setString("OYUN BITTI!\nSkor: " + std::to_string(score) + "\n\nMenuye Donmek Icin SPACE'e Bas");
        centerText.setFillColor(sf::Color::Red);
        centerText.setPosition(180.f, 220.f);
        window.draw(centerText);
    }
    else if (state == WIN) {
        centerText.setString("TEBRIKLER! OYUNU BITIRDIN!\n\nMenuye Donmek Icin SPACE'e Bas");
        centerText.setFillColor(sf::Color::Green);
        centerText.setPosition(120.f, 250.f);
        window.draw(centerText);
    }
    else if (state == PLAYING) {
        for (auto& b : bricks) b.draw(window);
        for (auto& i : items) i.draw(window);

        window.draw(scoreText);
        window.draw(levelText);

        sf::Text lText;
        lText.setFont(font);
        lText.setCharacterSize(24);
        lText.setFillColor(sf::Color(135, 206, 250));
        lText.setPosition(350.f, 15.f);
        lText.setString("Can: " + std::to_string(lives));
        window.draw(lText);

        paddle.draw(window);
        ball.draw(window);
    }

    window.display();
}