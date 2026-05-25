#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

class Game {
public:
    Game();
    void run();

private:
    // Temel oyun döngüsü fonksiyonları
    void processEvents();
    void update();
    void render();

    // Pencere
    sf::RenderWindow window;

    // Font ve Skor Metni (Çift yazılanları sildim)
    sf::Font font;
    sf::Text scoreText;

    // Oyun Değişkenleri
    int lives;
    int score;

    // Oyun Objeleri
    Paddle paddle;
    Ball ball;
    std::vector<Brick> bricks;
};