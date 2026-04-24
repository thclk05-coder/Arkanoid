#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kocaeli Uni Arkanoid - Canli Sistem");
    window.setFramerateLimit(60);

    // --- OYUN DEĞİŞKENLERİ ---
    int lives = 3;

    // --- RAKET (PADDLE) ---
    sf::RectangleShape paddle(sf::Vector2f(120.f, 20.f));
    paddle.setFillColor(sf::Color::Green);
    paddle.setPosition(340.f, 550.f);

    // --- TOP (BALL) ---
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(390.f, 300.f);
    float ballSpeedX = 5.0f;
    float ballSpeedY = -5.0f;

    // --- TUĞLALAR (BRICKS) ---
    std::vector<sf::RectangleShape> bricks;
    float startX = 50.f;
    float startY = 80.f;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            sf::RectangleShape brick(sf::Vector2f(65.f, 25.f));
            brick.setFillColor(sf::Color::Red);
            brick.setOutlineThickness(1.f);
            brick.setOutlineColor(sf::Color::Black);
            brick.setPosition(startX + j * 70.f, startY + i * 30.f);
            bricks.push_back(brick);
        }
    }

    // --- ANA OYUN DÖNGÜSÜ ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // --- KONTROLLER (A-D / OKLAR) ---
        float paddleSpeed = 9.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) paddle.move(-paddleSpeed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) paddle.move(paddleSpeed, 0.f);

        if (paddle.getPosition().x < 0) paddle.setPosition(0.f, paddle.getPosition().y);
        if (paddle.getPosition().x + paddle.getSize().x > 800) paddle.setPosition(800.f - paddle.getSize().x, paddle.getPosition().y);

        // --- TOP HAREKETİ ---
        ball.move(ballSpeedX, ballSpeedY);

        if (ball.getPosition().x <= 0 || ball.getPosition().x + 20 >= 800) ballSpeedX = -ballSpeedX;
        if (ball.getPosition().y <= 0) ballSpeedY = -ballSpeedY;

        // Yere Düşme (Can Kaybı)
        if (ball.getPosition().y + 20 >= 600) {
            lives--;
            if (lives > 0) {
                ball.setPosition(390.f, 300.f);
                paddle.setPosition(340.f, 550.f);
                ballSpeedY = -5.0f;
            }
            else {
                window.close();
            }
        }

        if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
            ballSpeedY = -ballSpeedY;
            ball.setPosition(ball.getPosition().x, paddle.getPosition().y - 20.f);
        }

        for (size_t i = 0; i < bricks.size(); ++i) {
            if (ball.getGlobalBounds().intersects(bricks[i].getGlobalBounds())) {
                ballSpeedY = -ballSpeedY;
                bricks.erase(bricks.begin() + i);
                break;
            }
        }

        // --- ÇİZİM ---
        window.clear(sf::Color(30, 30, 30));

        for (const auto& b : bricks) window.draw(b);
        window.draw(paddle);
        window.draw(ball);

        // --- CAN GÖSTERGESİ (KÜÇÜK KARELER) ---
        // Kaç canımız varsa o kadar küçük kırmızı kare çizdiriyoruz
        for (int i = 0; i < lives; i++) {
            sf::RectangleShape lifeIcon(sf::Vector2f(15.f, 15.f));
            lifeIcon.setFillColor(sf::Color::Red);
            // Sol üst köşede yan yana dizilmeleri için X koordinatını i ile çarpıyoruz
            lifeIcon.setPosition(20.f + (i * 25.f), 20.f);
            window.draw(lifeIcon);
        }

        window.display();
    }

    return 0;
}