#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h" 
#include "Ball.h"
#include "Brick.h"

class Game {
private:
    sf::RenderWindow window;
    Paddle paddle;
    Ball ball;
    std::vector<Brick> bricks; 

    void processEvents();
    void update();
    void render();

public:
    Game();
    void run();
};