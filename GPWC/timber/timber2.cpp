#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace sf;

int main() {
    srand(static_cast<unsigned>(time(0)));

    Vector2f res(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    RenderWindow window(VideoMode(res.x, res.y), "Timber Game!");

    Texture bgTexture; bgTexture.loadFromFile("Sprites/Graphics/background.png");
    Sprite bgSprite;
    bgSprite.setTexture(bgTexture);

    Texture treeTexture; treeTexture.loadFromFile("Sprites/Graphics/tree.png");
    Sprite treeSprite(treeTexture);
    treeSprite.setPosition(res.x / 2 - 150, 0);

    Texture beeTexture; beeTexture.loadFromFile("Sprites/Graphics/bee.png");
    Sprite beeSprite1(beeTexture), beeSprite2(beeTexture), beeSprite3(beeTexture), beeSprite4(beeTexture);
    bool beeActive1 = false, beeActive2 = false, beeActive3 = false, beeActive4 = false;
    float beeSpeed1 = 0, beeSpeed2 = 0, beeSpeed3 = 0, beeSpeed4 = 0;

    Texture cloudTexture; cloudTexture.loadFromFile("Sprites/Graphics/cloud.png");
    Sprite cloudSprite1(cloudTexture), cloudSprite2(cloudTexture), cloudSprite3(cloudTexture);
    bool cloudActive1 = false, cloudActive2 = false, cloudActive3 = false;
    float cloudSpeed1 = 0, cloudSpeed2 = 0, cloudSpeed3 = 0;

    Texture playerTexture; playerTexture.loadFromFile("Sprites/Graphics/player.png");
    Sprite playerSprite(playerTexture);
    playerSprite.setPosition(480, res.y - 330);

    RectangleShape timeBar;
    float timeBarStartWidth = 400, timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((res.x / 2) - timeBarStartWidth / 2.0f, res.y - 100);
    float timeRemaining = 10.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    Font font; font.loadFromFile("Sprites/Font/KOMIKAP_.ttf");
    Text messageText("", font, 60); messageText.setFillColor(Color::White);
    bool paused = true;

    Clock clock;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            paused = false;
            timeRemaining = 10.0f;
        }

        Time dt = clock.restart();

        if (!paused) {
            timeRemaining -= dt.asSeconds();
            if (timeRemaining < 0) timeRemaining = 0;
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
            if (timeRemaining <= 0) {
                paused = true;
                messageText.setString("Out of Time!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
                messageText.setPosition(res.x/2, res.y/2);
            }

            if (!beeActive1) {
                beeSpeed1 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite1.setPosition(res.x + 200, height);
                beeActive1 = true;
            } else {
                beeSprite1.move(-beeSpeed1 * dt.asSeconds(), 0);
                if (beeSprite1.getPosition().x < -100) beeActive1 = false;
            }

            if (!beeActive2) {
                beeSpeed2 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite2.setPosition(res.x + 200, height);
                beeActive2 = true;
            } else {
                beeSprite2.move(-beeSpeed2 * dt.asSeconds(), 0);
                if (beeSprite2.getPosition().x < -100) beeActive2 = false;
            }

            if (!beeActive3) {
                beeSpeed3 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite3.setPosition(res.x + 200, height);
                beeActive3 = true;
            } else {
                beeSprite3.move(-beeSpeed3 * dt.asSeconds(), 0);
                if (beeSprite3.getPosition().x < -100) beeActive3 = false;
            }

            if (!beeActive4) {
                beeSpeed4 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite4.setPosition(res.x + 200, height);
                beeActive4 = true;
            } else {
                beeSprite4.move(-beeSpeed4 * dt.asSeconds(), 0);
                if (beeSprite4.getPosition().x < -100) beeActive4 = false;
            }

            if (!cloudActive1) {
                cloudSpeed1 = (rand() % 100) + 50;
                float height = (rand() % 200) + 50;
                cloudSprite1.setPosition(-200, height);
                cloudActive1 = true;
            } else {
                cloudSprite1.move(cloudSpeed1 * dt.asSeconds(), 0);
                if (cloudSprite1.getPosition().x > res.x + 100) cloudActive1 = false;
            }

            if (!cloudActive2) {
                cloudSpeed2 = (rand() % 100) + 50;
                float height = (rand() % 200) + 50;
                cloudSprite2.setPosition(-200, height);
                cloudActive2 = true;
            } else {
                cloudSprite2.move(cloudSpeed2 * dt.asSeconds(), 0);
                if (cloudSprite2.getPosition().x > res.x + 100) cloudActive2 = false;
            }

            if (!cloudActive3) {
                cloudSpeed3 = (rand() % 100) + 50;
                float height = (rand() % 200) + 50;
                cloudSprite3.setPosition(-200, height);
                cloudActive3 = true;
            } else {
                cloudSprite3.move(cloudSpeed3 * dt.asSeconds(), 0);
                if (cloudSprite3.getPosition().x > res.x + 100) cloudActive3 = false;
            }
        } else {
            clock.restart();
        }
        window.clear();
        window.draw(bgSprite);
        window.draw(treeSprite);
        window.draw(cloudSprite1); window.draw(cloudSprite2); window.draw(cloudSprite3);
        window.draw(beeSprite1); window.draw(beeSprite2); window.draw(beeSprite3); window.draw(beeSprite4);
        window.draw(playerSprite);
        window.draw(timeBar);
        if (paused) window.draw(messageText);
        window.display();
    }
}