#include "Game.h"
#include <iostream>

// Ana oyun penceresi oluşturuluyor
Game::Game() : window(sf::VideoMode(800, 600), "Kocaeli Uni Arkanoid - Taha Celik") {

    // Rastgele sayı üretecini zamana göre başlat (her oynayışta farklı dizilim gelsin)
    srand(static_cast<unsigned>(time(NULL)));

    // FPS sabitleme (oyun fazla hızlanmasın)
    window.setFramerateLimit(60);

    // Başlangıç can, skor ve level atamaları
    lives = 3;
    score = 0;
    currentLevel = 1;

    // Level atlama tuşunun basılı kalma durumunu kontrol eden değişken
    isPlusPressed = false;

    // Arial bozuk çıktığı için çalışan fontu kullandım
    if (!font.loadFromFile("C:\\Users\\thclk\\Desktop\\Arkanoid\\font.ttf")) {
        std::cout << "FONT YUKLENEMEDI" << std::endl;
    }

    // Skor yazısı ayarları
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineThickness(2.f);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setPosition(20.f, 20.f);
    scoreText.setString("Skor: 0");

    // Level metni ayarları 
    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::Yellow);
    levelText.setOutlineThickness(2.f);
    levelText.setOutlineColor(sf::Color::Black);
    levelText.setPosition(650.f, 20.f);
    levelText.setString("Level: 1");

    // ARTIK MANUEL TUĞLA DİZMİYORUZ, FONKSİYON KENDİ HALLEDECEK
    loadLevel(currentLevel);
}

// BÖLÜM YÜKLEME VE ZORLUK ALGORİTMASI 
void Game::loadLevel(int level) {
    // Önceki bölümün tuğlalarını temizle
    bricks.clear();

    float startX = 50.f;
    float startY = 80.f;

    // Level arttıkça satır sayısı artsın (Max 8 satır olsun ki ekrandan taşmasın)
    int rows = 4 + (level / 5);
    if (rows > 8) rows = 8;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < 10; ++j) {

            int type = 1; // Varsayılan: normal kırmızı tuğla

            // Zorluk motoru:
            // Level 3'ten sonra giderek artan ihtimalle sert (2 canlı) tuğla at
            if (level >= 3 && (rand() % 100 < 20 + (level * 2))) {
                type = 2;
            }

            // Level 5'ten sonra %10 ihtimalle kırılamaz beton duvar (gri) at
            if (level >= 5 && (rand() % 100 < 10)) {
                type = -1;
            }

            bricks.push_back(Brick(startX + j * 70.f, startY + i * 30.f, type));
        }
    }

    // Arayüzdeki level yazısını güncelle
    levelText.setString("Level: " + std::to_string(level));

    // Yeni bölüme geçerken topu ve raketi merkeze sıfırla
    paddle.reset();
    ball.reset();
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

    // LEVEL ATLAMA HİLESİ (DEBUG İÇİN) - SADECE TEK TIKLAMA İLE ÇALIŞIR
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) || sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
        if (!isPlusPressed) { // Tuşa yeni mi basıldı kontrolü
            currentLevel++;
            if (currentLevel <= 100) {
                loadLevel(currentLevel);
            }
            isPlusPressed = true; // Basılı tutuluyor moduna al ki peş peşe atlamasın
        }
    }
    else {
        isPlusPressed = false; // Tuş bırakıldığında kilidi aç
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

    // Tüm kırılabilir tuğlalar bitti mi?
    bool allDestroyed = true;
    for (auto& brick : bricks) {
        if (!brick.isDestroyed() && brick.getHp() != -1) {
            allDestroyed = false;
            break;
        }
    }

    // EĞER BÖLÜM BİTTİYSE YENİ BÖLÜME GEÇİŞ YAP
    if (allDestroyed) {
        currentLevel++;
        if (currentLevel > 100) {
            return; // 100 level geçildiyse oyunu tamamen bitir
        }
        loadLevel(currentLevel); // Sonraki leveli yükle
        return; // Çarpışmaları hesaplamadan bu döngüyü atla
    }

    paddle.update(800.f);
    ball.update(800.f, 600.f);

    if (ball.getBounds().intersects(paddle.getBounds())) {
        ball.bounceOffPaddle(paddle.getBounds().top);
    }

    // Tuğla çarpışmaları
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
        lifeIcon.setPosition(20.f + (i * 25.f), 550.f);
        window.draw(lifeIcon);
    }

    window.draw(scoreText);
    window.draw(levelText);

    paddle.draw(window);
    ball.draw(window);

    // Oyun bitme ekranı
    if (lives <= 0) {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("OYUN BITTI!");
        gameOverText.setCharacterSize(60);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(220.f, 250.f);
        window.draw(gameOverText);
    }
    // 100 LEVEL GEÇİLİNCE KAZANILACAK EKRAN
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