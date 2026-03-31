#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side
{
    LEFT,
    RIGHT,
    NONE
};
side branchPositions[NUM_BRANCHES];

void updateBranches(int seed)
{
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
    {
        branchPositions[j] = branchPositions[j - 1];
    }
    srand((int)time(0) + seed);
    int r = (rand() % 3);
    switch (r)
    {
    case 0:
        branchPositions[0] = side::LEFT;
        break;
    case 1:
        branchPositions[0] = side::RIGHT;
        break;
    default:
        branchPositions[0] = side::NONE;
        break;
    }
}

int main()
{
    Vector2f res;
    res.x = VideoMode::getDesktopMode().width;
    res.y = VideoMode::getDesktopMode().height;

    VideoMode vm(res.x, res.y);

    RenderWindow rm(vm, "Timber", Style::Fullscreen);

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
    Sprite beeSprite1;
    beeSprite1.setTexture(beeTexture);
    beeSprite1.setPosition(1000, res.y / 2 - 100);
    Sprite beeSprite2;
    beeSprite2.setTexture(beeTexture);
    beeSprite2.setPosition(550, res.y / 2 - 40);
    Sprite beeSprite3;
    beeSprite3.setTexture(beeTexture);
    beeSprite3.setPosition(1100, res.y / 2 - 40);
    Sprite beeSprite4;
    beeSprite4.setTexture(beeTexture);
    beeSprite4.setPosition(450, res.y / 2 - 100);
    bool beeActive1 = false;
    bool beeActive2 = false;
    bool beeActive3 = false;
    bool beeActive4 = false;
    float beeSpeed1 = 0.0f;
    float beeSpeed2 = 0.0f;
    float beeSpeed3 = 0.0f;
    float beeSpeed4 = 0.0f;

    Texture cloudTexture;
    cloudTexture.loadFromFile("Sprites/Graphics/cloud.png");
    Sprite cloudSprite1;
    cloudSprite1.setTexture(cloudTexture);
    cloudSprite1.setPosition(0, 0);
    Sprite cloudSprite2;
    cloudSprite2.setTexture(cloudTexture);
    cloudSprite2.setPosition(res.x - 300, 150);
    Sprite cloudSprite3;
    cloudSprite3.setTexture(cloudTexture);
    cloudSprite3.setPosition(res.x / 2 + 200, 80);
    bool cloudActive1 = false;
    float cloudSpeed1 = 0.0f;
    bool cloudActive2 = false;
    float cloudSpeed2 = 0.0f;
    bool cloudActive3 = false;
    float cloudSpeed3 = 0.0f;

    Texture playerTexture;
    playerTexture.loadFromFile("Sprites/Graphics/player.png");
    Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(480, res.y - 330);
    side playerSide = side::LEFT;

    Texture graveTexture;
    graveTexture.loadFromFile("Sprites/Graphics/rip.png");
    Sprite graveSprite;
    graveSprite.setTexture(graveTexture);
    graveSprite.setPosition(500, res.y - 300);

    Texture axeTexture;
    axeTexture.loadFromFile("Sprites/Graphics/axe.png");
    Sprite axeSprite;
    axeSprite.setTexture(axeTexture);
    axeSprite.setPosition(600, res.y - 310);

    const float AXE_POSITION_LEFT = 650;
    const float AXE_POSITION_RIGHT = 950;

    Texture logTexture;
    logTexture.loadFromFile("Sprites/Graphics/log.png");
    Sprite logSprite;
    logSprite.setTexture(logTexture);
    logSprite.setPosition(650, res.y - 330);

    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    bool acceptInput = false;
    // Prepare the sounds
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("Sprites/Sounds/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("Sprites/Sounds/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("Sprites/Sounds/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

    Clock clock;
    // Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400.0f;
    float timeBarHeight = 80.0f;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((res.x / 2) - timeBarStartWidth / 2.0, res.y - 100);
    Time gameTimeTotal;
    float timeRemaining = 10.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool paused = true;

    // HUD
    Text scoreText, messageText;
    Font font;
    font.loadFromFile("Sprites/Font/KOMIKAP_.ttf");
    int score = 0;
    messageText.setFont(font);
    scoreText.setFont(font);
    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");
    messageText.setCharacterSize(80);
    scoreText.setCharacterSize(60);
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(res.x / 2.0f, res.y / 2.0f);
    scoreText.setPosition(20, 20);

    Texture branchTexture;
    branchTexture.loadFromFile("Sprites/Graphics/branch.png");
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(branchTexture);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 20);
    }

    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);

    while (rm.isOpen())
    {
        Event event;
        while (rm.pollEvent(event))
        {
            if (event.type == Event::KeyReleased && !paused)
            {
                acceptInput = true;
                axeSprite.setPosition(2000, axeSprite.getPosition().y);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            rm.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            paused = false;
            score = 0;
            timeRemaining = 9.0f;

            for (int i = 1; i < NUM_BRANCHES; i++)
            {
                branchPositions[i] = side::NONE;
            }

            graveSprite.setPosition(675, 2000);
            playerSprite.setPosition(480, res.y - 330);

            acceptInput = true;
        }
        if (acceptInput)
        {
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                playerSide = side::RIGHT;
                score++;
                timeRemaining += (2 / score) + .15;
                axeSprite.setPosition(AXE_POSITION_RIGHT, axeSprite.getPosition().y);
                playerSprite.setPosition(1000, res.y - 330);
                updateBranches(score);
                logSprite.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;
                chop.play();
            }
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                playerSide = side::LEFT;
                score++;
                timeRemaining += (2 / score) + .15;
                axeSprite.setPosition(AXE_POSITION_LEFT, axeSprite.getPosition().y);
                playerSprite.setPosition(480, res.y - 330);
                updateBranches(score);
                logSprite.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;
            }
        }
        if (!paused)
        {
            Time dt = clock.restart();

            // Subtract and size up the time bar
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                paused = true;
                messageText.setString("Out Of Time!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(res.x / 2.0f, res.y / 2.0f);
                outOfTime.play();
            }

            // Bee animation
            if (!beeActive1)
            {
                beeSpeed1 = (rand() % 200) + 200;
                srand(time(0) * 20);
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite1.setPosition(res.x + 200, height);
                beeActive1 = true;
            }
            else
            {
                beeSprite1.setPosition(
                    beeSprite1.getPosition().x - beeSpeed1 * dt.asSeconds(),
                    beeSprite1.getPosition().y);

                if (beeSprite1.getPosition().x < -100)
                    beeActive1 = false;
            }

            if (!beeActive2)
            {
                beeSpeed2 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite2.setPosition(res.x + 200, height);
                beeActive2 = true;
            }
            else
            {
                beeSprite2.move(-beeSpeed2 * dt.asSeconds(), 0);

                if (beeSprite2.getPosition().x < -100)
                    beeActive2 = false;
            }

            if (!beeActive3)
            {
                beeSpeed3 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite3.setPosition(res.x + 200, height);
                beeActive3 = true;
            }
            else
            {
                beeSprite3.move(-beeSpeed3 * dt.asSeconds(), 0);

                if (beeSprite3.getPosition().x < -100)
                    beeActive3 = false;
            }

            if (!beeActive4)
            {
                beeSpeed4 = (rand() % 200) + 200;
                float height = (rand() % (int)(res.y - 100)) + 50;
                beeSprite4.setPosition(res.x + 200, height);
                beeActive4 = true;
            }
            else
            {
                beeSprite4.move(-beeSpeed4 * dt.asSeconds(), 0);

                if (beeSprite4.getPosition().x < -100)
                    beeActive4 = false;
            }

            // Cloud animation
            if (!cloudActive1)
            {
                srand((int)time(0) * 10);
                cloudSpeed1 = (rand() % 200);
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                cloudSprite1.setPosition(-200, height);
                cloudActive1 = true;
            }
            else
            {
                cloudSprite1.setPosition(
                    cloudSprite1.getPosition().x + (cloudSpeed1 * dt.asSeconds()), cloudSprite1.getPosition().y);
                if (cloudSprite1.getPosition().x > res.x)
                    cloudActive1 = false;
            }

            if (!cloudActive2)
            {
                srand((int)time(0) * 20);
                cloudSpeed2 = (rand() % 200);
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                cloudSprite2.setPosition(-200, height);
                cloudActive2 = true;
            }
            else
            {
                cloudSprite2.setPosition(
                    cloudSprite2.getPosition().x + (cloudSpeed2 * dt.asSeconds()), cloudSprite2.getPosition().y);
                if (cloudSprite2.getPosition().x > res.x)
                    cloudActive2 = false;
            }

            if (!cloudActive3)
            {
                srand((int)time(0) * 20);
                cloudSpeed3 = (rand() % 200);
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                cloudSprite3.setPosition(-200, height);
                cloudActive3 = true;
            }
            else
            {
                cloudSprite3.setPosition(
                    cloudSprite3.getPosition().x + (cloudSpeed3 * dt.asSeconds()), cloudSprite3.getPosition().y);
                if (cloudSprite3.getPosition().x > res.x)
                    cloudActive3 = false;
            }

            // Update the score
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            // Update the branches
            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT)
                {
                    branches[i].setPosition(610, height); // Move to left
                    branches[i].setRotation(180);         // Flip the other way
                }
                else if (branchPositions[i] == side::RIGHT)
                {
                    branches[i].setPosition(1330, height); // Move to right
                    branches[i].setRotation(0);            // Set to normal
                }
                else
                {
                    branches[i].setPosition(3000, height); // Hide the branches
                }
            }
            // Flying log
            if (logActive)
            {
                logSprite.setPosition(
                    logSprite.getPosition().x + (logSpeedX * dt.asSeconds()),
                    logSprite.getPosition().y + (logSpeedY * dt.asSeconds()));
                if (logSprite.getPosition().x < -100 || logSprite.getPosition().x > 2000)
                {
                    logActive = false;
                    logSprite.setPosition(810, 720);
                }
            }
            // death
            if (branchPositions[5] == playerSide)
            {
                paused = true;
                acceptInput = false;
                graveSprite.setPosition(525, 760);
                playerSprite.setPosition(2000, 660);
                messageText.setString("SQUISHED!!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(res.x / 2.0f, res.y / 2.0f);
                death.play();
            }
        }

        rm.clear();

        rm.draw(bgSprite);
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            rm.draw(branches[i]);
        }
        rm.draw(treeSprite);
        rm.draw(playerSprite);
        rm.draw(axeSprite);
        rm.draw(logSprite);
        rm.draw(graveSprite);
        rm.draw(beeSprite1);
        rm.draw(beeSprite2);
        rm.draw(beeSprite3);
        rm.draw(beeSprite4);
        rm.draw(cloudSprite1);
        rm.draw(cloudSprite2);
        rm.draw(cloudSprite3);
        rm.draw(scoreText);
        rm.draw(timeBar);
        if (paused)
        {
            rm.draw(messageText);
        }
        rm.display();
    }
}