//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <cmath>
//using namespace sf;
//using namespace std;
//
//void Menu();
//
//int main() {
//
//    Menu();
//    return 0;
//}
//
//void Menu() {
//    RenderWindow window(VideoMode(800, 600), "GAME name");
//
//    // โหลด Texture
//    Texture Bg;
//    if (!Bg.loadFromFile("bgMenu5.jpg")) {
//        cerr << "Error: Could not load image!" << endl;
//        return;
//    }
//
//    // smoothing
//    Bg.setSmooth(true);
//
//    // สร้าง Sprite และตั้งค่า Texture
//    Sprite Bgsprite;
//    Bgsprite.setTexture(Bg);
//    // คำนวณอัตราส่วนเพื่อปรับขนาดให้เต็มหน้าจอ
//    Bgsprite.setScale(
//        static_cast<float>(window.getSize().x) / Bg.getSize().x,
//        static_cast<float>(window.getSize().y) / Bg.getSize().y     // ขนาดของหน้าต่าง (RenderWindow)
//    );
//
//
//    //Logo
//    Texture LogogameTexture;
//    if (!LogogameTexture.loadFromFile("Logo.png")) {
//        cerr << "Error: Could not load Logo image!" << endl;
//        return;
//    }
//    LogogameTexture.setSmooth(true);
//
//    Sprite Logogamesp;
//    Logogamesp.setTexture(LogogameTexture);
//    Logogamesp.setPosition(265, 100); // ตำแหน่ง x,y
//    //ButtonStsp.setScale(0.7f,0.7f);  // ขนาดปุ่ม
//    Vector2f normalScaleLg(0.22f, 0.18f);
//    //Vector2f clickScaleLg(0.15f, 0.11f);
//    Logogamesp.setScale(normalScaleLg);
//
//
//    //ปุ่ม start
//    Texture ButtonStTexture;
//    if (!ButtonStTexture.loadFromFile("Start.png")) {
//        cerr << "Error: Could not load button image!" << endl;
//        return;
//    }
//    ButtonStTexture.setSmooth(true);
//
//    Sprite ButtonStsp;
//    ButtonStsp.setTexture(ButtonStTexture);
//    ButtonStsp.setPosition(420, 490); // ตำแหน่ง x,y
//    //ButtonStsp.setScale(0.7f,0.7f);  // ขนาดปุ่ม
//    Vector2f normalScaleSt(0.20f, 0.16f);
//    Vector2f clickScaleSt(0.15f, 0.11f);
//    ButtonStsp.setScale(normalScaleSt);
//
//    bool isPressed = false; // เช็กว่าปุ่มถูกกดอยู่หรือไม่
//
//    // ตั้ง Origin ให้อยู่ตรงกลางของปุ่ม
//    ButtonStsp.setOrigin(ButtonStTexture.getSize().x / 2.0f, ButtonStTexture.getSize().y / 2.0f);
//
//
//    while (window.isOpen()) {
//        sf::Event event;
//        Vector2i mousePos = Mouse::getPosition(window);
//        bool isHovering = ButtonStsp.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
//
//
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            //  ตรวจจับการคลิกปุ่ม start
//            if (isHovering) {
//                ButtonStsp.setColor(Color(200, 200, 200)); // เปลี่ยนสีเมื่อ Hover
//
//                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
//                    ButtonStsp.setScale(clickScaleSt); // ย่อขนาดลง
//                    isPressed = true;
//                }
//
//                if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
//                    ButtonStsp.setScale(normalScaleSt); // คืนขนาดเดิม
//                    isPressed = false;
//                    cout << "Start clicked!" << endl;
//                    window.close();  // สามารถเปลี่ยนเป็นโหลดหน้าเกมได้
//                }
//            }
//            else {
//                ButtonStsp.setColor(Color::White);  // กลับเป็นสีเดิม
//            }
//
//        }
//
//        // แสดงผล
//        window.clear(); // ล้างหน้าจอ
//        window.draw(Bgsprite);
//        window.draw(ButtonStsp);
//        window.draw(Logogamesp);
//        window.display(); // แสดงผล
//    }
//
//}
//
//
