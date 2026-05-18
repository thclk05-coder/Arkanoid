#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h" // raketi dahil ettim

class Game {
private:
    sf::RenderWindow window;
    Paddle paddle; // raket objesi

    void processEvents();
    void update();
    void render();

public:
    Game();
    void run();
};