void CharacterSelect();

enum GameState {
    MAIN_MENU,     // หน้าจอหลัก
    CHARACTER_SELECT  // หน้าจอเลือกตัวละคร
};

enum Character {
    MALE,
    FEMALE
};

Character selectedCharacter = MALE;

Menu();  // หรือฟังก์ชันที่ใช้ในการเลือกตัวละคร
ST = false;
Vector2i player = Vector2i(20, 0);  // ตำแหน่งเริ่มต้นของตัวละคร          
Sprite playerSprite;                // Sprite ที่ใช้แสดงตัวละคร

// เช็คว่าตัวละครที่เลือกคือ male หรือ female
if (selectedCharacter == MALE) {
    // ถ้าเลือก male
    if (!playerTex.loadFromFile("Mini male.png")) {
        std::cerr << "Error: Could not load male character image!" << std::endl;
        return 0;
    }
}
else if (selectedCharacter == FEMALE) {
    // ถ้าเลือก female
    if (!playerTex.loadFromFile("smile.png")) {
        std::cerr << "Error: Could not load female character image!" << std::endl;
        return 0;
    }
}

// ตั้งค่า Sprite สำหรับตัวละคร
playerSprite.setTexture(playerTex);
playerSprite.setScale(0.05f, 0.05f);  // ตั้งขนาดของตัวละคร
playerSprite.setPosition(player.x * 25.f, player.y * 25.f);  // ตั้งตำแหน่ง
window.draw(playerSprite);

while (window.isOpen() && !ST) {

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
        window.clear(sf::Color::White);
        Mode = 1;
    }
    if (Mode == 1) { resetMap(); Map1(); }
    if (Mode == 2) { resetMap(); Map2(); }
    if (Mode == 3) { resetMap(); Map3(); }
    if (Mode == 4) { resetMap(); Map4(); }
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();

        }

        if (event.type == sf::Event::KeyPressed) {

            sf::Vector2i newPosition = player;
            switch (event.key.code) {

            case sf::Keyboard::W: // Move up
                puzzlesolve = false;
                if (footstepSound.getStatus() != sf::Sound::Playing) {
                    footstepSound.play();
                }
                if (player.y > 0) { newPosition.y -= 1; }
                else newPosition.y -= 0;
                break;
            case sf::Keyboard::S: // Move down
                puzzlesolve = false;
                if (footstepSound.getStatus() != sf::Sound::Playing) {
                    footstepSound.play();
                }
                newPosition.y += 1;
                break;
            case sf::Keyboard::D: // Move right
                puzzlesolve = false;
                if (footstepSound.getStatus() != sf::Sound::Playing) {
                    footstepSound.play();
                }
                newPosition.x += 1;
                break;
            case sf::Keyboard::A: // Move left
                puzzlesolve = false;
                if (footstepSound.getStatus() != sf::Sound::Playing) {
                    footstepSound.play();
                }
                newPosition.x -= 1;
                break;
            }

            if (Keyboard::isKeyPressed(Keyboard::Space)) { player = newPosition; }
            if (gameMap[newPosition.x + newPosition.y * 40] != 1) {
                player = newPosition;
                std::cout << "Player position: (" << player.x << ", " << player.y << ")" << std::endl;
            }
        }

        playerSprite.setPosition(player.x * 25.f, player.y * 25.f);
    }
    window.clear(Color::White);

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

            if (isHovering) {
                ButtonStsp.setColor(Color(200, 200, 200)); // เปลี่ยนสีเมื่อ Hover

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    ButtonStsp.setScale(clickScaleSt); // ย่อขนาดลง
                    isPressed = true;
                }

                if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                    ButtonStsp.setScale(normalScaleSt); // คืนขนาดเดิม
                    isPressed = false;
                    cout << "Start clicked!" << endl;
                    window.close();  // ปิดหน้าจอเมนูและไปหน้าเลือกตัวละคร
                    CharacterSelect(); // เรียกฟังก์ชันหน้าจอเลือกตัวละคร
                }
            }
            else {
                ButtonStsp.setColor(Color::White);  // กลับเป็นสีเดิม
            }
        }

        // แสดงผล
        window.clear();
        window.draw(Bgsprite);
        window.draw(ButtonStsp);
        window.draw(Logogamesp);
        window.display();
    }
}

void CharacterSelect() {
    RenderWindow window(VideoMode(1000, 1000), "Character Select");

    // โหลด Texture สำหรับหน้าจอเลือกตัวละคร
    Texture Bg;
    if (!Bg.loadFromFile("bgMenu5.jpg")) {
        cerr << "Error: Could not load character selection background!" << endl;
        return;
    }
    Bg.setSmooth(true);
    Sprite Bgsprite;
    Bgsprite.setTexture(Bg);
    Bgsprite.setScale(
        static_cast<float>(window.getSize().x) / Bg.getSize().x,
        static_cast<float>(window.getSize().y) / Bg.getSize().y
    );

    // สร้างปุ่มเลือกตัวละครชาย
    Texture ButtonMaleTexture;
    if (!ButtonMaleTexture.loadFromFile("Male button.png")) {
        cerr << "Error: Could not load male character button!" << endl;
        return;
    }
    ButtonMaleTexture.setSmooth(true);
    Sprite ButtonMalebtn;
    ButtonMalebtn.setTexture(ButtonMaleTexture);
    ButtonMalebtn.setScale(0.50f, 0.34f); // ขนาดเท่ากับปุ่ม Start
    ButtonMalebtn.setOrigin(ButtonMaleTexture.getSize().x / 2.0f, ButtonMaleTexture.getSize().y / 2.0f);
    ButtonMalebtn.setPosition(window.getSize().x * 0.25f, window.getSize().y - ButtonMaleTexture.getSize().y * 0.5f); // วางทางซ้าย

    // สร้างปุ่มเลือกตัวละครหญิง
    Texture ButtonFemaleTexture;
    if (!ButtonFemaleTexture.loadFromFile("Female button.png")) {
        cerr << "Error: Could not load female character button!" << endl;
        return;
    }
    ButtonFemaleTexture.setSmooth(true);
    Sprite ButtonFemalebtn;
    ButtonFemalebtn.setTexture(ButtonFemaleTexture);
    ButtonFemalebtn.setScale(0.50f, 0.34f); // ขนาดเท่ากับปุ่ม Start
    ButtonFemalebtn.setOrigin(ButtonFemaleTexture.getSize().x / 2.0f, ButtonFemaleTexture.getSize().y / 2.0f);
    ButtonFemalebtn.setPosition(window.getSize().x * 0.75f, window.getSize().y - ButtonFemaleTexture.getSize().y * 0.5f); // วางทางขวา

    // โหลดภาพตัวละคร (ชายและหญิง)
    Texture MaleCharacterTexture;
    if (!MaleCharacterTexture.loadFromFile("Male.png")) {
        cerr << "Error: Could not load male character image!" << endl;
        return;
    }
    Sprite MaleCharacterSprite;
    MaleCharacterSprite.setTexture(MaleCharacterTexture);
    MaleCharacterSprite.setScale(0.5f, 0.5f);  // ปรับขนาดของตัวละคร
    MaleCharacterSprite.setPosition(window.getSize().x * 0.02f, window.getSize().y * 0.04f); // วางด้านบนของปุ่ม Male

    Texture FemaleCharacterTexture;
    if (!FemaleCharacterTexture.loadFromFile("Female.png")) {
        cerr << "Error: Could not load female character image!" << endl;
        return;
    }
    Sprite FemaleCharacterSprite;
    FemaleCharacterSprite.setTexture(FemaleCharacterTexture);
    FemaleCharacterSprite.setScale(1.0f, 1.0f);  // ปรับขนาดของตัวละคร
    FemaleCharacterSprite.setPosition(window.getSize().x * 0.5f, window.getSize().y * 0.15f); // วางด้านบนของปุ่ม Female

    bool maleSelected = false;
    bool femaleSelected = false;

    // เพิ่มตัวแปรสำหรับการตรวจจับการกดปุ่ม
    bool isMalePressed = false;
    bool isFemalePressed = false;

    // เพิ่มเวลาช่วยให้ทำการย่อขนาดของปุ่ม
    Vector2f normalScale(0.50f, 0.34f);
    Vector2f pressedScale(0.30f, 0.17f); // ขนาดตอนกดปุ่ม

    while (window.isOpen()) {
        sf::Event event;
        Vector2i mousePos = Mouse::getPosition(window);

        bool isHoveringMale = ButtonMalebtn.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        bool isHoveringFemale = ButtonFemalebtn.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // ตรวจจับอีเวนต์ต่างๆ
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // เช็คว่ากดปุ่ม Male หรือ Female
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (isHoveringMale) {
                    ButtonMalebtn.setScale(pressedScale); // ย่อขนาดปุ่ม
                    isMalePressed = true;
                    maleSelected = true;
                    cout << "Male selected!" << endl;
                }
                if (isHoveringFemale) {
                    ButtonFemalebtn.setScale(pressedScale); // ย่อขนาดปุ่ม
                    isFemalePressed = true;
                    femaleSelected = true;
                    cout << "Female selected!" << endl;
                }
            }

            // เช็คปล่อยปุ่ม
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                if (isMalePressed) {
                    ButtonMalebtn.setScale(normalScale); // คืนขนาดปกติ
                    isMalePressed = false;
                    if (maleSelected) {
                        window.close(); // ปิดหน้าจอเลือกตัวละคร
                        Map1(); // เรียก Map1() หรือฟังก์ชันเกมที่คุณต้องการ
                    }
                }
                if (isFemalePressed) {
                    ButtonFemalebtn.setScale(normalScale); // คืนขนาดปกติ
                    isFemalePressed = false;
                    if (femaleSelected) {
                        window.close(); // ปิดหน้าจอเลือกตัวละคร
                        Map1(); // เรียก Map1() หรือฟังก์ชันเกมที่คุณต้องการ
                    }
                }
            }
        }

        // เปลี่ยนสีปุ่มเมื่อเมาส์ชี้ไปที่มัน
        if (isHoveringMale) {
            ButtonMalebtn.setColor(Color(200, 200, 200)); // เปลี่ยนสีเมื่อ Hover
        }
        else {
            ButtonMalebtn.setColor(Color::White);  // กลับเป็นสีเดิม
        }

        if (isHoveringFemale) {
            ButtonFemalebtn.setColor(Color(200, 200, 200)); // เปลี่ยนสีเมื่อ Hover
        }
        else {
            ButtonFemalebtn.setColor(Color::White);  // กลับเป็นสีเดิม
        }

        if (maleSelected || femaleSelected) {
            // คุณสามารถเปลี่ยนไปยังหน้าจอเกมหรือฟังก์ชันที่คุณต้องการได้ที่นี่
            window.close(); // ปิดหน้าจอเลือกตัวละคร
            Map1();
        }

        // แสดงผล
        window.clear();
        window.draw(Bgsprite);
        window.draw(MaleCharacterSprite);  // วาดภาพตัวละครชาย
        window.draw(FemaleCharacterSprite); // วาดภาพตัวละครหญิง
        window.draw(ButtonMalebtn);
        window.draw(ButtonFemalebtn);
        window.display();
    }
}

