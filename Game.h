#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // Rastgele sayılar için
#include <ctime>   // Zaman seed'i için 
#include <string>  // std::string kullanımı için
#include <fstream> // Dosya okuma (loadLevel için)
#include <sstream> // Metin parçalama (loadLevel için)
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

    // YENİ: Otomatik bölüm yükleme sistemi
    void loadLevel(int level);
    bool isPlusPressed;

    // Pencere
    sf::RenderWindow window;

    // Arka Plan Görseli
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