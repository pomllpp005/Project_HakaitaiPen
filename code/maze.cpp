﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
int gameMap[40 * 40];
sf::RenderWindow window(sf::VideoMode(1000, 1000), "Mazegame");
sf::RectangleShape displayRects[40 * 40];
sf::Texture wallTexture1;
sf::Texture wallTexture2;
sf::Texture playerTex;
void Map1();
void Map2();


int main() {
    sf::Vector2i player = sf::Vector2i(20, 0);
    playerTex.loadFromFile("smile.png");
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTex);
    playerSprite.setScale(0.045f, 0.045f);
    playerSprite.setPosition(player.x * 25.f, player.y * 25.f);
	int Mode = 0;
    
    while (window.isOpen()) {
        if(Mode==0)Map2();
        if(Mode==1)Map1();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                sf::Vector2i newPosition = player;
                switch (event.key.code) {
                case sf::Keyboard::W: // Move up
                    newPosition.y -= 1;
                    break;
                case sf::Keyboard::S: // Move down
                    newPosition.y += 1;
                    break;
                case sf::Keyboard::D: // Move right
                    newPosition.x += 1;
                    break;
                case sf::Keyboard::A: // Move left
                    newPosition.x -= 1;
                    break;
                }

                // Check for collision
                if (gameMap[newPosition.x + newPosition.y * 40] != 1) {
                    player = newPosition;
                    std::cout << "Player position: (" << player.x << ", " << player.y << ")" << std::endl;
                }
            }

            playerSprite.setPosition(player.x * 25.f, player.y * 25.f);
        }
        window.clear(sf::Color(255, 255, 255));

        for (int i = 0; i < 40 * 40; i++) {
            window.draw(displayRects[i]);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
        window.draw(playerSprite);
        if (player.x == 20 && player.y == 39) 
        { 
			player.x = 20;
			player.y = 0;
            window.clear(); 
            Mode = 1; 
        }
        window.display();
    }
    return 0;
}

void Map1() {
    wallTexture1.loadFromFile("brick.png");
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            displayRects[i + j * 40].setPosition(i * 25.f, j * 25.f);
            displayRects[i + j * 40].setSize(sf::Vector2f(25.f, 25.f));
            /*displayRects[i + j * 40].setOutlineThickness(1.f);*/
            displayRects[i + j * 40].setOutlineColor(sf::Color(0, 0, 0));

            if (
                (i == 0 || i == 39 || j == 0 || j == 39) && // ทุกขอบ
                !(j == 0 && i == 20) &&  // เว้นตรงกลางขอบบน
                !(j == 39 && i == 20) // เว้นตรงกลางขอบล่าง
                ) {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture1); // กำแพงสีดำ
            }
            if ((i == 1 && j == 8) || (i == 1 && j == 12) || (i == 1 && j == 17) || (i == 1 && j == 19) || (i == 1 && j == 27) || (i == 1 && j == 35)
                || (i == 2 && j > 1 && j < 9) || (i == 2 && j == 10) || (i == 2 && j > 11 && j < 14) || (i == 2 && j > 14 && j < 18) || (i == 2 && j == 19) || (i == 2 && j > 20 && j < 26) || (i == 2 && j == 27) || (i == 2 && j > 28 && j < 36) || (i == 2 && j > 36 && j < 39)
                || (i == 3 && j == 4) || (i == 3 && j == 8) || (i == 3 && j == 10) || (i == 3 && j == 12) || (i == 3 && j == 15) || (i == 3 && j == 17) || (i == 3 && j == 21) || (i == 3 && j == 25) || (i == 3 && j == 27) || (i == 3 && j == 31) || (i == 3 && j == 33)
                || (i == 4 && j > 0 && j < 3) || (i == 4 && j > 3 && j < 7) || (i == 4 && j > 7 && j < 11) || (i == 4 && j > 11 && j < 14) || (i == 4 && j == 15) || (i == 4 && j == 17) || (i == 4 && j == 19) || (i == 4 && j == 21) || (i == 4 && j > 22 && j < 30) || (i == 4 && j == 31) || (i == 4 && j == 33) || (i == 4 && j > 34 && j < 38)
                || (i == 5 && j == 4) || (i == 5 && j == 6) || (i == 5 && j == 8) || (i == 5 && j == 12) || (i == 5 && j == 17) || (i == 5 && j == 19) || (i == 5 && j == 29) || (i == 5 && j == 31) || (i == 5 && j == 35)
                || (i == 6 && j > 1 && j < 5) || (i == 6 && j == 6) || (i == 6 && j == 8) || (i == 6 && j > 9 && j < 13) || (i == 6 && j == 15) || (i == 6 && j == 17) || (i == 6 && j > 18 && j < 26) || (i == 6 && j > 26 && j < 30) || (i == 6 && j > 30 && j < 34) || (i == 6 && j > 34 && j < 38)
                || (i == 7 && j == 8) || (i == 7 && j == 10) || (i == 7 && j == 15) || (i == 7 && j == 25) || (i == 7 && j == 31) || (i == 7 && j == 33) || (i == 7 && j == 35)
                || (i == 8 && j > 0 && j < 7) || (i == 8 && j == 10) || (i == 8 && j > 11 && j < 18) || (i == 8 && j == 19) || (i == 8 && j > 20 && j < 30) || (i == 8 && j == 31) || (i == 8 && j > 32 && j < 36) || (i == 8 && j > 36 && j < 39)
                || (i == 9 && j == 8) || (i == 9 && j == 15) || (i == 9 && j == 17) || (i == 9 && j == 19) || (i == 9 && j == 29) || (i == 9 && j == 33) || (i == 9 && j == 35)
                || (i == 10 && j > 1 && j < 11) || (i == 10 && j > 11 && j < 16) || (i == 10 && j > 16 && j < 32) || (i == 10 && j == 33) || (i == 10 && j > 34 && j < 38)
                || (i == 11 && j == 5) || (i == 11 && j == 7) || (i == 11 && j == 21) || (i == 11 && j == 29) || (i == 11 && j == 31) || (i == 11 && j == 33)
                || (i == 12 && j > 0 && j < 3) || (i == 12 && j > 3 && j < 6) || (i == 12 && j > 6 && j < 18) || (i == 12 && j > 18 && j < 28) || (i == 12 && j == 29) || (i == 12 && j > 30 && j < 38)
                || (i == 13 && j == 11) || (i == 13 && j == 19) || (i == 13 && j == 23) || (i == 13 && j == 27) || (i == 13 && j == 29) || (i == 13 && j == 33) || (i == 13 && j == 35) || (i == 13 && j == 37)
                || (i == 14 && j > 1 && j < 5) || (i == 14 && j > 5 && j < 12) || (i == 14 && j > 12 && j < 18) || (i == 14 && j == 19) || (i == 14 && j == 21) || (i == 14 && j == 23) || (i == 14 && j == 25) || (i == 14 && j == 29) || (i == 14 && j == 31) || (i == 14 && j == 33) || (i == 14 && j == 35) || (i == 14 && j == 37)
                || (i == 15 && j == 2) || (i == 15 && j == 9) || (i == 15 && j == 13) || (i == 15 && j == 15) || (i == 15 && j == 17) || (i == 15 && j > 18 && j < 22) || (i == 15 && j == 25) || (i == 15 && j == 27) || (i == 15 && j == 29) || (i == 15 && j > 30 && j < 34) || (i == 15 && j == 37)
                || (i == 16 && j == 2) || (i == 16 && j > 3 && j < 10) || (i == 16 && j > 10 && j < 14) || (i == 16 && j == 15) || (i == 16 && j == 17) || (i == 16 && j == 19) || (i == 16 && j == 23) || (i == 16 && j == 25) || (i == 16 && j == 27) || (i == 16 && j > 34 && j < 38)
                || (i == 17 && j > 0 && j < 3) || (i == 17 && j == 6) || (i == 17 && j == 13) || (i == 17 && j == 15) || (i == 17 && j == 17) || (i == 17 && j == 19) || (i == 17 && j > 20 && j < 24) || (i == 17 && j == 25) || (i == 17 && j > 26 && j < 36)
                || (i == 18 && j > 3 && j < 7) || (i == 18 && j == 8) || (i == 18 && j > 9 && j < 12) || (i == 18 && j == 13) || (i == 18 && j == 15) || (i == 18 && j == 19) || (i == 18 && j == 21) || (i == 18 && j == 23) || (i == 18 && j == 25) || (i == 18 && j == 37)
                || (i == 19 && j > 1 && j < 5) || (i == 19 && j == 8) || (i == 19 && j == 10) || (i == 19 && j == 13) || (i == 19 && j > 14 && j < 18) || (i == 19 && j == 19) || (i == 19 && j == 21) || (i == 19 && j > 22 && j < 30) || (i == 19 && j > 30 && j < 36) || (i == 19 && j > 36 && j < 39)
                || (i == 20 && j == 3) || (i == 20 && j > 6 && j < 12) || (i == 20 && j == 13) || (i == 20 && j == 19) || (i == 20 && j == 21) || (i == 20 && j == 27) || (i == 20 && j == 35)
                || (i == 21 && j > 0 && j < 8) || (i == 21 && j == 11) || (i == 21 && j == 13) || (i == 21 && j > 14 && j < 20) || (i == 21 && j > 20 && j < 26) || (i == 21 && j == 27) || (i == 21 && j == 29) || (i == 21 && j == 31) || (i == 21 && j > 32 && j < 36) || (i == 21 && j > 36 && j < 39)
                || (i == 22 && j == 2) || (i == 22 && j == 9) || (i == 22 && j == 11) || (i == 22 && j == 13) || (i == 22 && j == 15) || (i == 22 && j == 21) || (i == 22 && j == 23) || (i == 22 && j == 27) || (i == 22 && j == 29) || (i == 22 && j == 31) || (i == 22 && j == 35)
                || (i == 23 && j > 1 && j < 10) || (i == 23 && j > 10 && j < 14) || (i == 23 && j == 15) || (i == 23 && j == 17) || (i == 23 && j > 18 && j < 22) || (i == 23 && j > 22 && j < 26) || (i == 23 && j == 27) || (i == 23 && j > 28 && j < 38)
                || (i == 24 && j == 6) || (i == 24 && j == 11) || (i == 24 && j == 15) || (i == 24 && j == 17) || (i == 24 && j == 27) || (i == 24 && j == 29) || (i == 24 && j == 37)
                || (i == 25 && j == 2) || (i == 25 && j == 4) || (i == 25 && j == 6) || (i == 25 && j > 7 && j < 10) || (i == 25 && j > 12 && j < 16) || (i == 25 && j > 16 && j < 26) || (i == 25 && j > 26 && j < 30) || (i == 25 && j > 30 && j < 36) || (i == 25 && j == 37)
                || (i == 26 && j > 0 && j < 3) || (i == 26 && j == 4) || (i == 26 && j == 6) || (i == 26 && j == 8) || (i == 26 && j == 11) || (i == 26 && j == 15) || (i == 26 && j == 19) || (i == 26 && j == 25) || (i == 26 && j == 27) || (i == 26 && j == 33) || (i == 26 && j == 37)
                || (i == 27 && j > 3 && j < 7) || (i == 27 && j == 8) || (i == 27 && j > 9 && j < 14) || (i == 27 && j == 15) || (i == 27 && j > 16 && j < 20) || (i == 27 && j > 20 && j < 28) || (i == 27 && j > 28 && j < 34) || (i == 27 && j > 34 && j < 38)
                || (i == 28 && j > 0 && j < 3) || (i == 28 && j == 4) || (i == 28 && j == 8) || (i == 28 && j == 11) || (i == 28 && j == 15) || (i == 28 && j == 25) || (i == 28 && j == 29) || (i == 28 && j == 35)
                || (i == 29 && j > 3 && j < 9) || (i == 29 && j > 9 && j < 12) || (i == 29 && j > 12 && j < 16) || (i == 29 && j > 16 && j < 22) || (i == 29 && j > 22 && j < 26) || (i == 29 && j == 27) || (i == 29 && j == 29) || (i == 29 && j > 30 && j < 36) || (i == 29 && j > 36 && j < 39)
                || (i == 30 && j == 2) || (i == 30 && j == 6) || (i == 30 && j == 10) || (i == 30 && j == 13) || (i == 30 && j == 17) || (i == 30 && j == 21) || (i == 30 && j == 23) || (i == 30 && j == 25) || (i == 30 && j == 27) || (i == 30 && j == 29) || (i == 30 && j == 31) || (i == 30 && j == 33)
                || (i == 31 && j > 1 && j < 5) || (i == 31 && j == 6) || (i == 31 && j > 7 && j < 11) || (i == 31 && j > 11 && j < 16) || (i == 31 && j > 16 && j < 20) || (i == 31 && j == 21) || (i == 31 && j == 23) || (i == 31 && j > 24 && j < 28) || (i == 31 && j == 29) || (i == 31 && j == 31) || (i == 31 && j > 32 && j < 36) || (i == 31 && j == 37)
                || (i == 32 && j == 2) || (i == 32 && j == 6) || (i == 32 && j == 8) || (i == 32 && j == 13) || (i == 32 && j == 17) || (i == 32 && j == 19) || (i == 32 && j == 23) || (i == 32 && j == 27) || (i == 32 && j == 13) || (i == 32 && j == 29) || (i == 32 && j == 31) || (i == 32 && j == 37)
                || (i == 33 && j > 0 && j < 3) || (i == 33 && j > 3 && j < 11) || (i == 33 && j > 11 && j < 14) || (i == 33 && j > 14 && j < 18) || (i == 33 && j > 18 && j < 22) || (i == 33 && j > 22 && j < 26) || (i == 33 && j == 27) || (i == 33 && j > 28 && j < 38)
                || (i == 34 && j == 12) || (i == 34 && j == 17) || (i == 34 && j == 19) || (i == 34 && j == 29)
                || (i == 35 && j > 1 && j < 7) || (i == 35 && j == 8) || (i == 35 && j == 10) || (i == 35 && j == 12) || (i == 35 && j > 13 && j < 18) || (i == 35 && j == 19) || (i == 35 && j == 21) || (i == 35 && j > 22 && j < 26) || (i == 35 && j > 26 && j < 34) || (i == 35 && j == 35) || (i == 35 && j == 37)
                || (i == 36 && j == 2) || (i == 36 && j == 6) || (i == 36 && j == 8) || (i == 36 && j == 10) || (i == 36 && j == 12) || (i == 36 && j == 14) || (i == 36 && j == 21) || (i == 36 && j == 25) || (i == 36 && j == 33) || (i == 36 && j == 35) || (i == 36 && j == 37)
                || (i == 37 && j == 2) || (i == 37 && j == 4) || (i == 37 && j > 5 && j < 11) || (i == 37 && j == 12) || (i == 37 && j > 13 && j < 24) || (i == 37 && j > 24 && j < 28) || (i == 37 && j > 28 && j < 36) || (i == 37 && j > 36 && j < 39)
                || (i == 38 && j == 4) || (i == 38 && j == 10) || (i == 38 && j == 14) || (i == 38 && j == 27)) {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture1); // กำแพงสีดำ
            }
            if ((i == 22 && j == 2)) {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture1); // กำแพงสีดำ
            }

        }
    }
   
}
void Map2() {
    wallTexture2.loadFromFile("green.png");
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            displayRects[i + j * 40].setPosition(i * 25.f, j * 25.f);
            displayRects[i + j * 40].setSize(sf::Vector2f(25.f, 25.f));
            /*displayRects[i + j * 40].setOutlineThickness(1.f);*/
            displayRects[i + j * 40].setOutlineColor(sf::Color(0, 0, 0));

            if (
                (i == 0 || i == 39 || j == 0 || j == 39) && // ทุกขอบ
                !(j == 0 && i == 20) &&  // เว้นตรงกลางขอบบน
                !(j == 39 && i == 20) // เว้นตรงกลางขอบล่าง
                ) {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture2); // กำแพงสีดำ
            }
            if ((i == 1 && j == 8) || (i == 1 && j == 12) || (i == 1 && j == 17) || (i == 1 && j == 19) || (i == 1 && j == 27) || (i == 1 && j == 35)
                || (i == 2 && j > 1 && j < 9) || (i == 2 && j == 10) || (i == 2 && j > 11 && j < 14) || (i == 2 && j > 14 && j < 18) || (i == 2 && j == 19) || (i == 2 && j > 20 && j < 26) || (i == 2 && j == 27) || (i == 2 && j > 28 && j < 36) || (i == 2 && j > 36 && j < 39)
                || (i == 3 && j == 4) || (i == 3 && j == 8) || (i == 3 && j == 10) || (i == 3 && j == 12) || (i == 3 && j == 15) || (i == 3 && j == 17) || (i == 3 && j == 21) || (i == 3 && j == 25) || (i == 3 && j == 27) || (i == 3 && j == 31) || (i == 3 && j == 33)
                || (i == 4 && j > 0 && j < 3) || (i == 4 && j > 3 && j < 7) || (i == 4 && j > 7 && j < 11) || (i == 4 && j > 11 && j < 14) || (i == 4 && j == 15) || (i == 4 && j == 17) || (i == 4 && j == 19) || (i == 4 && j == 21) || (i == 4 && j > 22 && j < 30) || (i == 4 && j == 31) || (i == 4 && j == 33) || (i == 4 && j > 34 && j < 38)
                || (i == 5 && j == 4) || (i == 5 && j == 6) || (i == 5 && j == 8) || (i == 5 && j == 12) || (i == 5 && j == 17) || (i == 5 && j == 19) || (i == 5 && j == 29) || (i == 5 && j == 31) || (i == 5 && j == 35)
                || (i == 6 && j > 1 && j < 5) || (i == 6 && j == 6) || (i == 6 && j == 8) || (i == 6 && j > 9 && j < 13) || (i == 6 && j == 15) || (i == 6 && j == 17) || (i == 6 && j > 18 && j < 26) || (i == 6 && j > 26 && j < 30) || (i == 6 && j > 30 && j < 34) || (i == 6 && j > 34 && j < 38)
                || (i == 7 && j == 8) || (i == 7 && j == 10) || (i == 7 && j == 15) || (i == 7 && j == 25) || (i == 7 && j == 31) || (i == 7 && j == 33) || (i == 7 && j == 35)
                || (i == 8 && j > 0 && j < 7) || (i == 8 && j == 10) || (i == 8 && j > 11 && j < 18) || (i == 8 && j == 19) || (i == 8 && j > 20 && j < 30) || (i == 8 && j == 31) || (i == 8 && j > 32 && j < 36) || (i == 8 && j > 36 && j < 39)
                || (i == 9 && j == 8) || (i == 9 && j == 15) || (i == 9 && j == 17) || (i == 9 && j == 19) || (i == 9 && j == 29) || (i == 9 && j == 33) || (i == 9 && j == 35)
                || (i == 10 && j > 1 && j < 11) || (i == 10 && j > 11 && j < 16) || (i == 10 && j > 16 && j < 32) || (i == 10 && j == 33) || (i == 10 && j > 34 && j < 38)
                || (i == 11 && j == 5) || (i == 11 && j == 7) || (i == 11 && j == 21) || (i == 11 && j == 29) || (i == 11 && j == 31) || (i == 11 && j == 33)
                || (i == 12 && j > 0 && j < 3) || (i == 12 && j > 3 && j < 6) || (i == 12 && j > 6 && j < 18) || (i == 12 && j > 18 && j < 28) || (i == 12 && j == 29) || (i == 12 && j > 30 && j < 38)
                || (i == 13 && j == 11) || (i == 13 && j == 19) || (i == 13 && j == 23) || (i == 13 && j == 27) || (i == 13 && j == 29) || (i == 13 && j == 33) || (i == 13 && j == 35) || (i == 13 && j == 37)
                || (i == 14 && j > 1 && j < 5) || (i == 14 && j > 5 && j < 12) || (i == 14 && j > 12 && j < 18) || (i == 14 && j == 19) || (i == 14 && j == 21) || (i == 14 && j == 23) || (i == 14 && j == 25) || (i == 14 && j == 29) || (i == 14 && j == 31) || (i == 14 && j == 33) || (i == 14 && j == 35) || (i == 14 && j == 37)
                || (i == 15 && j == 2) || (i == 15 && j == 9) || (i == 15 && j == 13) || (i == 15 && j == 15) || (i == 15 && j == 17) || (i == 15 && j > 18 && j < 22) || (i == 15 && j == 25) || (i == 15 && j == 27) || (i == 15 && j == 29) || (i == 15 && j > 30 && j < 34) || (i == 15 && j == 37)
                || (i == 16 && j == 2) || (i == 16 && j > 3 && j < 10) || (i == 16 && j > 10 && j < 14) || (i == 16 && j == 15) || (i == 16 && j == 17) || (i == 16 && j == 19) || (i == 16 && j == 23) || (i == 16 && j == 25) || (i == 16 && j == 27) || (i == 16 && j > 34 && j < 38)
                || (i == 17 && j > 0 && j < 3) || (i == 17 && j == 6) || (i == 17 && j == 13) || (i == 17 && j == 15) || (i == 17 && j == 17) || (i == 17 && j == 19) || (i == 17 && j > 20 && j < 24) || (i == 17 && j == 25) || (i == 17 && j > 26 && j < 36)
                || (i == 18 && j > 3 && j < 7) || (i == 18 && j == 8) || (i == 18 && j > 9 && j < 12) || (i == 18 && j == 13) || (i == 18 && j == 15) || (i == 18 && j == 19) || (i == 18 && j == 21) || (i == 18 && j == 23) || (i == 18 && j == 25) || (i == 18 && j == 37)
                || (i == 19 && j > 1 && j < 5) || (i == 19 && j == 8) || (i == 19 && j == 10) || (i == 19 && j == 13) || (i == 19 && j > 14 && j < 18) || (i == 19 && j == 19) || (i == 19 && j == 21) || (i == 19 && j > 22 && j < 30) || (i == 19 && j > 30 && j < 36) || (i == 19 && j > 36 && j < 39)
                || (i == 20 && j == 3) || (i == 20 && j > 6 && j < 12) || (i == 20 && j == 13) || (i == 20 && j == 19) || (i == 20 && j == 21) || (i == 20 && j == 27) || (i == 20 && j == 35)
                || (i == 21 && j > 0 && j < 8) || (i == 21 && j == 11) || (i == 21 && j == 13) || (i == 21 && j > 14 && j < 20) || (i == 21 && j > 20 && j < 26) || (i == 21 && j == 27) || (i == 21 && j == 29) || (i == 21 && j == 31) || (i == 21 && j > 32 && j < 36) || (i == 21 && j > 36 && j < 39)
                || (i == 22 && j == 2) || (i == 22 && j == 9) || (i == 22 && j == 11) || (i == 22 && j == 13) || (i == 22 && j == 15) || (i == 22 && j == 21) || (i == 22 && j == 23) || (i == 22 && j == 27) || (i == 22 && j == 29) || (i == 22 && j == 31) || (i == 22 && j == 35)
                || (i == 23 && j > 1 && j < 10) || (i == 23 && j > 10 && j < 14) || (i == 23 && j == 15) || (i == 23 && j == 17) || (i == 23 && j > 18 && j < 22) || (i == 23 && j > 22 && j < 26) || (i == 23 && j == 27) || (i == 23 && j > 28 && j < 38)
                || (i == 24 && j == 6) || (i == 24 && j == 11) || (i == 24 && j == 15) || (i == 24 && j == 17) || (i == 24 && j == 27) || (i == 24 && j == 29) || (i == 24 && j == 37)
                || (i == 25 && j == 2) || (i == 25 && j == 4) || (i == 25 && j == 6) || (i == 25 && j > 7 && j < 10) || (i == 25 && j > 12 && j < 16) || (i == 25 && j > 16 && j < 26) || (i == 25 && j > 26 && j < 30) || (i == 25 && j > 30 && j < 36) || (i == 25 && j == 37)
                || (i == 26 && j > 0 && j < 3) || (i == 26 && j == 4) || (i == 26 && j == 6) || (i == 26 && j == 8) || (i == 26 && j == 11) || (i == 26 && j == 15) || (i == 26 && j == 19) || (i == 26 && j == 25) || (i == 26 && j == 27) || (i == 26 && j == 33) || (i == 26 && j == 37)
                || (i == 27 && j > 3 && j < 7) || (i == 27 && j == 8) || (i == 27 && j > 9 && j < 14) || (i == 27 && j == 15) || (i == 27 && j > 16 && j < 20) || (i == 27 && j > 20 && j < 28) || (i == 27 && j > 28 && j < 34) || (i == 27 && j > 34 && j < 38)
                || (i == 28 && j > 0 && j < 3) || (i == 28 && j == 4) || (i == 28 && j == 8) || (i == 28 && j == 11) || (i == 28 && j == 15) || (i == 28 && j == 25) || (i == 28 && j == 29) || (i == 28 && j == 35)
                || (i == 29 && j > 3 && j < 9) || (i == 29 && j > 9 && j < 12) || (i == 29 && j > 12 && j < 16) || (i == 29 && j > 16 && j < 22) || (i == 29 && j > 22 && j < 26) || (i == 29 && j == 27) || (i == 29 && j == 29) || (i == 29 && j > 30 && j < 36) || (i == 29 && j > 36 && j < 39)
                || (i == 30 && j == 2) || (i == 30 && j == 6) || (i == 30 && j == 10) || (i == 30 && j == 13) || (i == 30 && j == 17) || (i == 30 && j == 21) || (i == 30 && j == 23) || (i == 30 && j == 25) || (i == 30 && j == 27) || (i == 30 && j == 29) || (i == 30 && j == 31) || (i == 30 && j == 33)
                || (i == 31 && j > 1 && j < 5) || (i == 31 && j == 6) || (i == 31 && j > 7 && j < 11) || (i == 31 && j > 11 && j < 16) || (i == 31 && j > 16 && j < 20) || (i == 31 && j == 21) || (i == 31 && j == 23) || (i == 31 && j > 24 && j < 28) || (i == 31 && j == 29) || (i == 31 && j == 31) || (i == 31 && j > 32 && j < 36) || (i == 31 && j == 37)
                || (i == 32 && j == 2) || (i == 32 && j == 6) || (i == 32 && j == 8) || (i == 32 && j == 13) || (i == 32 && j == 17) || (i == 32 && j == 19) || (i == 32 && j == 23) || (i == 32 && j == 27) || (i == 32 && j == 13) || (i == 32 && j == 29) || (i == 32 && j == 31) || (i == 32 && j == 37)
                || (i == 33 && j > 0 && j < 3) || (i == 33 && j > 3 && j < 11) || (i == 33 && j > 11 && j < 14) || (i == 33 && j > 14 && j < 18) || (i == 33 && j > 18 && j < 22) || (i == 33 && j > 22 && j < 26) || (i == 33 && j == 27) || (i == 33 && j > 28 && j < 38)
                || (i == 34 && j == 12) || (i == 34 && j == 17) || (i == 34 && j == 19) || (i == 34 && j == 29)
                || (i == 35 && j > 1 && j < 7) || (i == 35 && j == 8) || (i == 35 && j == 10) || (i == 35 && j == 12) || (i == 35 && j > 13 && j < 18) || (i == 35 && j == 19) || (i == 35 && j == 21) || (i == 35 && j > 22 && j < 26) || (i == 35 && j > 26 && j < 34) || (i == 35 && j == 35) || (i == 35 && j == 37)
                || (i == 36 && j == 2) || (i == 36 && j == 6) || (i == 36 && j == 8) || (i == 36 && j == 10) || (i == 36 && j == 12) || (i == 36 && j == 14) || (i == 36 && j == 21) || (i == 36 && j == 25) || (i == 36 && j == 33) || (i == 36 && j == 35) || (i == 36 && j == 37)
                || (i == 37 && j == 2) || (i == 37 && j == 4) || (i == 37 && j > 5 && j < 11) || (i == 37 && j == 12) || (i == 37 && j > 13 && j < 24) || (i == 37 && j > 24 && j < 28) || (i == 37 && j > 28 && j < 36) || (i == 37 && j > 36 && j < 39)
                || (i == 38 && j == 4) || (i == 38 && j == 10) || (i == 38 && j == 14) || (i == 38 && j == 27)) {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture2); // กำแพงสีดำ
            }
            if ((i == 22 && j == 2)) {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture2); // กำแพงสีดำ
            }

        }
    }
}


   
