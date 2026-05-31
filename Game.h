#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // Rastgele sayilar icin
#include <ctime>   // Zaman seed'i icin 
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Item.h"

class Game {
public:
    Game();
    void run();

private:
    // Temel oyun döngüsü fonksiyonları
    void processEvents();
    void update();
    void render();
    bool isPlusPressed;

    // YENİ: Otomatik bölüm yükleme sistemi
    void loadLevel(int level);

    // Pencere
    sf::RenderWindow window;

    // YENİ EKLENEN: Arka Plan Görseli için değişkenler
    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    // Font ve Skor Metni
    sf::Font font;
    sf::Text scoreText;
    sf::Text levelText;

    // Oyun Değişkenleri
    int lives;
    int score;
    int currentLevel;

    // Oyun Objeleri
    Paddle paddle;
    Ball ball;
    std::vector<Brick> bricks;
    std::vector<Item> items; // Ekranda süzülen itemleri tutacağımız liste
};