#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

int gameMap[40 * 40];
int loading_Ar[3 * 25];
void Map1();
void Map2();
void Map3();
void Map4();
void wait(double);
void PuzzleMain();
void Menu();
void resetMap();
using namespace sf;
using namespace std;
RenderWindow window(VideoMode(1000, 1000), "Mazegame");
RectangleShape displayRects[40 * 40];
RectangleShape loading[3 * 25];
Texture wallTexture1;
Texture wallTexture2;
Texture wallTexture3;
Texture wallTexture4;
Texture playerTex;
Font font;

SoundBuffer buttonBuffer, footstepBuffer,finishBuffer;
Sound buttonSound, footstepSound ,finishSound;

int Mode = 0;
bool ST = true;

// โครงสร้างเก็บข้อมูลโจทย์และคำตอบ
struct Puzzle {
    string question;
    string answer;
};


// ฟังก์ชันสุ่มโจทย์คณิตศาสตร์ (เพิ่มความหลากหลายของโจทย์)
Puzzle getRandomMathPuzzle() {
    int a = rand() % 30 + 1;
    int b = rand() % 30 + 1;
    int operation = rand() % 4;
    std::string question;
    int answer;

    switch (operation) {
    case 0: question = "What is " + std::to_string(a) + " + " + std::to_string(b) + "?"; answer = a + b; break;
    case 1: question = "What is " + std::to_string(a) + " - " + std::to_string(b) + "?"; answer = a - b; break;
    case 2: question = "What is " + std::to_string(a) + " * " + std::to_string(b) + "?"; answer = a * b; break;
    case 3: question = "What is " + std::to_string(a * b) + " / " + std::to_string(b) + "?"; answer = a; break;
    }

    return { question, std::to_string(answer) };
}

// ฟังก์ชันสุ่มโจทย์โค้ดจากลิสต์ที่เตรียมไว้
Puzzle getRandomCodePuzzle(const std::vector<Puzzle>& puzzles) {
    int index = rand() % puzzles.size();
    return puzzles[index];
}

int main() {
    sf::Music bgMusic;
    if (!bgMusic.openFromFile("SoundBack.ogg")) {
        std::cerr << "Failed to load background music!" << std::endl;
        return -1; 
    }
    bgMusic.setLoop(true);
    bgMusic.setVolume(10);
    bgMusic.play();

    if (!footstepBuffer.loadFromFile("walksound.ogg")) {
        std::cerr << "Failed to load footstep sound!" << std::endl;
    }
    footstepSound.setBuffer(footstepBuffer);
    footstepSound.setVolume(50);

    if (!buttonBuffer.loadFromFile("Buttom.ogg")) {
        std::cerr << "Failed to load button sound!" << std::endl;
    }
    buttonSound.setBuffer(buttonBuffer);
    buttonSound.setVolume(70);

    if (!finishBuffer.loadFromFile("FinishSound.ogg")) {
        std::cerr << "Failed to load button sound!" << std::endl;
    }
    finishSound.setBuffer(finishBuffer);
    finishSound.setVolume(70);

    Menu();
    ST = false;
    Vector2i player = Vector2i(20, 38);
    playerTex.loadFromFile("smile.png");
    Sprite playerSprite;
    playerSprite.setTexture(playerTex);
    playerSprite.setScale(0.045f, 0.045f);
    playerSprite.setPosition(player.x * 25.f, player.y * 25.f);
    

    

    while (window.isOpen()&&!ST) {


        if (Mode == 0) {
            window.clear(sf::Color(0, 0, 0));
            if (!font.loadFromFile("ARIAL.ttf")) {
                return -1;
            }
            sf::Text text("Waitting..", font, 100);
            text.setFillColor(sf::Color::White);
            text.setPosition(250, 500);
            window.draw(text);
            window.display();
            wait(2);
            window.clear(sf::Color(0, 0, 0));
            Mode = 1;
        }
        if (Mode == 1) { resetMap();Map1(); }
        if (Mode == 2) { resetMap();Map2(); }
        if (Mode == 3) { resetMap();Map3(); }
        if (Mode == 4) { resetMap();Map4(); }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed) {

                sf::Vector2i newPosition = player;
                switch (event.key.code) {
                case sf::Keyboard::W: // Move up
                    if (footstepSound.getStatus() != sf::Sound::Playing) {
                        footstepSound.play();
                    }
                    if (player.y > 0) { newPosition.y -= 1; }
                    else newPosition.y -= 0;
                    break;
                case sf::Keyboard::S: // Move down
                    if (footstepSound.getStatus() != sf::Sound::Playing) {
                        footstepSound.play();
                    }
                    newPosition.y += 1;
                    break;
                case sf::Keyboard::D: // Move right
                    if (footstepSound.getStatus() != sf::Sound::Playing) {
                        footstepSound.play();
                    }
                    newPosition.x += 1;
                    break;
                case sf::Keyboard::A: // Move left
                    if (footstepSound.getStatus() != sf::Sound::Playing) {
                        footstepSound.play();
                    }
                    newPosition.x -= 1;
                    break;
                }


                if (gameMap[newPosition.x + newPosition.y * 40] != 1) {
                    player = newPosition;
                    std::cout << "Player position: (" << player.x << ", " << player.y << ")" << std::endl;
                }
            }

            playerSprite.setPosition(player.x * 25.f, player.y * 25.f);
        }
        window.clear(Color(0, 0, 0));

     //map1
        if (Mode == 1) {
           
            //(Y/X)

            if (player.x == 29 && player.y == 2) {
                PuzzleMain();
                player.x = 29;
                player.y = 3;
            }
            if (player.x == 20 && player.y == 8) {
                PuzzleMain();
                player.x = 19;
                player.y = 8;
            }
            if (player.x == 16 && player.y == 22) {
                PuzzleMain();
                player.x = 15;
                player.y = 22;
            }
            if (player.x == 34 && player.y == 20) {
                PuzzleMain();
                player.x = 34;
                player.y = 21;
            }
            if (player.x == 24 && player.y == 18) {
                PuzzleMain();
                player.x = 24;
                player.y = 19;
            }
            if (player.x == 34 && player.y == 28) {
                PuzzleMain();
                player.x = 34;
                player.y = 29;
            }
            if (player.x == 17 && player.y == 32) {
                PuzzleMain();
                player.x = 19;
                player.y = 8;
            }
            if (player.x == 20 && player.y == 37) {
                PuzzleMain();
                player.x = 20;
                player.y = 38;
            }

            if ((player.x == 20 && player.y == 39) and (Mode == 1))
            {

                finishSound.play();
                player.x = 20;
                player.y = 37;
                bgMusic.setVolume(0);
                window.clear(sf::Color(0, 0, 0));
                if (!font.loadFromFile("ARIAL.ttf")) {
                    return -1;
                }
                sf::Text text("Waitting..", font, 100);
                text.setFillColor(sf::Color::White);
                text.setPosition(250, 500);
                window.draw(text);
                window.display();
                wait(2);
                window.clear(sf::Color(0, 0, 0));
                Mode = 2;
                bgMusic.setVolume(12);
            }   //เส้นชัย map1
        }
     //map2
        if(Mode == 2) {
            
                if (player.x == 29 && player.y == 2) {
                    PuzzleMain();
                }
                if (player.x == 9 && player.y == 20) {
                    PuzzleMain();
                }
                if (player.x == 20 && player.y == 8) {
                    PuzzleMain();
                }
                if (player.x == 16 && player.y == 20) {
                    PuzzleMain();
                }
                if (player.x == 20 && player.y == 26) {
                    PuzzleMain();
                }
                if (player.x == 22 && player.y == 19) {
                    PuzzleMain();
                }
                if (player.x == 10 && player.y == 34) {
                    PuzzleMain();
                }
                if (player.x == 38 && player.y == 20) {
                    PuzzleMain();
                }
                if (player.x == 20 && player.y == 37) {
                    PuzzleMain();
                }
            

            if ((player.x == 20 && player.y == 39) and (Mode == 2))
            {
                finishSound.play();
                player.x = 20;
                player.y = 37;
                bgMusic.setVolume(0);
                window.clear(sf::Color(0, 0, 0));
                if (!font.loadFromFile("ARIAL.ttf")) {
                    return -1;
                }
                sf::Text text("Waitting..", font, 100);
                text.setFillColor(sf::Color::White);
                text.setPosition(250, 500);
                window.draw(text);
                window.display();
                wait(2);
                window.clear(sf::Color(0, 0, 0));
                Mode = 3;
                bgMusic.setVolume(12);
            }
        }
     //map3
        if (Mode == 3) {
            
                if (player.x == 29 && player.y == 5) {
                    PuzzleMain();
                }
                if (player.x == 28 && player.y == 2) {
                    PuzzleMain();
                }
                if (player.x == 20 && player.y == 10) {
                    PuzzleMain();
                }
                if (player.x == 16 && player.y == 22) {
                    PuzzleMain();
                }
                if (player.x == 35 && player.y == 20) {
                    PuzzleMain();
                }
                if (player.x == 17 && player.y == 34) {
                    PuzzleMain();
                }
                if (player.x == 20 && player.y == 37) {
                    PuzzleMain();
                }
                if (player.x == 9 && player.y == 20) {
                    PuzzleMain();
                }
                if (player.x == 20 && player.y == 8) {
                    PuzzleMain();
                }
                if (player.x == 16 && player.y == 20) {
                    PuzzleMain();
                }
                if (player.x == 20 && player.y == 26) {
                    PuzzleMain();
                }
                if (player.x == 22 && player.y == 19) {
                    PuzzleMain();
                }
                if (player.x == 10 && player.y == 34) {
                    PuzzleMain();
                }
                if (player.x == 38 && player.y == 19) {
                    PuzzleMain();
                }
                if (player.x == 20 && player.y == 37) {
                    PuzzleMain();
                }
            

            if ((player.x == 20 && player.y == 39) and (Mode == 3))
            {
                finishSound.play();
                player.x = 20;
                player.y = 37;
                bgMusic.setVolume(0);
                window.clear(sf::Color(0, 0, 0));
                if (!font.loadFromFile("ARIAL.ttf")) {
                    return -1;
                }
                sf::Text text("Waitting..", font, 100);
                text.setFillColor(sf::Color::White);
                text.setPosition(250, 500);
                window.draw(text);
                window.display();
                wait(2);
                window.clear(sf::Color(0, 0, 0));
                Mode = 4;
                bgMusic.setVolume(0);
            }   //เส้นชัย map1
        }
     //map4
        if (Mode == 4) {
            if (player.x == 29 && player.y == 5) {
                PuzzleMain();
            }
            if (player.x == 28 && player.y == 2) {
                PuzzleMain();
            }
            if (player.x == 22 && player.y == 10) {
                PuzzleMain();
            }
            if (player.x == 15 && player.y == 22) {
                PuzzleMain();
            }
            if (player.x == 34 && player.y == 20) {
                PuzzleMain();
            }
            if (player.x == 17 && player.y == 34) {
                PuzzleMain();
            }
            if (player.x == 20 && player.y == 37) {
                PuzzleMain();
            }
            if (player.x == 9 && player.y == 20) {
                PuzzleMain();
            }
            if (player.x == 20 && player.y == 6) {
                PuzzleMain();
            }
            if (player.x == 16 && player.y == 20) {
                PuzzleMain();
            }
            if (player.x == 20 && player.y == 26) {
                PuzzleMain();
            }
            if (player.x == 22 && player.y == 19) {
                PuzzleMain();
            }
            if (player.x == 10 && player.y == 34) {
                PuzzleMain();
            }
            if (player.x == 38 && player.y == 19) {
                PuzzleMain();
            }
            if ((player.x == 20 && player.y == 39) and (Mode == 4))
            {
                finishSound.play();
                player.x = 20;
                player.y = 37;
                bgMusic.setVolume(0);
                window.clear(sf::Color(0, 0, 0));
                if (!font.loadFromFile("ARIAL.ttf")) {
                    return -1;
                }
                sf::Text text("Waitting..", font, 100);
                text.setFillColor(sf::Color::White);
                text.setPosition(250, 500);
                window.draw(text);
                window.display();
                wait(2);
                window.clear(sf::Color(0, 0, 0));
                Mode = 4;
                bgMusic.setVolume(12);
            }   //เส้นชัย map1
        }
        
        for (int i = 0; i < 40 * 40; i++) {
            window.draw(displayRects[i]);
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }//ถ้ากด esc จะปิดโปรแกรม
        window.draw(playerSprite);

        window.display();
    }
    return 0;
}
void Map1() {
    wallTexture1.loadFromFile("brick.png");
    window.clear(sf::Color(0, 0, 0));
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            displayRects[i + j * 40].setPosition(i * 25.f, j * 25.f);
            displayRects[i + j * 40].setSize(sf::Vector2f(25.f, 25.f));
            displayRects[i + j * 40].setOutlineThickness(1.f);
            displayRects[i + j * 40].setOutlineColor(sf::Color::Black);


            if ((i == 1 && j == 13) || (i == 1 && j == 17) || (i == 1 && j == 21) || (i == 1 && j == 27) || (i == 1 && j == 31)
                || (i == 2 && j > 1 && j < 6) || (i == 2 && j > 6 && j < 14) || (i == 2 && j == 15) || (i == 2 && j > 16 && j < 20) || (i == 2 && j > 20 && j < 24) || (i == 2 && j > 24 && j < 28) || (i == 2 && j == 29) || (i == 2 && j == 31) || (i == 2 && j > 32 && j < 36) || (i == 2 && j == 37)
                || (i == 3 && j == 2) || (i == 3 && j == 7) || (i == 3 && j == 11) || (i == 3 && j == 15) || (i == 3 && j == 19) || (i == 3 && j == 27) || (i == 3 && j == 29) || (i == 3 && j == 31) || (i == 3 && j == 33) || (i == 3 && j == 35) || (i == 3 && j > 36 && j < 39)
                || (i == 4 && j == 2) || (i == 4 && j > 3 && j < 8) || (i == 4 && j == 9) || (i == 4 && j == 11) || (i == 4 && j == 13) || (i == 4 && j > 14 && j < 18) || (i == 4 && j > 18 && j < 24) || (i == 4 && j == 25) || (i == 4 && j == 27) || (i == 4 && j == 29) || (i == 4 && j == 33) || (i == 4 && j == 35)
                || (i == 5 && j == 2) || (i == 5 && j == 9) || (i == 9 && j == 9) || (i == 5 && j == 17) || (i == 5 && j == 19) || (i == 5 && j == 23) || (i == 5 && j == 25) || (i == 5 && j == 27) || (i == 5 && j > 28 && j < 34) || (i == 5 && j > 34 && j < 38)
                || (i == 6 && j > 0 && j < 5) || (i == 6 && j > 5 && j < 10) || (i == 6 && j == 11) || (i == 6 && j > 12 && j < 16) || (i == 6 && j == 17) || (i == 6 && j == 19) || (i == 6 && j == 21) || (i == 6 && j == 25) || (i == 6 && j == 27) || (i == 6 && j == 31) || (i == 6 && j == 37)
                || (i == 7 && j == 6) || (i == 7 && j == 11) || (i == 7 && j == 15) || (i == 7 && j == 17) || (i == 7 && j > 18 && j < 22) || (i == 7 && j > 22 && j < 26) || (i == 7 && j > 26 && j < 32) || (i == 7 && j > 32 && j < 36) || (i == 7 && j == 37)
                || (i == 8 && j > 1 && j < 7) || (i == 8 && j > 7 && j < 16) || (i == 8 && j == 17) || (i == 8 && j == 21) || (i == 8 && j == 23) || (i == 8 && j == 25) || (i == 8 && j == 35) || (i == 8 && j == 37)
                || (i == 9 && j == 4) || (i == 9 && j == 9) || (i == 9 && j == 11) || (i == 9 && j > 14 && j < 20) || (i == 9 && j == 21) || (i == 9 && j == 23) || (i == 9 && j > 24 && j < 34) || (i == 9 && j == 35) || (i == 9 && j == 37)
                || (i == 10 && j > 0 && j < 3) || (i == 10 && j > 3 && j < 8) || (i == 10 && j == 9) || (i == 10 && j == 13) || (i == 10 && j == 19) || (i == 10 && j == 21) || (i == 10 && j == 23) || (i == 10 && j == 27) || (i == 10 && j == 33) || (i == 10 && j == 35)
                || (i == 11 && j == 2) || (i == 11 && j == 4) || (i == 11 && j == 9) || (i == 11 && j > 10 && j < 20) || (i == 11 && j == 21) || (i == 11 && j > 22 && j < 26) || (i == 11 && j == 27) || (i == 11 && j > 28 && j < 32) || (i == 11 && j == 33) || (i == 11 && j == 35) || (i == 11 && j > 36 && j < 39)
                || (i == 12 && j == 2) || (i == 12 && j == 4) || (i == 12 && j == 11) || (i == 12 && j > 5 && j < 10) || (i == 12 && j == 21) || (i == 12 && j == 15) || (i == 12 && j == 19) || (i == 12 && j == 21) || (i == 12 && j == 25) || (i == 12 && j == 27) || (i == 12 && j == 29) || (i == 12 && j == 31) || (i == 12 && j == 35)
                || (i == 13 && j == 4) || (i == 13 && j == 9) || (i == 13 && j == 11) || (i == 13 && j == 13) || (i == 13 && j == 15) || (i == 13 && j == 17) || (i == 13 && j == 19) || (i == 13 && j == 21) || (i == 13 && j > 22 && j < 26) || (i == 13 && j == 27) || (i == 13 && j == 29) || (i == 13 && j > 30 && j < 38)
                || (i == 14 && j > 1 && j < 10) || (i == 14 && j == 11) || (i == 14 && j == 13) || (i == 14 && j == 15) || (i == 14 && j == 17) || (i == 14 && j == 21) || (i == 14 && j == 27) || (i == 14 && j == 29) || (i == 14 && j == 37)
                || (i == 15 && j == 2) || (i == 15 && j == 4) || (i == 15 && j > 8 && j < 12) || (i == 15 && j > 12 && j < 16) || (i == 15 && j > 16 && j < 22) || (i == 15 && j > 22 && j < 26) || (i == 15 && j == 27) || (i == 15 && j > 28 && j < 36) || (i == 15 && j == 37)
                || (i == 16 && j == 2) || (i == 16 && j == 7) || (i == 16 && j == 11) || (i == 16 && j == 23) || (i == 16 && j == 27) || (i == 16 && j == 33)
                || (i == 17 && j > 1 && j < 8) || (i == 17 && j == 9) || (i == 17 && j > 10 && j < 16) || (i == 17 && j > 16 && j < 28) || (i == 17 && j > 28 && j < 32) || (i == 17 && j == 33) || (i == 17 && j > 34 && j < 39)
                || (i == 18 && j == 9) || (i == 18 && j == 13) || (i == 18 && j == 19) || (i == 18 && j == 21) || (i == 18 && j == 25) || (i == 18 && j == 29) || (i == 18 && j == 33)
                || (i == 19 && j > 0 && j < 8) || (i == 19 && j > 8 && j < 18) || (i == 19 && j == 19) || (i == 19 && j == 21) || (i == 19 && j == 23) || (i == 19 && j == 25) || (i == 19 && j > 26 && j < 30) || (i == 19 && j > 30 && j < 34) || (i == 19 && j > 34 && j < 39)
                || (i == 20 && j == 4) || (i == 20 && j == 9) || (i == 20 && j == 17) || (i == 20 && j == 19) || (i == 20 && j == 23) || (i == 20 && j == 25) || (i == 20 && j == 27) || (i == 20 && j == 33) || (i == 20 && j == 35)
                || (i == 21 && j == 2) || (i == 21 && j == 4) || (i == 21 && j > 5 && j < 10) || (i == 21 && j > 10 && j < 14) || (i == 21 && j > 14 && j < 24) || (i == 21 && j == 25) || (i == 21 && j > 26 && j < 32) || (i == 21 && j > 32 && j < 36) || (i == 21 && j > 36 && j < 39)
                || (i == 22 && j == 2) || (i == 22 && j == 4) || (i == 22 && j == 6) || (i == 22 && j == 13) || (i == 22 && j == 25) || (i == 22 && j == 27) || (i == 22 && j == 31) || (i == 22 && j == 33) || (i == 22 && j == 37)
                || (i == 23 && j == 2) || (i == 23 && j == 6) || (i == 23 && j > 7 && j < 10) || (i == 23 && j == 11) || (i == 23 && j == 13) || (i == 23 && j > 14 && j < 26) || (i == 23 && j == 27) || (i == 23 && j == 29) || (i == 23 && j == 31) || (i == 23 && j == 33) || (i == 23 && j > 34 && j < 38)
                || (i == 24 && j > 1 && j < 5) || (i == 24 && j == 6) || (i == 24 && j == 9) || (i == 24 && j == 11) || (i == 24 && j == 13) || (i == 24 && j == 17) || (i == 24 && j == 23) || (i == 24 && j == 27) || (i == 24 && j == 29) || (i == 24 && j == 31) || (i == 24 && j == 33) || (i == 24 && j == 37)
                || (i == 25 && j == 2) || (i == 25 && j == 6) || (i == 25 && j == 9) || (i == 25 && j == 11) || (i == 25 && j > 12 && j < 16) || (i == 25 && j == 17) || (i == 25 && j > 18 && j < 22) || (i == 25 && j == 23) || (i == 25 && j > 24 && j < 28) || (i == 25 && j == 29) || (i == 25 && j == 31) || (i == 25 && j > 32 && j < 36) || (i == 25 && j == 37)
                || (i == 26 && j == 2) || (i == 26 && j > 3 && j < 10) || (i == 26 && j == 11) || (i == 26 && j == 13) || (i == 26 && j == 17) || (i == 26 && j == 19) || (i == 26 && j == 21) || (i == 26 && j == 23) || (i == 26 && j == 27) || (i == 26 && j == 29) || (i == 26 && j == 31) || (i == 26 && j == 35) || (i == 26 && j == 37)
                || (i == 27 && j == 2) || (i == 27 && j == 9) || (i == 27 && j == 11) || (i == 27 && j == 13) || (i == 27 && j > 14 && j < 18) || (i == 27 && j == 19) || (i == 27 && j == 21) || (i == 27 && j == 23) || (i == 27 && j == 25) || (i == 27 && j == 27) || (i == 27 && j > 28 && j < 34) || (i == 27 && j == 35) || (i == 27 && j == 37)
                || (i == 28 && j > 1 && j < 8) || (i == 28 && j == 9) || (i == 28 && j == 11) || (i == 28 && j == 13) || (i == 28 && j == 15) || (i == 28 && j == 19) || (i == 28 && j == 23) || (i == 28 && j == 25) || (i == 28 && j == 27) || (i == 28 && j == 35)
                || (i == 29 && j == 4) || (i == 29 && j == 7) || (i == 29 && j > 8 && j < 12) || (i == 29 && j > 12 && j < 16) || (i == 29 && j > 16 && j < 20) || (i == 29 && j > 20 && j < 24) || (i == 29 && j == 25) || (i == 29 && j > 26 && j < 38)
                || (i == 30 && j > 0 && j < 3) || (i == 30 && j == 4) || (i == 30 && j == 9) || (i == 30 && j == 13) || (i == 30 && j == 15) || (i == 30 && j == 17) || (i == 30 && j == 21) || (i == 30 && j == 25) || (i == 30 && j == 29)
                || (i == 31 && j > 3 && j < 8) || (i == 31 && j > 8 && j < 12) || (i == 31 && j == 13) || (i == 31 && j == 17) || (i == 31 && j > 18 && j < 24) || (i == 31 && j > 24 && j < 28) || (i == 31 && j == 29) || (i == 31 && j > 30 && j < 39)
                || (i == 32 && j == 2) || (i == 32 && j == 7) || (i == 32 && j == 9) || (i == 32 && j == 13) || (i == 32 && j == 17) || (i == 32 && j == 25) || (i == 32 && j == 29) || (i == 32 && j == 31)
                || (i == 33 && j > 1 && j < 6) || (i == 33 && j == 7) || (i == 33 && j == 9) || (i == 33 && j > 10 && j < 16) || (i == 33 && j > 16 && j < 30) || (i == 33 && j > 30 && j < 34) || (i == 33 && j > 34 && j < 38)
                || (i == 34 && j == 5) || (i == 34 && j == 7) || (i == 34 && j == 9) || (i == 34 && j == 15) || (i == 34 && j == 17) || (i == 34 && j == 31) || (i == 34 && j == 35)
                || (i == 35 && j > 0 && j < 3) || (i == 35 && j > 3 && j < 6) || (i == 35 && j == 7) || (i == 35 && j > 8 && j < 14) || (i == 35 && j == 15) || (i == 35 && j == 17) || (i == 35 && j > 18 && j < 32) || (i == 35 && j > 32 && j < 39)
                || (i == 36 && j == 4) || (i == 36 && j == 7) || (i == 36 && j == 9) || (i == 36 && j == 15) || (i == 36 && j == 19) || (i == 36 && j == 21) || (i == 36 && j == 29) || (i == 36 && j == 33)
                || (i == 37 && j == 2) || (i == 37 && j == 4) || (i == 37 && j > 5 && j < 8) || (i == 37 && j == 9) || (i == 37 && j > 10 && j < 20) || (i == 37 && j == 21) || (i == 37 && j > 22 && j < 26) || (i == 37 && j == 27) || (i == 37 && j == 29) || (i == 37 && j == 31) || (i == 37 && j == 33) || (i == 37 && j > 34 && j < 38)
                || (i == 38 && j == 2) || (i == 38 && j == 23) || (i == 38 && j == 27) || (i == 38 && j == 31) || (i == 38 && j == 35)
                )
            {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture1); // กำแพงสีดำ
            }
            else if ((i == 0 || i == 39 || j == 0 || j == 39) && !(j == 0 && i == 20) && !(j == 39 && i == 20))
            {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture1); // กำแพงสีดำ
            }
            else
            {
                displayRects[i + j * 40].setFillColor(Color::Black);
                displayRects[2 * 40 + 29].setFillColor(Color(25,51,0));
                displayRects[8 * 40 + 20].setFillColor(Color(255,51,51));
                displayRects[22 * 40 + 16].setFillColor(Color(153, 0, 76));
                displayRects[20 * 40 + 34].setFillColor(Color(51, 255, 51));
                displayRects[18 * 40 + 24].setFillColor(Color(102, 0, 102));
                displayRects[28 * 40 + 34].setFillColor(Color(0, 102, 102));
                displayRects[34 * 40 + 17].setFillColor(Color(127, 0, 255));
                displayRects[37 * 40 + 20].setFillColor(Color(153, 0, 0));

               
            }
            
   


        }
    }

}
void Map2() {
    window.clear(sf::Color(0, 0, 0));
    wallTexture2.loadFromFile("green.png");
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            displayRects[i + j * 40].setPosition(i * 25.f, j * 25.f);
            displayRects[i + j * 40].setSize(sf::Vector2f(25.f, 25.f));
            displayRects[i + j * 40].setOutlineThickness(1.f);
            displayRects[i + j * 40].setOutlineColor(sf::Color(0, 0, 0));


            if ((i == 1 && j == 13) || (i == 1 && j == 17) || (i == 1 && j == 21) || (i == 1 && j == 27) || (i == 1 && j == 31)
                || (i == 2 && j > 1 && j < 6) || (i == 2 && j > 6 && j < 14) || (i == 2 && j == 15) || (i == 2 && j > 16 && j < 20) || (i == 2 && j > 20 && j < 24) || (i == 2 && j > 24 && j < 28) || (i == 2 && j == 29) || (i == 2 && j == 31) || (i == 2 && j > 32 && j < 36) || (i == 2 && j == 37)
                || (i == 3 && j == 2) || (i == 3 && j == 7) || (i == 3 && j == 11) || (i == 3 && j == 15) || (i == 3 && j == 19) || (i == 3 && j == 27) || (i == 3 && j == 29) || (i == 3 && j == 31) || (i == 3 && j == 33) || (i == 3 && j == 35) || (i == 3 && j > 36 && j < 39)
                || (i == 4 && j == 2) || (i == 4 && j > 3 && j < 8) || (i == 4 && j == 9) || (i == 4 && j == 11) || (i == 4 && j == 13) || (i == 4 && j > 14 && j < 18) || (i == 4 && j > 18 && j < 24) || (i == 4 && j == 25) || (i == 4 && j == 27) || (i == 4 && j == 29) || (i == 4 && j == 33) || (i == 4 && j == 35)
                || (i == 5 && j == 2) || (i == 5 && j == 9) || (i == 9 && j == 9) || (i == 5 && j == 17) || (i == 5 && j == 19) || (i == 5 && j == 23) || (i == 5 && j == 25) || (i == 5 && j == 27) || (i == 5 && j > 28 && j < 34) || (i == 5 && j > 34 && j < 38)
                || (i == 6 && j > 0 && j < 5) || (i == 6 && j > 5 && j < 10) || (i == 6 && j == 11) || (i == 6 && j > 12 && j < 16) || (i == 6 && j == 17) || (i == 6 && j == 19) || (i == 6 && j == 21) || (i == 6 && j == 25) || (i == 6 && j == 27) || (i == 6 && j == 31) || (i == 6 && j == 37)
                || (i == 7 && j == 6) || (i == 7 && j == 11) || (i == 7 && j == 15) || (i == 7 && j == 17) || (i == 7 && j > 18 && j < 22) || (i == 7 && j > 22 && j < 26) || (i == 7 && j > 26 && j < 32) || (i == 7 && j > 32 && j < 36) || (i == 7 && j == 37)
                || (i == 8 && j > 1 && j < 7) || (i == 8 && j > 7 && j < 16) || (i == 8 && j == 17) || (i == 8 && j == 21) || (i == 8 && j == 23) || (i == 8 && j == 25) || (i == 8 && j == 35) || (i == 8 && j == 37)
                || (i == 9 && j == 4) || (i == 9 && j == 9) || (i == 9 && j == 11) || (i == 9 && j > 14 && j < 20) || (i == 9 && j == 21) || (i == 9 && j == 23) || (i == 9 && j > 24 && j < 34) || (i == 9 && j == 35) || (i == 9 && j == 37)
                || (i == 10 && j > 0 && j < 3) || (i == 10 && j > 3 && j < 8) || (i == 10 && j == 9) || (i == 10 && j == 13) || (i == 10 && j == 19) || (i == 10 && j == 21) || (i == 10 && j == 23) || (i == 10 && j == 27) || (i == 10 && j == 33) || (i == 10 && j == 35)
                || (i == 11 && j == 2) || (i == 11 && j == 4) || (i == 11 && j == 9) || (i == 11 && j > 10 && j < 20) || (i == 11 && j == 21) || (i == 11 && j > 22 && j < 26) || (i == 11 && j == 27) || (i == 11 && j > 28 && j < 32) || (i == 11 && j == 33) || (i == 11 && j == 35) || (i == 11 && j > 36 && j < 39)
                || (i == 12 && j == 2) || (i == 12 && j == 4) || (i == 12 && j == 11) || (i == 12 && j > 5 && j < 10) || (i == 12 && j == 21) || (i == 12 && j == 15) || (i == 12 && j == 19) || (i == 12 && j == 21) || (i == 12 && j == 25) || (i == 12 && j == 27) || (i == 12 && j == 29) || (i == 12 && j == 31) || (i == 12 && j == 35)
                || (i == 13 && j == 4) || (i == 13 && j == 9) || (i == 13 && j == 11) || (i == 13 && j == 13) || (i == 13 && j == 15) || (i == 13 && j == 17) || (i == 13 && j == 19) || (i == 13 && j == 21) || (i == 13 && j > 22 && j < 26) || (i == 13 && j == 27) || (i == 13 && j == 29) || (i == 13 && j > 30 && j < 38)
                || (i == 14 && j > 1 && j < 10) || (i == 14 && j == 11) || (i == 14 && j == 13) || (i == 14 && j == 15) || (i == 14 && j == 17) || (i == 14 && j == 21) || (i == 14 && j == 27) || (i == 14 && j == 29) || (i == 14 && j == 37)
                || (i == 15 && j == 2) || (i == 15 && j == 4) || (i == 15 && j > 8 && j < 12) || (i == 15 && j > 12 && j < 16) || (i == 15 && j > 16 && j < 22) || (i == 15 && j > 22 && j < 26) || (i == 15 && j == 27) || (i == 15 && j > 28 && j < 36) || (i == 15 && j == 37)
                || (i == 16 && j == 2) || (i == 16 && j == 7) || (i == 16 && j == 11) || (i == 16 && j == 23) || (i == 16 && j == 27) || (i == 16 && j == 33)
                || (i == 17 && j > 1 && j < 8) || (i == 17 && j == 9) || (i == 17 && j > 10 && j < 16) || (i == 17 && j > 16 && j < 28) || (i == 17 && j > 28 && j < 32) || (i == 17 && j == 33) || (i == 17 && j > 34 && j < 39)
                || (i == 18 && j == 9) || (i == 18 && j == 13) || (i == 18 && j == 19) || (i == 18 && j == 21) || (i == 18 && j == 25) || (i == 18 && j == 29) || (i == 18 && j == 33)
                || (i == 19 && j > 0 && j < 8) || (i == 19 && j > 8 && j < 18) || (i == 19 && j == 19) || (i == 19 && j == 21) || (i == 19 && j == 23) || (i == 19 && j == 25) || (i == 19 && j > 26 && j < 30) || (i == 19 && j > 30 && j < 34) || (i == 19 && j > 34 && j < 39)
                || (i == 20 && j == 4) || (i == 20 && j == 9) || (i == 20 && j == 17) || (i == 20 && j == 19) || (i == 20 && j == 23) || (i == 20 && j == 25) || (i == 20 && j == 27) || (i == 20 && j == 33) || (i == 20 && j == 35)
                || (i == 21 && j == 2) || (i == 21 && j == 4) || (i == 21 && j > 5 && j < 10) || (i == 21 && j > 10 && j < 14) || (i == 21 && j > 14 && j < 24) || (i == 21 && j == 25) || (i == 21 && j > 26 && j < 32) || (i == 21 && j > 32 && j < 36) || (i == 21 && j > 36 && j < 39)
                || (i == 22 && j == 2) || (i == 22 && j == 4) || (i == 22 && j == 6) || (i == 22 && j == 13) || (i == 22 && j == 25) || (i == 22 && j == 27) || (i == 22 && j == 31) || (i == 22 && j == 33) || (i == 22 && j == 37)
                || (i == 23 && j == 2) || (i == 23 && j == 6) || (i == 23 && j > 7 && j < 10) || (i == 23 && j == 11) || (i == 23 && j == 13) || (i == 23 && j > 14 && j < 26) || (i == 23 && j == 27) || (i == 23 && j == 29) || (i == 23 && j == 31) || (i == 23 && j == 33) || (i == 23 && j > 34 && j < 38)
                || (i == 24 && j > 1 && j < 5) || (i == 24 && j == 6) || (i == 24 && j == 9) || (i == 24 && j == 11) || (i == 24 && j == 13) || (i == 24 && j == 17) || (i == 24 && j == 23) || (i == 24 && j == 27) || (i == 24 && j == 29) || (i == 24 && j == 31) || (i == 24 && j == 33) || (i == 24 && j == 37)
                || (i == 25 && j == 2) || (i == 25 && j == 6) || (i == 25 && j == 9) || (i == 25 && j == 11) || (i == 25 && j > 12 && j < 16) || (i == 25 && j == 17) || (i == 25 && j > 18 && j < 22) || (i == 25 && j == 23) || (i == 25 && j > 24 && j < 28) || (i == 25 && j == 29) || (i == 25 && j == 31) || (i == 25 && j > 32 && j < 36) || (i == 25 && j == 37)
                || (i == 26 && j == 2) || (i == 26 && j > 3 && j < 10) || (i == 26 && j == 11) || (i == 26 && j == 13) || (i == 26 && j == 17) || (i == 26 && j == 19) || (i == 26 && j == 21) || (i == 26 && j == 23) || (i == 26 && j == 27) || (i == 26 && j == 29) || (i == 26 && j == 31) || (i == 26 && j == 35) || (i == 26 && j == 37)
                || (i == 27 && j == 2) || (i == 27 && j == 9) || (i == 27 && j == 11) || (i == 27 && j == 13) || (i == 27 && j > 14 && j < 18) || (i == 27 && j == 19) || (i == 27 && j == 21) || (i == 27 && j == 23) || (i == 27 && j == 25) || (i == 27 && j == 27) || (i == 27 && j > 28 && j < 34) || (i == 27 && j == 35) || (i == 27 && j == 37)
                || (i == 28 && j > 1 && j < 8) || (i == 28 && j == 9) || (i == 28 && j == 11) || (i == 28 && j == 13) || (i == 28 && j == 15) || (i == 28 && j == 19) || (i == 28 && j == 23) || (i == 28 && j == 25) || (i == 28 && j == 27) || (i == 28 && j == 35)
                || (i == 29 && j == 4) || (i == 29 && j == 7) || (i == 29 && j > 8 && j < 12) || (i == 29 && j > 12 && j < 16) || (i == 29 && j > 16 && j < 20) || (i == 29 && j > 20 && j < 24) || (i == 29 && j == 25) || (i == 29 && j > 26 && j < 38)
                || (i == 30 && j > 0 && j < 3) || (i == 30 && j == 4) || (i == 30 && j == 9) || (i == 30 && j == 13) || (i == 30 && j == 15) || (i == 30 && j == 17) || (i == 30 && j == 21) || (i == 30 && j == 25) || (i == 30 && j == 29)
                || (i == 31 && j > 3 && j < 8) || (i == 31 && j > 8 && j < 12) || (i == 31 && j == 13) || (i == 31 && j == 17) || (i == 31 && j > 18 && j < 24) || (i == 31 && j > 24 && j < 28) || (i == 31 && j == 29) || (i == 31 && j > 30 && j < 39)
                || (i == 32 && j == 2) || (i == 32 && j == 7) || (i == 32 && j == 9) || (i == 32 && j == 13) || (i == 32 && j == 17) || (i == 32 && j == 25) || (i == 32 && j == 29) || (i == 32 && j == 31)
                || (i == 33 && j > 1 && j < 6) || (i == 33 && j == 7) || (i == 33 && j == 9) || (i == 33 && j > 10 && j < 16) || (i == 33 && j > 16 && j < 30) || (i == 33 && j > 30 && j < 34) || (i == 33 && j > 34 && j < 38)
                || (i == 34 && j == 5) || (i == 34 && j == 7) || (i == 34 && j == 9) || (i == 34 && j == 15) || (i == 34 && j == 17) || (i == 34 && j == 31) || (i == 34 && j == 35)
                || (i == 35 && j > 0 && j < 3) || (i == 35 && j > 3 && j < 6) || (i == 35 && j == 7) || (i == 35 && j > 8 && j < 14) || (i == 35 && j == 15) || (i == 35 && j == 17) || (i == 35 && j > 18 && j < 32) || (i == 35 && j > 32 && j < 39)
                || (i == 36 && j == 4) || (i == 36 && j == 7) || (i == 36 && j == 9) || (i == 36 && j == 15) || (i == 36 && j == 19) || (i == 36 && j == 21) || (i == 36 && j == 29) || (i == 36 && j == 33)
                || (i == 37 && j == 2) || (i == 37 && j == 4) || (i == 37 && j > 5 && j < 8) || (i == 37 && j == 9) || (i == 37 && j > 10 && j < 20) || (i == 37 && j == 21) || (i == 37 && j > 22 && j < 26) || (i == 37 && j == 27) || (i == 37 && j == 29) || (i == 37 && j == 31) || (i == 37 && j == 33) || (i == 37 && j > 34 && j < 38)
                || (i == 38 && j == 2) || (i == 38 && j == 23) || (i == 38 && j == 27) || (i == 38 && j == 31) || (i == 38 && j == 35))
            {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture2); // กำแพงสีดำ

            }
            else if ((i == 0 || i == 39 || j == 0 || j == 39) && !(j == 0 && i == 20) && !(j == 39 && i == 20))
            {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture2); // กำแพงสีดำ
            }
            else
            {
                displayRects[i + j * 40].setFillColor(Color::Black);

                             //(Y,X)
                displayRects[2 * 40 + 29].setFillColor(Color::Red);
                displayRects[20 * 40 + 9].setFillColor(Color(51, 0, 102));
                displayRects[8 * 40 + 20].setFillColor(Color(51,0,102));
                displayRects[20 * 40 + 16].setFillColor(Color(153, 0, 102));
                displayRects[26 * 40 + 20].setFillColor(Color(204, 204, 0));
                displayRects[19 * 40 + 22].setFillColor(Color(51, 0, 102));
                displayRects[34 * 40 + 10].setFillColor(Color(204, 204, 0));
                displayRects[20 * 40 + 38].setFillColor(Color(0, 153, 76));
                displayRects[37 * 40 + 20].setFillColor(Color(153, 0, 0));
            }

        }
    }
}
void Map3() {
    window.clear(sf::Color(255, 255, 255));
    wallTexture3.loadFromFile("ice.png");
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            displayRects[i + j * 40].setPosition(i * 25.f, j * 25.f);
            displayRects[i + j * 40].setSize(sf::Vector2f(25.f, 25.f));
            displayRects[i + j * 40].setOutlineThickness(1.f);
            displayRects[i + j * 40].setOutlineColor(sf::Color(255,255, 255));

            
            if ((i == 1 && (j == 2 || j == 6 || j == 10 || j == 14 || j == 23 || j == 27 || j == 31 || j == 35)) ||
                (i == 2 && (j == 2 || j == 4 || (j >= 6 && j <= 8) || j == 10 || j == 12 || j == 14 || j == 16 || (j >= 18 && j <= 23) || j == 25 || j == 27 || (j >= 29 && j <= 31) || (j >= 33 && j <= 35) || j == 37)) ||
                (i == 3 && (j == 2 || j == 4 || j == 8 || j == 12 || j == 14 || j == 16 || j == 25 || j == 27 || j == 31 || j == 37)) ||
                (i == 4 && (j == 2 || (j >= 4 && j <= 6) || j == 8 || (j >= 10 && j <= 14) || (j >= 16 && j <= 25) || j == 27 || j == 29 || (j >= 31 && j <= 37))) ||
                (i == 5 && (j == 2 || j == 6 || j == 8 || j == 16 || j == 19 || j == 23 || j == 29 || j == 37)) ||
                (i == 6 && (j == 2 || j == 4 || j == 6 || (j >= 8 && j <= 17) || j == 19 || (j >= 21 && j <= 23) || (j >= 25 && j <= 37))) ||
                (i == 7 && (j == 2 || j == 4 || j == 6 || j == 17 || j == 19 || j == 23 || j == 29 || j == 35)) ||
                (i == 8 && (j == 2 || j == 4 || (j >= 6 && j <= 11) || (j >= 13 && j <= 15) || j == 17 || (j >= 19 && j <= 21) || (j >= 23 && j <= 25) || j == 27 || j == 29 || j == 33 || j == 35 || (j >= 37 && j <= 38))) ||
                (i == 9 && (j == 4 || j == 7 || j == 11 || j == 13 || j == 21 || j == 23 || j == 27 || (j >= 31 && j <= 35))) ||
                (i == 10 && ((j >= 1 && j <= 5) || j == 7 || (j >= 9 && j <= 11) || j == 13 || j == 15 || (j >= 17 && j <= 19) || j == 21 || (j >= 23 && j <= 29) || j == 31 || (j >= 35 && j <= 37))) ||
                (i == 11 && (j == 7 || j == 9 || j == 13 || (j >= 15 && j <= 17) || j == 21 || j == 27 || j == 29 || j == 31 || j == 33 || j == 37)) ||
                (i == 12 && ((j >= 1 && j <= 3) || j == 5 || j == 7 || j == 9 || (j >= 11 && j <= 13) || j == 19 || j == 23 || j == 25 || j == 31 || j == 33 || j == 35)) ||
                (i == 13 && ((j >= 5 && j <= 7) || j == 9 || j == 11 || j == 13 || (j >= 17 && j <= 27) || j == 29 || j == 31 || j == 33 || (j >= 35 && j <= 37))) ||
                (i == 14 && (j == 2 || j == 6 || j == 9 || j == 11 || j == 13 || j == 15 || j == 19 || j == 29 || j == 31 || j == 33 || j == 37)) ||
                (i == 15 && ((j >= 2 && j <= 7) || j == 9 || j == 11 || j == 13 || (j >= 15 && j <= 17) || (j >= 19 && j <= 31) || j == 33 || (j >= 34 && j <= 35) || (j >= 37 && j <= 38))) ||
                (i == 16 && (j == 6 || j == 9 || j == 13 || j == 15 || j == 21 || j == 25 || j == 31 || j == 33 || j == 35)) ||
                (i == 17 && ((j >= 1 && j <= 4) || j == 6 || (j >= 8 && j <= 15) || j == 17 || j == 19 || j == 21 || j == 23 || j == 25 || (j >= 27 && j <= 29) || j == 31 || j == 33 || (j >= 35 && j <= 37))) ||
                (i == 18 && (j == 6 || j == 9 || j == 17 || j == 19 || j == 21 || j == 23 || j == 27 || j == 31 || j == 33 || j == 35)) ||
                (i == 19 && (j == 2 || j == 4 || (j >= 6 && j <= 7) || j == 9 || (j >= 11 && j <= 12) || (j >= 14 && j <= 17) || j == 19 || j == 21 || (j >= 23 && j <= 27) || (j >= 29 && j <= 31) || j == 33 || j == 35 || (j >= 37 && j <= 38))) ||
                (i == 20 && (j == 2 || j == 4 || j == 9 || j == 12 || j == 14 || j == 19 || j == 21 || j == 27 || j == 31 || j == 33 || j == 35)) ||
                (i == 21 && (j == 2 || (j >= 4 && j <= 6) || (j >= 8 && j <= 9) || (j >= 12 && j <= 14) || (j >= 16 && j <= 19) || (j >= 21 && j <= 25) || (j >= 27 && j <= 31) || j == 33 || (j >= 35 && j <= 38))) ||
                (i == 22 && (j == 2 || j == 6 || j == 9 || j == 11 || j == 12 || j == 16 || j == 23 || j == 25 || j == 29 || j == 35)) ||
                (i == 23 && ((j >= 2 && j <= 6) || j == 9 || j == 12 || (j >= 14 && j <= 21) || j == 23 || (j >= 25 && j <= 27) || j == 29 || (j >= 31 && j <= 37))) ||
                (i == 24 && (j == 6 || (j >= 8 && j <= 10) || j == 12 || j == 14 || j == 19 || j == 21 || j == 23 || j == 25 || j == 29 || j == 35)) ||
                (i == 25 && ((j >= 1 && j <= 4) || j == 6 || j == 8 || j == 12 || j == 14 || j == 16 || j == 17 || j == 19 || j == 21 || j == 23 || j == 25 || (j >= 27 && j <= 29) || (j >= 31 && j <= 33) || j == 35 || (j >= 37 && j <= 38))) ||
                (i == 26 && (j == 6 || j == 8 || (j >= 10 && j <= 12) || j == 14 || j == 17 || j == 21 || j == 23 || j == 25 || j == 31 || j == 35)) ||
                (i == 27 && ((j >= 1 && j <= 4) || (j >= 6 && j <= 8) || j == 10 || j == 12 || j == 14 || (j >= 16 && j <= 19) || j == 21 || j == 23 || j == 25 || (j >= 27 && j <= 31) || (j >= 33 && j <= 37))) ||
                (i == 28 && (j == 4 || j == 6 || j == 10 || j == 12 || j == 17 || j == 21 || j == 27)) ||
                (i == 29 && ((j >= 2 && j <= 4) || j == 6 || (j >= 8 && j <= 10) || (j >= 12 && j <= 15) || (j >= 17 && j <= 19) || (j >= 21 && j <= 23) || j == 25 || j == 27 || (j >= 29 && j <= 31) || j >= 33 && j <= 38)) ||
                (i == 30 && (j == 2 || j == 6 || j == 12 || j == 15 || j == 17 || j == 21 || j == 25 || j == 29 || j == 31 || j == 37)) ||
                (i == 31 && (j == 2 || (j >= 4 && j <= 10) || j == 12 || j == 17 || (j >= 19 && j <= 21) || (j >= 23 && j <= 29) || (j >= 31 && j <= 35) || j == 37)) ||
                (i == 32 && (j == 4 || j == 10 || j == 12 || j == 14 || j == 17 || j == 19 || j == 21 || j == 25 || j == 31 || j == 33 || j == 37)) ||
                (i == 33 && ((j >= 1 && j <= 4) || (j >= 6 && j <= 10) || j == 12 || (j >= 14 && j <= 17) || j == 19 || j == 21 || (j >= 23 && j <= 25) || (j >= 27 && j <= 29) || j == 31 || j == 33 || (j >= 35 && j <= 37))) ||
                (i == 34 && (j == 6 || j == 12 || j == 16 || j == 19 || j == 21 || j == 27 || j == 29 || j == 31 || j == 37)) ||
                (i == 35 && ((j >= 2 && j <= 4) || j == 6 || (j >= 8 && j <= 14) || j == 16 || (j >= 18 && j <= 19) || (j >= 21 && j <= 27) || j == 29 || (j >= 31 && j <= 35) || j == 37)) ||
                (i == 36 && (j == 4 || j == 8 || j == 12 || j == 16 || j == 18 || j == 23 || j == 27 || j == 29 || j == 33 || j == 35)) ||
                (i == 37 && (j >= 1 && j <= 2 || j == 4 || (j >= 6 && j <= 10) || j == 12 || (j >= 14 && j <= 16) || j == 18 || (j >= 20 && j <= 21) || j == 23 || j == 25 || j == 27 || (j >= 29 && j <= 31) || j == 33 || (j >= 35 && j <= 38))) ||
                (i == 38 && (j == 4 || j == 12 || j == 16 || j == 20 || j == 25 || j == 27)))
            {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture3); // กำแพงสีดำ
            }
            else if ((i == 0 || i == 39 || j == 0 || j == 39) && !(j == 0 && i == 20) && !(j == 39 && i == 20))
            {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture3); // กำแพงสีดำ
            }
            else
            {
                displayRects[i + j * 40].setFillColor(Color::White);
                //(Y,X)
                displayRects[5 * 40 + 29].setFillColor(Color::Red);
                displayRects[2 * 40 + 28].setFillColor(Color(0, 153,153));
                displayRects[10 * 40 + 20].setFillColor(Color(255, 51, 51));
                displayRects[22 * 40 + 16].setFillColor(Color(153, 0, 76));
                displayRects[20 * 40 + 35].setFillColor(Color(51, 255, 51));
                displayRects[34 * 40 + 17].setFillColor(Color(127, 0, 255));
                displayRects[37 * 40 + 20].setFillColor(Color(153, 0, 0));
                displayRects[20 * 40 + 9].setFillColor(Color(51, 0, 102));
                displayRects[8 * 40 + 20].setFillColor(Color(51, 0, 102));
                displayRects[20 * 40 + 16].setFillColor(Color(153, 0, 102));
                displayRects[26 * 40 + 20].setFillColor(Color(204, 204, 0));
                displayRects[19 * 40 + 22].setFillColor(Color(51, 0, 102));
                displayRects[34 * 40 + 10].setFillColor(Color(204, 204, 0));
                displayRects[19 * 40 + 38].setFillColor(Color(0, 153, 76));
                displayRects[37 * 40 + 20].setFillColor(Color(153, 0, 0));
            }
           


        }
    }
}

void Map4() {
    window.clear(sf::Color(0, 0, 0));
    wallTexture4.loadFromFile("lawa.png");
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            displayRects[i + j * 40].setPosition(i * 25.f, j * 25.f);
            displayRects[i + j * 40].setSize(sf::Vector2f(25.f, 25.f));
            displayRects[i + j * 40].setOutlineThickness(1.f);
            displayRects[i + j * 40].setOutlineColor(sf::Color(0, 0, 0));


            if ((i == 1 && (j == 4 || j == 10 || j == 17)) ||
                (i == 2 && ((j >= 2 && j <= 4) || (j >= 6 && j <= 8) || j == 10 || j == 12 || (j >= 14 && j <= 15) || j == 17 || (j >= 19 && j <= 25) || (j >= 27 && j <= 33) || (j >= 35 && j <= 37))) ||
                (i == 3 && (j == 6 || j == 8 || j == 12 || j == 14 || j == 17 || j == 21 || j == 27 || j == 33 || j == 37)) ||
                (i == 4 && ((j >= 2 && j <= 6) || (j >= 8 && j <= 12) || j == 14 || (j >= 16 && j <= 19) || j == 21 || (j >= 23 && j <= 31) || j == 33 || j == 35 || j == 37)) ||
                (i == 5 && ((j >= 12 && j <= 14) || j == 21 || j == 31 || (j >= 33 && j <= 35) || j == 37)) ||
                (i == 6 && (j == 2 || j == 3 || (j >= 5 && j <= 10) || j == 12 || (j >= 14 && j <= 17) || (j >= 19 && j <= 29) || j == 33 || j == 37)) ||
                (i == 7 && (j == 3 || j == 10 || j == 12 || j == 14 || j == 19 || j == 23 || j == 27 || (j >= 29 && j <= 33) || j == 35 || (j >= 37 && j <= 38))) ||
                (i == 8 && (j >= 1 && j <= 6 || j >= 9 && j <= 12 || j == 14 || (j >= 16 && j <= 21) || j == 25 || j == 27 || j == 31 || j == 35)) ||
                (i == 9 && (j == 2 || j == 6 || j == 8 || j == 9 || (j >= 23 && j <= 25) || (j >= 27 && j <= 29) || j == 31 || (j >= 33 && j <= 37))) ||
                (i == 10 && (j >= 9 && j <= 14 || (j >= 16 && j <= 23) || j == 31 || j == 37)) ||
                (i == 11 && ((j >= 2 && j <= 7) || j == 9 || j == 14 || j == 19 || j == 23 || (j >= 25 && j <= 35) || j == 37)) ||
                (i == 12 && (j == 4 || j == 6 || j == 9 || (j >= 11 && j <= 12) || (j >= 14 && j <= 17) || j == 19 || j == 21 || j == 23 || j == 31 || j == 33 || j == 37)) ||
                (i == 13 && ((j >= 1 && j <= 2) || j == 4 || (j >= 6 && j <= 9) || j == 12 || j == 17 || j == 21 || (j >= 23 && j <= 29) || j == 31 || j == 33 || (j >= 35 && j <= 37))) ||
                (i == 14 && (j == 4 || j == 9 || (j >= 11 && j <= 21) || j == 23 || j == 25 || j == 31 || j == 33 || j == 37)) ||
                (i == 15 && ((j >= 2 && j <= 7) || j == 11 || j == 17 || j == 23 || j == 25 || (j >= 27 && j <= 31) || (j >= 33 && j <= 35) || (j >= 37 && j <= 38))) ||
                (i == 16 && (j == 7 || (j >= 9 && j <= 11) || (j >= 13 && j <= 15) || j == 17 || j == 19 || (j >= 21 && j <= 23) || j == 25 || j == 29 || j == 33 || j == 35)) ||
                (i == 17 && ((j >= 1 && j <= 5) || j == 7 || j == 13 || j == 15 || j == 19 || j == 23 || (j >= 25 && j <= 27) || j == 29 || j == 31 || (j >= 35 && j <= 37))) ||
                (i == 18 && (j == 5 || (j >= 7 && j <= 11) || j == 13 || (j >= 15 && j <= 23) || j == 27 || j == 29 || (j >= 31 && j <= 35))) ||
                (i == 19 && ((j >= 2 && j <= 5) || j == 7 || j == 9 || j == 15 || j == 17 || (j >= 23 && j <= 25) || j == 27 || j == 29 || j == 31 || j == 35 || (j >= 37 && j <= 38))) ||
                (i == 20 && (j == 7 || j == 11 || (j >= 13 && j <= 15) || j == 17 || (j >= 19 && j <= 21) || j == 23 || j == 27 || j == 31 || j == 35 || j == 37)) ||
                (i == 21 && ((j >= 1 && j <= 11) || j == 13 || j == 17 || j == 21 || j == 23 || (j >= 25 && j <= 31) || j == 33 || j == 35 || j == 37)) ||
                (i == 22 && (j == 8 || j == 11 || j == 13 || j == 15 || (j >= 17 && j <= 19) || j == 21 || j == 23 || j == 33 || j == 35 || j == 37)) ||
                (i == 23 && ((j >= 2 && j <= 9) || j == 11 || j == 13 || j == 15 || j == 17 || j == 21 || j == 23 || (j >= 25 && j <= 33) || j == 35 || j == 37)) ||
                (i == 24 && (j == 2 || j == 13 || (j >= 15 && j <= 17) || (j >= 19 && j <= 21) || j == 23 || j == 27 || j == 33 || j == 35 || j == 37)) ||
                (i == 25 && (j == 2 || (j >= 4 && j <= 11) || j == 13 || j == 19 || j == 23 || (j >= 25 && j <= 27) || (j >= 29 && j <= 31) || j == 33 || j == 35 || j == 37)) ||
                (i == 26 && (j == 2 || j == 4 || j == 9 || j == 11 || (j >= 13 && j <= 19) || (j >= 21 && j <= 23) || j == 25 || j == 29 || j == 31 || j == 35)) ||
                (i == 27 && (j == 2 || j == 4 || (j >= 6 && j <= 7) || j == 9 || j == 13 || j == 19 || j == 21 || j == 25 || (j >= 27 && j <= 29) || (j >= 31 && j <= 35) || (j >= 37 && j <= 38))) ||
                (i == 28 && (j == 2 || j == 4 || j == 6 || j == 9 || (j >= 11 && j <= 13) || (j >= 15 && j <= 17) || j == 19 || (j >= 21 && j <= 23) || j == 25 || j == 29 || j == 33)) ||
                (i == 29 && ((j >= 2 && j <= 4) || j == 6 || (j >= 8 && j <= 9) || j == 11 || j == 15 || j == 21 || j == 25 || j == 27 || (j >= 29 && j <= 31) || j == 33 || j == 35 || (j >= 37 && j <= 38))) ||
                (i == 30 && (j == 4 || j == 6 || j == 9 || (j >= 11 && j <= 15) || (j >= 17 && j <= 21) || (j >= 23 && j <= 27) || j == 29 || j == 33 || j == 35)) ||
                (i == 31 && ((j >= 2 && j <= 4) || (j >= 6 && j <= 9) || j == 11 || j == 15 || j == 17 || j == 21 || j == 27 || j == 29 || (j >= 31 && j <= 33) || (j >= 35 && j <= 37))) ||
                (i == 32 && (j == 2 || j == 4 || j == 11 || j == 13 || j == 15 || j == 19 || (j >= 21 && j <= 25) || j == 27 || j == 31 || j == 35)) ||
                (i == 33 && ((j >= 4 && j <= 7) || j == 9 || j == 11 || j == 13 || (j >= 15 && j <= 19) || j == 21 || (j >= 27 && j <= 29) || j == 31 || (j >= 33 && j <= 35) || (j >= 37 && j <= 38))) ||
                (i == 34 && ((j >= 1 && j <= 2) || j == 4 || j == 9 || j == 11 || j == 13 || j == 17 || j == 21 || (j >= 23 && j <= 25) || j == 29 || j == 31 || j == 33)) ||
                (i == 35 && (j == 4 || (j >= 6 && j <= 9) || j == 11 || (j >= 13 && j <= 17) || (j >= 19 && j <= 21) || j == 25 || (j >= 27 && j <= 29) || j == 31 || (j >= 33 && j <= 37))) ||
                (i == 36 && (j == 2 || j == 4 || j == 9 || j == 11 || j == 17 || (j >= 21 && j <= 23) || j == 25 || j == 27 || j == 31 || j == 37)) ||
                (i == 37 && ((j >= 2 && j <= 7) || j == 9 || (j >= 11 && j <= 15) || (j >= 17 && j <= 19) || j == 21 || j == 23 || j == 25 || j == 27 || j == 29 || (j >= 31 && j <= 35) || j == 37)) ||
                (i == 38 && (j == 9 || j == 25 || j == 27 || j == 29 || j == 37))
                )
            {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture4); // กำแพงสีดำ
            }
            else if ((i == 0 || i == 39 || j == 0 || j == 39) && !(j == 0 && i == 20) && !(j == 39 && i == 20))
            {
                gameMap[i + j * 40] = 1;
                displayRects[i + j * 40].setTexture(&wallTexture4); // กำแพงสีดำ
            }
            else
            {
                //(y/x)
                displayRects[i + j * 40].setFillColor(Color::Black);
                displayRects[5 * 40 + 29].setFillColor(Color::Red);
                displayRects[2 * 40 + 28].setFillColor(Color(0, 153, 153));
                displayRects[10 * 40 + 22].setFillColor(Color(255, 51, 51));
                displayRects[22 * 40 + 15].setFillColor(Color(153, 0, 76));
                displayRects[20 * 40 + 34].setFillColor(Color(51, 255, 51));
                displayRects[34 * 40 + 17].setFillColor(Color(127, 0, 255));
                displayRects[37 * 40 + 20].setFillColor(Color(153, 0, 0));
                displayRects[20 * 40 + 9].setFillColor(Color(51, 0, 102));
                displayRects[6 * 40 + 20].setFillColor(Color(51, 0, 102));
                displayRects[20 * 40 + 16].setFillColor(Color(153, 0, 102));
                displayRects[26 * 40 + 20].setFillColor(Color(204, 204, 0));
                displayRects[19 * 40 + 22].setFillColor(Color(51, 0, 102));
                displayRects[34 * 40 + 10].setFillColor(Color(204, 204, 0));
                displayRects[19 * 40 + 38].setFillColor(Color(0, 153, 76));
                displayRects[37 * 40 + 20].setFillColor(Color(153, 0, 0));
            }



        }
    }
}
void wait(double seconds) {
    clock_t start_time = clock();
    while ((double)(clock() - start_time) / CLOCKS_PER_SEC < seconds);
}
void PuzzleMain() {
    window.clear(Color::White);
    bool Puz = true;
    window.clear(sf::Color(0, 0, 0));
    if (!font.loadFromFile("ARIAL.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }
    srand(static_cast<unsigned>(time(nullptr)));
    std::vector<Puzzle> codePuzzles = {
     {"What is the output?\n\nint a = 2;\nint b = 3;\nstd::cout << a + b;", "5"},
     {"What is the output?\n\nint x = 10;\nstd::cout << x * 2;", "20"},
     {"What is the output?\n\nfor(int i=0; i<3; i++) {\n    std::cout << i;\n}", "012"},
     {"What is the output?\n\nint sum = 0;\nfor(int i=1; i<=5; i++) {\n    sum += i;\n}\nstd::cout << sum;", "15"},
     {"What is the output?\n\nint a = 5;\nint b = 2;\nstd::cout << a / b;", "2"},
     {"What is the output?\n\nint a = 7;\nif(a % 2 == 0) {\n    std::cout << \"Even\";\n} else {\n    std::cout << \"Odd\";\n}", "Odd"},
     {"What is the output?\n\nstd::string s = \"Hello\";\nstd::cout << s.size();", "5"},
     {"What is the output?\n\nint factorial(int n) {\n    if(n <= 1) return 1;\n    return n * factorial(n - 1);\n}\nstd::cout << factorial(4);", "24"},
     {"What is the output?\n\nstd::vector<int> v = {10, 20, 30};\nfor(int x : v) {\n    std::cout << x << \" \";\n}", "10 20 30 "},
     {"What is the output?\n\nfor(int i = 1; i <= 3; i++) {\n    for(int j = 1; j <= 2; j++) {\n        std::cout << i + j << \" \";\n    }\n}", "2 3 3 4 4 5 "},
     {"What is the output?\n\nstd::string s = \"world\";\ns[0] = 'W';\nstd::cout << s;", "World"},
     {"What is the output?\n\nint x = 1;\nwhile(x <= 3) {\n    std::cout << x++;\n}", "123"},
     {"What is the output?\n\nint a = 0;\nfor(int i = 0; i < 5; i++) {\n    a += i;\n}\nstd::cout << a;", "10"},
     {"What is the output?\n\nstd::vector<int> v = {1, 2, 3, 4};\nv.push_back(5);\nstd::cout << v.size();", "5"}
    };

    Puzzle currentPuzzle = getRandomMathPuzzle();
    bool isMathPhase = true;   // เฟสโจทย์คณิตศาสตร์
    int correctCount = 0;      // ตัวนับคำตอบที่ถูกต้อง

    // SECTION: การตั้งค่าและการแสดงข้อความในเกม

    sf::Text questionText(currentPuzzle.question, font, 50);
    questionText.setFillColor(Color::Cyan);
    questionText.setPosition(500 - (sizeof(questionText)) / 2, 300);

    sf::Text answerPrompt("", font, 50);
    answerPrompt.setFillColor(sf::Color::Green);
    answerPrompt.setPosition(500 - (sizeof(answerPrompt)) / 2, 400);

    sf::Text resultText("", font, 50);
    resultText.setPosition(500 - (sizeof(resultText)) / 2, 500);

    // ตัวแปรที่ใช้ในการป้อนคำตอบ
    std::string userAnswer = "";
    bool isCorrect = false;
    sf::Clock countdownClock;
    int countdownTime = 3;

    sf::Clock cursorClock;
    bool showCursor = true;
    float cursorBlinkTime = 0.5f;

    while (Puz) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }

            // รับอินพุตจากผู้เล่น
            if (!isCorrect && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !userAnswer.empty()) {
                    userAnswer.pop_back();  // ลบตัวอักษรเมื่อกด Backspace
                }
                else if (event.text.unicode == '\r') {  // เมื่อผู้เล่นกด Enter
                    if (userAnswer.empty()) {
                        resultText.setString("Please enter an answer!");
                        resultText.setPosition(450 - (sizeof(resultText)) / 2, 500);
                        resultText.setFillColor(sf::Color::Yellow);
                    }
                    else if (userAnswer == currentPuzzle.answer) {
                        // ผู้เล่นตอบถูก
                        resultText.setString("You're Correct! (3s)");
                        resultText.setFillColor(sf::Color::Green);
                        isCorrect = true;
                        countdownClock.restart();
                        correctCount++;
                    }
                    else {
                        // ผู้เล่นตอบผิด
                        resultText.setString("Incorrect! Try again.");
                        resultText.setPosition(450 - (sizeof(resultText)) / 2, 500);
                        resultText.setFillColor(sf::Color::Red);
                    }
                    userAnswer = "";

                    // เปลี่ยนเป็นเฟสโจทย์โค้ดเมื่อผู้เล่นตอบถูก 2 ข้อในเฟสคณิตศาสตร์
                    if (correctCount >= 2 && isMathPhase) {
                        isMathPhase = false;
                        resultText.setString("Welcome to the coding phase!");
                        resultText.setFillColor(sf::Color::Magenta);
                        currentPuzzle = getRandomCodePuzzle(codePuzzles);
                        questionText.setFillColor(sf::Color::Yellow);
                        questionText.setString(currentPuzzle.question);
                    }
                    else if (!isMathPhase) {
                        currentPuzzle = getRandomCodePuzzle(codePuzzles);
                        questionText.setString(currentPuzzle.question);
                    }
                    else {
                        currentPuzzle = getRandomMathPuzzle();
                        questionText.setString(currentPuzzle.question);
                    }
                }
                else if (event.text.unicode < 128) {
                    userAnswer += static_cast<char>(event.text.unicode);  // รับตัวอักษรจากผู้เล่น
                }
            }
        }

        // กระพริบเคอร์เซอร์เมื่อผู้เล่นกำลังพิมพ์คำตอบ
        if (!isCorrect && cursorClock.getElapsedTime().asSeconds() >= cursorBlinkTime) {
            showCursor = !showCursor;
            cursorClock.restart();
        }

        if (!isCorrect) {
            answerPrompt.setString("Your answer: " + userAnswer + (showCursor ? "_" : " "));
        }
        if (isCorrect) {
            Puz = false;
        }

        // ------------------------------------------
        // SECTION: การแสดงผล
        // ------------------------------------------
        window.clear();
        window.draw(questionText);
        window.draw(answerPrompt);
        window.draw(resultText);
        window.display();

    }

}
void Menu() {
 
        RenderWindow window(VideoMode(1000, 1000), "Mazegame");

        Texture Bg;
        if (!Bg.loadFromFile("bgMenu5.jpg")) {
            cerr << "Error: Could not load image!" << endl;
            return;
        }

        // smoothing
        Bg.setSmooth(true);

        // สร้าง Sprite และตั้งค่า Texture
        Sprite Bgsprite;
        Bgsprite.setTexture(Bg);
        // คำนวณอัตราส่วนเพื่อปรับขนาดให้เต็มหน้าจอ
        Bgsprite.setScale(
            static_cast<float>(window.getSize().x) / Bg.getSize().x,
            static_cast<float>(window.getSize().y) / Bg.getSize().y     // ขนาดของหน้าต่าง (RenderWindow)
        );


        //Logo
        Texture LogogameTexture;
        if (!LogogameTexture.loadFromFile("Logo.png")) {
            cerr << "Error: Could not load Logo image!" << endl;
            return;
        }
        LogogameTexture.setSmooth(true);

        Sprite Logogamesp;
        Logogamesp.setTexture(LogogameTexture);
        Logogamesp.setPosition(165, 150); // ตำแหน่ง x,y
        //ButtonStsp.setScale(0.7f,0.7f);  // ขนาดปุ่ม
        Vector2f normalScaleLg(0.50f, 0.34f);
        //Vector2f clickScaleLg(0.15f, 0.11f);
        Logogamesp.setScale(normalScaleLg);


        //ปุ่ม start
        Texture ButtonStTexture;
        if (!ButtonStTexture.loadFromFile("Start.png")) {
            cerr << "Error: Could not load button image!" << endl;
            return;
        }
        ButtonStTexture.setSmooth(true);

        Sprite ButtonStsp;
        ButtonStsp.setTexture(ButtonStTexture);
        ButtonStsp.setPosition(520, 800); // ตำแหน่ง x,y
        //ButtonStsp.setScale(0.7f,0.7f);  // ขนาดปุ่ม
        Vector2f normalScaleSt(0.50f, 0.34f);
        Vector2f clickScaleSt(0.30f, 0.17f);
        ButtonStsp.setScale(normalScaleSt);

        bool isPressed = false; // เช็กว่าปุ่มถูกกดอยู่หรือไม่

        // ตั้ง Origin ให้อยู่ตรงกลางของปุ่ม
        ButtonStsp.setOrigin(ButtonStTexture.getSize().x / 2.0f, ButtonStTexture.getSize().y / 2.0f);

 
    while (window.isOpen()) {
        sf::Event event;
        Vector2i mousePos = Mouse::getPosition(window);
        bool isHovering = ButtonStsp.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //  ตรวจจับการคลิกปุ่ม start
            if (isHovering) {
                ButtonStsp.setColor(Color(200, 200, 200)); // เปลี่ยนสีเมื่อ Hover

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    ButtonStsp.setScale(clickScaleSt); // ย่อขนาดลง
                    isPressed = true;
                    if (buttonSound.getStatus() != sf::Sound::Playing) {
                        buttonSound.play();
                    }
                }

                if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                    ButtonStsp.setScale(normalScaleSt); // คืนขนาดเดิม
                    isPressed = false;
                    cout << "Start clicked!" << endl;
                   
                    window.close();
                    
                    
                }
            }
            else {
                ButtonStsp.setColor(Color::White);  // กลับเป็นสีเดิม
            }

        }

        // แสดงผล
        window.clear(); // ล้างหน้าจอ
        window.draw(Bgsprite);
        window.draw(ButtonStsp);
        window.draw(Logogamesp);
        window.display(); // แสดงผล
    }

}
void resetMap() {
   
        for (int i = 0; i < 40 * 40; i++) {
            gameMap[i] = 0;  // รีเซ็ตค่าของแผนที่
            displayRects[i].setFillColor(Color::White);  // รีเซ็ตสีพื้นหลัง
            displayRects[i].setTexture(nullptr); // เอา texture ออก
       }
    

}