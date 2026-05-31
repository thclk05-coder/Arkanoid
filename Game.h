#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <string>  
#include <fstream> 
#include <sstream> 
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Item.h"
#include <SFML/Audio.hpp>

class Game {
public:
    enum GameState { MENU, PLAYING, TRANSITION, GAMEOVER, WIN };

    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void loadLevel(int level);
    sf::SoundBuffer bufferTugla, bufferMenu, bufferGameOver;
    sf::Sound soundTugla, soundMenu, soundGameOver;

    GameState state;
    bool isPlusPressed;

    sf::RenderWindow window;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    sf::Font font;
    sf::Text scoreText;
    sf::Text levelText;
    sf::Text centerText;

    // YENİ: ANA MENÜ ELEMANLARI
    sf::Text menuTitle;
    sf::Text menuOpt1; // YENİ OYUN
    sf::Text menuOpt2; // DEVAM ET
    sf::Text menuOpt3; // ÇIKIŞ
    int menuSelectedIndex; // Hangi seçeneğin üzerinde olduğumuzu tutar

    int lives;
    int score;
    int currentLevel;

    Paddle paddle;
    Ball ball;
    std::vector<Brick> bricks;
    std::vector<Item> items;
};