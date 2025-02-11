#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

// ------------------------------------------
// SECTION: โครงสร้างข้อมูลและฟังก์ชันช่วยเหลือ
// ------------------------------------------

// โครงสร้างเก็บข้อมูลโจทย์และคำตอบ
struct Puzzle {
    std::string question;
    std::string answer;
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

    return {question, std::to_string(answer)};
}

// ฟังก์ชันสุ่มโจทย์โค้ดจากลิสต์ที่เตรียมไว้
Puzzle getRandomCodePuzzle(const std::vector<Puzzle>& puzzles) {
    int index = rand() % puzzles.size();
    return puzzles[index];
}

// ------------------------------------------
// SECTION: ฟังก์ชันหลักของโปรแกรม (main loop)
// ------------------------------------------
int main() {
    // ตั้งค่า seed สำหรับการสุ่มเลข
    srand(static_cast<unsigned>(time(nullptr)));

    // สร้างหน้าต่างแสดงผล (SFML)
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Puzzle Game");

    // โหลดฟอนต์เพื่อใช้ในการแสดงข้อความ
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error loading font (arial.ttf)!\n";
        return -1;
    }

    // ------------------------------------------
    // SECTION: เตรียมโจทย์และตัวแปรที่ใช้ในเกม
    // ------------------------------------------

    // โจทย์เกี่ยวกับโค้ด C++
    std::vector<Puzzle> codePuzzles = {
        {"What is the output?\n\nint a = 2;\nint b = 3;\nstd::cout << a + b;", "5"},
        {"What is the output?\n\nint x = 10;\nstd::cout << x * 2;", "20"},
        {"What is the output?\n\nfor(int i=0; i<3; i++) {\n    std::cout << i;\n}", "012"},
        {"What is the output?\n\nint sum = 0;\nfor(int i=1; i<=5; i++) {\n    sum += i;\n}\nstd::cout << sum;", "15"},
        {"What is the output?\n\nint a = 5;\nint b = 2;\nstd::cout << a / b;", "2"}
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

    // ตัวแปรเริ่มต้นของเกม
    Puzzle currentPuzzle = getRandomMathPuzzle();
    bool isMathPhase = true;   // เฟสโจทย์คณิตศาสตร์
    int correctCount = 0;      // ตัวนับคำตอบที่ถูกต้อง

    // ------------------------------------------
    // SECTION: การตั้งค่าและการแสดงข้อความในเกม
    // ------------------------------------------
    sf::Text questionText(currentPuzzle.question, font, 24);
    questionText.setFillColor(sf::Color::Cyan);
    questionText.setPosition(50, 50);

    sf::Text answerPrompt("", font, 24);
    answerPrompt.setFillColor(sf::Color::Green);
    answerPrompt.setPosition(50, 250);

    sf::Text resultText("", font, 32);
    resultText.setPosition(50, 350);

    // ตัวแปรที่ใช้ในการป้อนคำตอบ
    std::string userAnswer = "";
    bool isCorrect = false;
    sf::Clock countdownClock;
    int countdownTime = 3;

    sf::Clock cursorClock;
    bool showCursor = true;
    float cursorBlinkTime = 0.5f;

    // ------------------------------------------
    // SECTION: ลูปหลักของเกม
    // ------------------------------------------
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // รับอินพุตจากผู้เล่น
            if (!isCorrect && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !userAnswer.empty()) {
                    userAnswer.pop_back();  // ลบตัวอักษรเมื่อกด Backspace
                } else if (event.text.unicode == '\r') {  // เมื่อผู้เล่นกด Enter
                    if (userAnswer.empty()) {
                        resultText.setString("Please enter an answer!");
                        resultText.setFillColor(sf::Color::Yellow);
                    } else if (userAnswer == currentPuzzle.answer) {
                        // ผู้เล่นตอบถูก
                        resultText.setString("You're Correct! (3s)");
                        resultText.setFillColor(sf::Color::Green);
                        isCorrect = true;
                        countdownClock.restart();
                        correctCount++;
                    } else {
                        // ผู้เล่นตอบผิด
                        resultText.setString("Incorrect! Try again.");
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
                    } else if (!isMathPhase) {
                        currentPuzzle = getRandomCodePuzzle(codePuzzles);
                        questionText.setString(currentPuzzle.question);
                    } else {
                        currentPuzzle = getRandomMathPuzzle();
                        questionText.setString(currentPuzzle.question);
                    }
                } else if (event.text.unicode < 128) {
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
ๆ
        // นับถอยหลังเมื่อผู้เล่นตอบถูก
        if (isCorrect) {
            int timeLeft = countdownTime - static_cast<int>(countdownClock.getElapsedTime().asSeconds());
            if (timeLeft <= 0) {
                isCorrect = false;
                resultText.setString("");
            } else {
                resultText.setString("You're Correct! (" + std::to_string(timeLeft) + "s)");
            }
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

    return 0;
}
