#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace sf;

int main()
{
    Vector2f res;
    res.x = VideoMode::getDesktopMode().width;
    res.y = VideoMode::getDesktopMode().height;

    RenderWindow rm(VideoMode(res.x, res.y), "Timber", Style::Fullscreen);

    Texture bgTexture;
    bgTexture.loadFromFile("Sprites/Graphics/background.png");
    Sprite bgSprite;
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0, 0);

    Texture treeTexture;
    treeTexture.loadFromFile("Sprites/Graphics/tree.png");
    Sprite treeSprite;
    treeSprite.setTexture(treeTexture);
    treeSprite.setPosition(res.x / 2 - 300 / 2, 0);

    Texture beeTexture;
    beeTexture.loadFromFile("Sprites/Graphics/bee.png");
    Sprite beeSprite1, beeSprite2, beeSprite3, beeSprite4;
    beeSprite1.setTexture(beeTexture);
    beeSprite2.setTexture(beeTexture);
    beeSprite3.setTexture(beeTexture);
    beeSprite4.setTexture(beeTexture);
    bool beeActive1 = false, beeActive2 = false, beeActive3 = false, beeActive4 = false;
    float beeSpeed1 = 0, beeSpeed2 = 0, beeSpeed3 = 0, beeSpeed4 = 0;

    Texture cloudTexture;
    cloudTexture.loadFromFile("Sprites/Graphics/cloud.png");
    Sprite cloudSprite1, cloudSprite2, cloudSprite3;
    cloudSprite1.setTexture(cloudTexture);
    cloudSprite2.setTexture(cloudTexture);
    cloudSprite3.setTexture(cloudTexture);
    bool cloudActive1 = false, cloudActive2 = false, cloudActive3 = false;
    float cloudSpeed1 = 0, cloudSpeed2 = 0, cloudSpeed3 = 0;

    Texture playerTexture;
    playerTexture.loadFromFile("Sprites/Graphics/player.png");
    Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(480, res.y - 330);

    RectangleShape timeBar;
    float timeBarStartWidth = 400.0f;
    float timeBarHeight = 80.0f;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((res.x / 2) - timeBarStartWidth / 2.0f, res.y - 100);
    float timeRemaining = 10.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    Font font;
    font.loadFromFile("Sprites/Font/KOMIKAP_.ttf");
    Text messageText;
    messageText.setFont(font);
    messageText.setString("Press Enter to start!");
    messageText.setCharacterSize(80);
    messageText.setFillColor(Color::White);
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(res.x / 2.0f, res.y / 2.0f);

    Clock clock;
    bool paused = true;

    while (rm.isOpen())
    {
        Event event;
        while (rm.pollEvent(event))
        {
            if (event.type == Event::Closed)
                rm.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            rm.close();

        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            paused = !paused;
            timeRemaining = 10.0f;
        }

        Time dt = clock.restart();

        if (!paused)
        {
            timeRemaining -= dt.asSeconds();
            if (timeRemaining < 0) {
                paused = true;
            }
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (!beeActive1) {
                beeSpeed1 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite1.setPosition(res.x + 200, height);
                beeActive1 = true;
            }
            else {
                beeSprite1.move(-beeSpeed1 * dt.asSeconds(), 0);
                if (beeSprite1.getPosition().x < -100) beeActive1 = false;
            }

            if (!beeActive2) {
                beeSpeed2 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite2.setPosition(res.x + 200, height);
                beeActive2 = true;
            }
            else {
                beeSprite2.move(-beeSpeed2 * dt.asSeconds(), 0);
                if (beeSprite2.getPosition().x < -100) beeActive2 = false;
            }

            if (!beeActive3) {
                beeSpeed3 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite3.setPosition(res.x + 200, height);
                beeActive3 = true;
            }
            else {
                beeSprite3.move(-beeSpeed3 * dt.asSeconds(), 0);
                if (beeSprite3.getPosition().x < -100) beeActive3 = false;
            }

            if (!beeActive4) {
                beeSpeed4 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite4.setPosition(res.x + 200, height);
                beeActive4 = true;
            }
            else {
                beeSprite4.move(-beeSpeed4 * dt.asSeconds(), 0);
                if (beeSprite4.getPosition().x < -100) beeActive4 = false;
            }

            if (!cloudActive1) {
                cloudSpeed1 = (rand() % 200);
                float height = (rand() % 150);
                cloudSprite1.setPosition(-200, height);
                cloudActive1 = true;
            }
            else {
                cloudSprite1.move(cloudSpeed1 * dt.asSeconds(), 0);
                if (cloudSprite1.getPosition().x > res.x) cloudActive1 = false;
            }

            if (!cloudActive2) {
                cloudSpeed2 = (rand() % 200);
                float height = (rand() % 150);
                cloudSprite2.setPosition(-200, height);
                cloudActive2 = true;
            }
            else {
                cloudSprite2.move(cloudSpeed2 * dt.asSeconds(), 0);
                if (cloudSprite2.getPosition().x > res.x) cloudActive2 = false;
            }

            if (!cloudActive3) {
                cloudSpeed3 = (rand() % 200);
                float height = (rand() % 150);
                cloudSprite3.setPosition(-200, height);
                cloudActive3 = true;
            }
            else {
                cloudSprite3.move(cloudSpeed3 * dt.asSeconds(), 0);
                if (cloudSprite3.getPosition().x > res.x) cloudActive3 = false;
            }
        }
        rm.clear();
        rm.draw(bgSprite);
        rm.draw(treeSprite);
        rm.draw(beeSprite1);
        rm.draw(beeSprite2);
        rm.draw(beeSprite3);
        rm.draw(beeSprite4);
        rm.draw(cloudSprite1);
        rm.draw(cloudSprite2);
        rm.draw(cloudSprite3);
        rm.draw(playerSprite);
        rm.draw(timeBar);
        if (paused)
            rm.draw(messageText);
        rm.display();
    }
}