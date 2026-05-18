#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Kocaeli Uni Arkanoid - Project")
{
    window.setFramerateLimit(60);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update() {
}

void Game::render() {
    window.clear(sf::Color(30, 30, 30));
    window.display();
}