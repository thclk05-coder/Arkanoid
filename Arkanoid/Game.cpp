#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Kocaeli Uni Arkanoid - Parcali Sistem") {
    window.setFramerateLimit(60); // fps'i 60a sabitledim pc yorulmasin
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
            window.close(); // carpiya basinca kapansin
    }

    // klavye kontrolleri a, d ve yon tuslari
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        paddle.moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        paddle.moveRight();
    }
}

void Game::update() {
    paddle.update(800.f); // sinir kontrolu icin ekran genisligini yolladim
}

void Game::render() {
    window.clear(sf::Color(30, 30, 30)); // arka plan rengi

    paddle.draw(window); // raketi cizdiriyorum

    window.display();
}