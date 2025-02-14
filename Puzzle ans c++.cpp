#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

struct Puzzle {
    std::string question;
    std::string answer;
};

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

Puzzle getRandomPuzzle(const std::vector<Puzzle>& puzzles) {
    int index = rand() % puzzles.size();
    return puzzles[index];
}

void drawRoundedTextBox(sf::RenderWindow& window, sf::Text& text, sf::Color boxColor, float padding = 20.f) {
    sf::FloatRect textBounds = text.getGlobalBounds();
    sf::RectangleShape textBox(sf::Vector2f(textBounds.width + padding * 2, textBounds.height + padding * 2));
    textBox.setPosition(textBounds.left - padding, textBounds.top - padding);
    textBox.setFillColor(boxColor);
    textBox.setOutlineColor(sf::Color::White);
    textBox.setOutlineThickness(2);
    window.draw(textBox);
    window.draw(text);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "C++ Puzzle Game");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("bg.png")) {
        std::cerr << "Error loading background image!\n";
        return -1;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error loading font (arial.ttf)!\n";
        return -1;
    }

    std::vector<Puzzle> puzzles = {
        getRandomMathPuzzle(),
        {"What is the output?\n\nint a = 2;\nint b = 3;\nstd::cout << a + b;", "5"},
        {"What is the output?\n\nint x = 10;\nstd::cout << x * 2;", "20"},
        {"What is the output?\n\nint sum = 0;\nfor(int i=1; i<=5; i++) {\n    sum += i;\n}\nstd::cout << sum;", "15"},
        {"What is the output?\n\nstd::string s = \"Hello\";\nstd::cout << s.size();", "5"}
    };

    Puzzle currentPuzzle = getRandomPuzzle(puzzles);

    sf::Text questionText(currentPuzzle.question, font, 24);
    questionText.setFillColor(sf::Color::Black);
    questionText.setPosition(200, 200);

    sf::Text answerPrompt("", font, 24);
    answerPrompt.setFillColor(sf::Color::White);
    answerPrompt.setPosition(150, 600);

    sf::Text resultText("", font, 32);
    resultText.setPosition(150, 700);

    std::string userAnswer = "";
    bool isCorrect = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !userAnswer.empty()) {
                    userAnswer.pop_back();
                }
                else if (event.text.unicode == '\r') {
                    if (userAnswer == currentPuzzle.answer) {
                        resultText.setString("Correct! New puzzle incoming...");
                        resultText.setFillColor(sf::Color::Green);
                        currentPuzzle = getRandomPuzzle(puzzles);
                        questionText.setString(currentPuzzle.question);
                    }
                    else {
                        resultText.setString("Incorrect. Try again!");
                        resultText.setFillColor(sf::Color::Red);
                    }
                    userAnswer = "";
                }
                else if (event.text.unicode < 128) {
                    userAnswer += static_cast<char>(event.text.unicode);
                }
            }
        }

        answerPrompt.setString("Your answer: " + userAnswer + "_");

        window.clear();
        window.draw(backgroundSprite);  // วาด background ก่อน
        drawRoundedTextBox(window, questionText, sf::Color(0, 0, 0, 0));
        drawRoundedTextBox(window, answerPrompt, sf::Color(0, 100, 0, 150));
        drawRoundedTextBox(window, resultText, sf::Color(100, 0, 0, 150));
        window.display();
    }

    return 0;
}
