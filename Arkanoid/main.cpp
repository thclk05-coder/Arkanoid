#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kocaeli Uni Arkanoid - Can Sistemi");
    window.setFramerateLimit(60);

    // --- OYUN DEĞİŞKENLERİ ---
    int lives = 3; // Başlangıçta 3 canımız var

    // --- RAKET (PADDLE) ---
    sf::RectangleShape paddle(sf::Vector2f(100.f, 20.f));
    paddle.setFillColor(sf::Color::Green);
    paddle.setPosition(350.f, 550.f);

    // --- TOP (BALL) ---
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(390.f, 300.f);
    float ballSpeedX = 5.0f;
    float ballSpeedY = -5.0f;

    // --- BLOKLAR (BRICKS) DİZİLİMİ ---
    std::vector<sf::RectangleShape> bricks;
    float brickWidth = 60.f;
    float brickHeight = 20.f;
    float padding = 10.f;
    float startX = 55.f;
    float startY = 50.f;

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 10; ++col) {
            sf::RectangleShape brick(sf::Vector2f(brickWidth, brickHeight));
            brick.setFillColor(sf::Color::Red);
            float x = startX + col * (brickWidth + padding);
            float y = startY + row * (brickHeight + padding);
            brick.setPosition(x, y);
            bricks.push_back(brick);
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // --- KLAVYE KONTROLLERİ ---
        float paddleSpeed = 8.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            paddle.move(-paddleSpeed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            paddle.move(paddleSpeed, 0.f);
        }

        // --- RAKET SINIR KONTROLÜ ---
        if (paddle.getPosition().x < 0) paddle.setPosition(0.f, paddle.getPosition().y);
        if (paddle.getPosition().x + paddle.getSize().x > 800) paddle.setPosition(800.f - paddle.getSize().x, paddle.getPosition().y);

        // --- TOP HAREKETİ VE ÇARPIŞMALAR ---
        ball.move(ballSpeedX, ballSpeedY);

        // Sağ ve Sol Duvar
        if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= 800) ballSpeedX = -ballSpeedX;

        // Tavan
        if (ball.getPosition().y <= 0) ballSpeedY = -ballSpeedY;

        // YERE DÜŞME (CAN KAYBI)
        if (ball.getPosition().y + ball.getRadius() * 2 >= 600) {
            lives--; // Canı 1 azalt

            if (lives > 0) {
                // Eğer canı bitmediyse pozisyonları sıfırla
                paddle.setPosition(350.f, 550.f);
                ball.setPosition(390.f, 300.f);
                ballSpeedY = -5.0f; // Topu tekrar yukarı doğru yolla
            }
            else {
                // Canı bittiyse oyun bitsin (Şimdilik pencereyi kapatıyoruz)
                window.close();
            }
        }

        // --- TOP VE RAKET ÇARPIŞMASI ---
        if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
            ballSpeedY = -ballSpeedY;
            ball.setPosition(ball.getPosition().x, paddle.getPosition().y - ball.getRadius() * 2);
        }

        // --- TOP VE BLOKLARIN ÇARPIŞMASI (KIRILMA) ---
        for (size_t i = 0; i < bricks.size(); ++i) {
            if (ball.getGlobalBounds().intersects(bricks[i].getGlobalBounds())) {
                ballSpeedY = -ballSpeedY;
                bricks.erase(bricks.begin() + i);
                break;
            }
        }

        // --- ÇİZİM İŞLEMLERİ ---
        window.clear(sf::Color::Black);

        window.draw(paddle);
        window.draw(ball);
        for (const auto& brick : bricks) {
            window.draw(brick);
        }

        window.display();
    }
    return 0;
}