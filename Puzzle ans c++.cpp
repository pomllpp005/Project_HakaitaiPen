#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

// โครงสร้างเก็บข้อมูลโจทย์และคำตอบ
struct Puzzle {
    std::string question;
    std::string answer;
};

// ฟังก์ชันสุ่มโจทย์ใหม่
Puzzle getRandomPuzzle(const std::vector<Puzzle>& puzzles) {
    int index = rand() % puzzles.size();
    return puzzles[index];
}

int main() {
    // ตั้งค่าเริ่มต้น
    srand(static_cast<unsigned>(time(nullptr)));

    // สร้างหน้าต่างเกม
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Puzzle Game");

    // โหลดฟอนต์จาก Windows เท่านั้น
    sf::Font font;
#ifdef _WIN32  // Windows
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error loading system font (arial.ttf)!\n";
        return -1;
    }
#else
    std::cerr << "This program supports only Windows fonts.\n";
    return -1;
#endif

    // 🔹 โจทย์และคำตอบ
    std::vector<Puzzle> puzzles = {
        {"What is the output?\n\nint a = 2;\nint b = 3;\nstd::cout << a + b;", "5"},
        {"What is the output?\n\nint x = 10;\nstd::cout << x * 2;", "20"},
        {"What is the output?\n\nfor(int i=0; i<3; i++) {\n    std::cout << i;\n}", "012"},
        {"What is the output?\n\nint arr[3] = {1, 2, 3};\nstd::cout << arr[1];", "2"},
        {"What is the output?\n\nint arr[] = {1, 2, 3};\nfor(int i = 0; i < 3; i++) {\n    std::cout << arr[i];\n}", "123"},
        {"What is the output?\n\nfor(int i = 1; i < 5; i++) {\n    std::cout << i * 2;\n}", "246"}
    };

    // เลือกโจทย์แรก
    Puzzle currentPuzzle = getRandomPuzzle(puzzles);

    // ข้อความโจทย์
    sf::Text questionText(currentPuzzle.question, font, 24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(50, 50);

    // ข้อความสำหรับรับคำตอบ
    sf::Text answerPrompt("", font, 24);
    answerPrompt.setFillColor(sf::Color::White);
    answerPrompt.setPosition(50, 250);

    // ข้อความแจ้งเตือนผลลัพธ์
    sf::Text resultText("", font, 32);
    resultText.setFillColor(sf::Color::Green);
    resultText.setPosition(50, 350);

    std::string userAnswer = "";
    bool isCorrect = false;
    sf::Clock countdownClock;
    int countdownTime = 3; // นับถอยหลัง 3 วินาที

    // ตัวจับเวลาสำหรับทำให้เคอร์เซอร์กระพริบ
    sf::Clock cursorClock;
    bool showCursor = true;
    float cursorBlinkTime = 0.5f;

    // วนลูปเกม
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close(); // ปิดโปรแกรมเมื่อกด ESC
            }

            // รับอินพุตจากแป้นพิมพ์
            if (!isCorrect && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !userAnswer.empty()) {
                    userAnswer.pop_back();
                }
                else if (event.text.unicode == '\r') { // กด Enter เพื่อตรวจคำตอบ
                    if (userAnswer.empty()) {
                        // ไม่สามารถเปลี่ยนโจทย์ได้ถ้ายังไม่ตอบ
                        resultText.setString("Please enter an answer!");
                        resultText.setFillColor(sf::Color::Yellow);
                    }
                    else if (userAnswer == currentPuzzle.answer) {
                        resultText.setString("You're Correct! (3s)");
                        resultText.setFillColor(sf::Color::Green);
                        isCorrect = true;
                        countdownClock.restart(); // เริ่มจับเวลา 3 วินาที
                    }
                    else {
                        resultText.setString("Incorrect! Try again.");
                        resultText.setFillColor(sf::Color::Red);

                        // เปลี่ยนโจทย์ใหม่ทันทีเมื่อผิด
                        currentPuzzle = getRandomPuzzle(puzzles);
                        questionText.setString(currentPuzzle.question);
                    }
                    userAnswer = ""; // เคลียร์คำตอบ
                }
                else if (event.text.unicode < 128) {
                    userAnswer += static_cast<char>(event.text.unicode);
                }
            }
        }

        // กระพริบเคอร์เซอร์
        if (!isCorrect && cursorClock.getElapsedTime().asSeconds() >= cursorBlinkTime) {
            showCursor = !showCursor;
            cursorClock.restart();
        }

        // อัปเดตข้อความคำตอบพร้อมเคอร์เซอร์กระพริบ
        if (!isCorrect) {
            answerPrompt.setString("Your answer: " + userAnswer + (showCursor ? "_" : " "));
        }

        // ถ้าผู้เล่นตอบถูก เริ่มนับถอยหลัง 3 วินาที และปิดโปรแกรม
        if (isCorrect) {
            int timeLeft = countdownTime - static_cast<int>(countdownClock.getElapsedTime().asSeconds());
            if (timeLeft <= 0) {
                window.close(); // ปิดโปรแกรมเมื่อครบ 3 วินาที
            }
            else {
                resultText.setString("You're Correct! (" + std::to_string(timeLeft) + "s)");
            }
        }

        // วาดหน้าจอ
        window.clear();
        window.draw(questionText);
        window.draw(answerPrompt);
        window.draw(resultText);
        window.display();
    }

    return 0;
}
