#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kocaeli Uni Arkanoid - Solo Dev");
    window.setFramerateLimit(60);

    // --- RAKET (PADDLE) ---
    sf::RectangleShape paddle(sf::Vector2f(100.f, 20.f));
    paddle.setFillColor(sf::Color::Green);
    paddle.setPosition(350.f, 550.f);

    // --- TOP (BALL) ---
    sf::CircleShape ball(10.f); // 10 piksel yarıçapında bir top
    ball.setFillColor(sf::Color::White);
    ball.setPosition(390.f, 300.f); // Ekranın ortasından başlasın

    // Topun X ve Y eksenindeki hızı
    float ballSpeedX = 5.0f;
    float ballSpeedY = -5.0f; // Eksi değer yukarı doğru gitmesini sağlar

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
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

        // --- TOP HAREKETİ ---
        ball.move(ballSpeedX, ballSpeedY);

        // --- TOP DUVAR ÇARPIŞMALARI ---
        // Sol veya Sağ duvara çarparsa X hızını tersine çevir
        if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= 800) {
            ballSpeedX = -ballSpeedX;
        }
        // Tavana çarparsa Y hızını tersine çevir
        if (ball.getPosition().y <= 0) {
            ballSpeedY = -ballSpeedY;
        }
        // Yere düşerse (Şimdilik sadece seksin, ileride burada can azaltacağız)
        if (ball.getPosition().y + ball.getRadius() * 2 >= 600) {
            ballSpeedY = -ballSpeedY;
            // İleride buraya "lives--;" yazacağız
        }

        // --- TOP VE RAKET ÇARPIŞMASI ---
        // Eğer topun sınırları ile raketin sınırları kesişirse (intersects)
        if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
            // Topu yukarı doğru sektir
            ballSpeedY = -ballSpeedY;

            // Topun raketin içine girmesini (bug'da kalmasını) engellemek için topu biraz yukarı itelim
            ball.setPosition(ball.getPosition().x, paddle.getPosition().y - ball.getRadius() * 2);
        }

        // --- ÇİZİM İŞLEMLERİ ---
        window.clear(sf::Color::Black);

        window.draw(paddle);
        window.draw(ball); // Topu çiziyoruz

        window.display();
    }
    return 0;
}