#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h" 
#include "Ball.h"

class Game {
private:
    sf::RenderWindow window;
    Paddle paddle;
    Ball ball;

    void processEvents();
    void update();
    void render();

public:
    Game();
    void run();
};