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
//    // ��Ŵ Texture
//    Texture Bg;
//    if (!Bg.loadFromFile("bgMenu5.jpg")) {
//        cerr << "Error: Could not load image!" << endl;
//        return;
//    }
//
//    // smoothing
//    Bg.setSmooth(true);
//
//    // ���ҧ Sprite ��е�駤�� Texture
//    Sprite Bgsprite;
//    Bgsprite.setTexture(Bg);
//    // �ӹǳ�ѵ����ǹ���ͻ�Ѻ��Ҵ������˹�Ҩ�
//    Bgsprite.setScale(
//        static_cast<float>(window.getSize().x) / Bg.getSize().x,
//        static_cast<float>(window.getSize().y) / Bg.getSize().y     // ��Ҵ�ͧ˹�ҵ�ҧ (RenderWindow)
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
//    Logogamesp.setPosition(265, 100); // ���˹� x,y
//    //ButtonStsp.setScale(0.7f,0.7f);  // ��Ҵ����
//    Vector2f normalScaleLg(0.22f, 0.18f);
//    //Vector2f clickScaleLg(0.15f, 0.11f);
//    Logogamesp.setScale(normalScaleLg);
//
//
//    //���� start
//    Texture ButtonStTexture;
//    if (!ButtonStTexture.loadFromFile("Start.png")) {
//        cerr << "Error: Could not load button image!" << endl;
//        return;
//    }
//    ButtonStTexture.setSmooth(true);
//
//    Sprite ButtonStsp;
//    ButtonStsp.setTexture(ButtonStTexture);
//    ButtonStsp.setPosition(420, 490); // ���˹� x,y
//    //ButtonStsp.setScale(0.7f,0.7f);  // ��Ҵ����
//    Vector2f normalScaleSt(0.20f, 0.16f);
//    Vector2f clickScaleSt(0.15f, 0.11f);
//    ButtonStsp.setScale(normalScaleSt);
//
//    bool isPressed = false; // ����һ����١�������������
//
//    // ��� Origin �������ç��ҧ�ͧ����
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
//            //  ��Ǩ�Ѻ��ä�ԡ���� start
//            if (isHovering) {
//                ButtonStsp.setColor(Color(200, 200, 200)); // ����¹������� Hover
//
//                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
//                    ButtonStsp.setScale(clickScaleSt); // ��͢�Ҵŧ
//                    isPressed = true;
//                }
//
//                if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
//                    ButtonStsp.setScale(normalScaleSt); // �׹��Ҵ���
//                    isPressed = false;
//                    cout << "Start clicked!" << endl;
//                    window.close();  // ����ö����¹����Ŵ˹������
//                }
//            }
//            else {
//                ButtonStsp.setColor(Color::White);  // ��Ѻ�������
//            }
//
//        }
//
//        // �ʴ���
//        window.clear(); // ��ҧ˹�Ҩ�
//        window.draw(Bgsprite);
//        window.draw(ButtonStsp);
//        window.draw(Logogamesp);
//        window.display(); // �ʴ���
//    }
//
//}
//
//
