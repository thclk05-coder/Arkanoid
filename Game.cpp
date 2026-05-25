#include "Game.h"
#include <iostream>

// Ana oyun penceresi oluşturuluyor
Game::Game() : window(sf::VideoMode(800, 600), "Kocaeli Uni Arkanoid - Taha Celik") {

    // FPS sabitleme (oyun fazla hızlanmasın)
    window.setFramerateLimit(60);

    // Başlangıç can ve skor
    lives = 3;
    score = 0;

    // Arial bozuk çıktığı için çalışan fontu kullandım
    if (!font.loadFromFile("C:\\Users\\thclk\\Desktop\\Arkanoid\\font.ttf")) {
        std::cout << "FONT YUKLENEMEDI" << std::endl;
    }

    // Skor yazısı ayarları
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);

    // Yazının daha görünür olması için kenarlık ekledim
    scoreText.setOutlineThickness(2.f);
    scoreText.setOutlineColor(sf::Color::Black);

    // Skorun ekrandaki konumu (sol alt)
    scoreText.setPosition(20.f, 540.f);
    scoreText.setString("Skor: 0");

    // Tuğlaların başlangıç pozisyonları
    float startX = 50.f;
    float startY = 80.f;

    // Tuğlaları oluşturma (5 satır, 10 sütun)
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            // Her döngüde yeni tuğla ekleniyor
            bricks.push_back(Brick(startX + j * 70.f, startY + i * 30.f));
        }
    }
}

// Ana oyun döngüsü
void Game::run() {
    while (window.isOpen()) {
        // Olayları kontrol et
        processEvents();

        // Oyunu güncelle
        update();

        // Ekrana çiz
        render();
    }
}

// Klavye ve pencere olayları
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        // Pencere kapatılırsa oyun kapanır
        if (event.type == sf::Event::Closed)
            window.close();
    }

    // Can varsa raket hareket etsin
    if (lives > 0) {
        // A veya sol ok -> sola git
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            paddle.moveLeft();
        }
        // D veya sağ ok -> sağa git
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paddle.moveRight();
        }
    }
}

// Oyun içi güncellemeler
void Game::update() {
    // Can bittiyse oyun durur
    if (lives <= 0) return;

    // Tüm tuğlalar kırıldı mı kontrolü
    bool allDestroyed = true;
    for (auto& brick : bricks) {
        if (!brick.isDestroyed()) {
            allDestroyed = false;
            break;
        }
    }

    // Hepsi kırıldıysa güncelleme yapma
    if (allDestroyed) return;

    // Raket ve top güncelleme
    paddle.update(800.f);
    ball.update(800.f, 600.f);

    // Top rakete çarptı mı
    if (ball.getBounds().intersects(paddle.getBounds())) {
        // Top sekme işlemi
        ball.bounceOffPaddle(paddle.getBounds().top);
    }

    // Tuğla çarpışmaları
    for (size_t i = 0; i < bricks.size(); ++i) {
        if (!bricks[i].isDestroyed() && ball.getBounds().intersects(bricks[i].getBounds())) {

            // Tuğlayı yok et
            bricks[i].destroy();

            // Topun yönünü ters çevir (ışınlanma hatasını çözmek için)
            ball.reverseY();

            // Skor artır
            score += 10;

            // Yeni skoru ekrana yaz
            scoreText.setString("Skor: " + std::to_string(score));
            break;
        }
    }

    // Top aşağı düşerse can azalt
    if (ball.getBounds().top > 600.f) {
        lives--;

        // Hala can varsa oyunu sıfırla
        if (lives > 0) {
            paddle.reset();
            ball.reset();
        }
    }
}

// Çizim işlemleri
void Game::render() {
    // Arka plan rengi (koyu gri)
    window.clear(sf::Color(30, 30, 30));

    // Tuğlaları çiz
    for (auto& brick : bricks) {
        brick.draw(window);
    }

    // Can göstergesi çizimi (kırmızı kareler)
    for (int i = 0; i < lives; i++) {
        sf::RectangleShape lifeIcon(sf::Vector2f(15.f, 15.f));
        lifeIcon.setFillColor(sf::Color::Red);

        // Her can biraz sağa kaydırılıyor
        lifeIcon.setPosition(20.f + (i * 25.f), 20.f);
        window.draw(lifeIcon);
    }

    // Skoru çiz (raketin altında kalması için önce çizdiriyoruz)
    window.draw(scoreText);

    // Raketi ve topu çiz
    paddle.draw(window);
    ball.draw(window);

    // Oyun bitme ekranı
    if (lives <= 0) {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("OYUN BITTI!");
        gameOverText.setCharacterSize(60);

        // Kırmızı renk
        gameOverText.setFillColor(sf::Color::Red);

        // Ortaya yakın konum
        gameOverText.setPosition(220.f, 250.f);
        window.draw(gameOverText);
    }
    else {
        // Kazanma kontrolü
        bool allDestroyed = true;
        for (auto& brick : bricks) {
            if (!brick.isDestroyed()) {
                allDestroyed = false;
                break;
            }
        }

        // Kazanma yazısı
        if (allDestroyed) {
            sf::Text winText;
            winText.setFont(font);
            winText.setString("TEBRIKLER KAZANDIN!");
            winText.setCharacterSize(50);

            // Yeşil renk
            winText.setFillColor(sf::Color::Green);
            winText.setPosition(150.f, 250.f);
            window.draw(winText);
        }
    }

    // Ekranı güncelle
    window.display();
}