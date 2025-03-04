#include <SFML/Graphics.hpp>
#include <iostream>

const int WIDTH = 40;
const int HEIGHT = 40;
const int CELL_SIZE = 25;

// 🏗 แผนที่กำหนดเอง (1 = กำแพง, 0 = ทางเดิน)
int gameMap[HEIGHT][WIDTH] = {  // กำแพงรอบขอบ เว้นตรงกลางบนล่าง
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1},
    {1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1},
    {1,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0},
    {1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
    // ... (กำหนดแถวที่เหลือเอง)
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE), "Custom Maze");
    sf::RectangleShape displayRects[WIDTH * HEIGHT];

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            int index = i + j * WIDTH;
            displayRects[index].setPosition(i * CELL_SIZE, j * CELL_SIZE);
            displayRects[index].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            displayRects[index].setOutlineThickness(1.f);
            displayRects[index].setOutlineColor(sf::Color(0, 0, 0));

            if (gameMap[j][i] == 1) {
                displayRects[index].setFillColor(sf::Color(0, 0, 0)); // กำแพงสีดำ
            }
            else {
                displayRects[index].setFillColor(sf::Color(255, 255, 255)); // ทางเดิน
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

        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            window.draw(displayRects[i]);
        }
        window.display();
    }

    return 0;
}
