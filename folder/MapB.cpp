#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int MapB() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "game");

    int gameMapB[40 * 40];
    sf::RectangleShape displayRects[40 * 40];

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            displayRects[i + j * 40].setPosition(i * 25.f, j * 25.f);
            displayRects[i + j * 40].setSize(sf::Vector2f(25.f, 25.f));
            displayRects[i + j * 40].setOutlineThickness(1.f);
            displayRects[i + j * 40].setOutlineColor(sf::Color(0, 0, 0));

            if (
                (i == 0 || i == 39 || j == 0 || j == 39) && // ทุกขอบ
                !(j == 0 && i == 20) &&  // เว้นตรงกลางขอบบน
                !(j == 39 && i == 20) // เว้นตรงกลางขอบล่าง
                ) {
                gameMapB[i + j * 40] = 1;
                displayRects[i + j * 40].setFillColor(sf::Color(0, 0, 0)); // กำแพงสีดำ
            }
            

        }
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color(255, 255, 255));

        for (int i = 0; i < 40 * 40; i++) {
            window.draw(displayRects[i]);
        }
        window.display();
    }
    return 0;
}