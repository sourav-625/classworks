#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <sstream>

float length(sf::Vector2f v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f normalize(sf::Vector2f v) {
    float len = length(v);
    if (len != 0)
        return v / len;
    return v;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Space Survival");
    window.setFramerateLimit(60);

    // Player
    sf::CircleShape player(25);
    player.setFillColor(sf::Color::Cyan);
    player.setOrigin(25, 25);
    player.setPosition(500, 350);
    float playerSpeed = 300.f;

    // Bullets
    std::vector<sf::CircleShape> bullets;
    float bulletSpeed = 700.f;

    // Enemies
    std::vector<sf::CircleShape> enemies;
    float enemySpawnTimer = 0;
    float enemySpawnDelay = 1.0f;

    // Font (make sure arial.ttf is in folder)
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(300, 250);

    int score = 0;
    bool gameOver = false;

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!gameOver && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::CircleShape bullet(5);
                    bullet.setFillColor(sf::Color::Yellow);
                    bullet.setOrigin(5, 5);
                    bullet.setPosition(player.getPosition());
                    bullets.push_back(bullet);
                }
            }

            if (gameOver && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    gameOver = false;
                    score = 0;
                    enemies.clear();
                    bullets.clear();
                    player.setPosition(500, 350);
                }
            }
        }

        if (!gameOver) {
            // Player Movement
            sf::Vector2f movement(0, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= playerSpeed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += playerSpeed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= playerSpeed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += playerSpeed;

            player.move(movement * deltaTime);

            // Rotate toward mouse
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldMouse = window.mapPixelToCoords(mousePos);
            sf::Vector2f direction = worldMouse - player.getPosition();
            player.setRotation(std::atan2(direction.y, direction.x) * 180 / 3.14159);

            // Spawn Enemies
            enemySpawnTimer += deltaTime;
            if (enemySpawnTimer >= enemySpawnDelay) {
                enemySpawnTimer = 0;

                sf::CircleShape enemy(20);
                enemy.setFillColor(sf::Color::Red);
                enemy.setOrigin(20, 20);

                int side = rand() % 4;
                if (side == 0) enemy.setPosition(rand() % 1000, 0);
                if (side == 1) enemy.setPosition(rand() % 1000, 700);
                if (side == 2) enemy.setPosition(0, rand() % 700);
                if (side == 3) enemy.setPosition(1000, rand() % 700);

                enemies.push_back(enemy);
            }

            // Move Bullets
            for (auto& bullet : bullets) {
                sf::Vector2f dir = normalize(worldMouse - bullet.getPosition());
                bullet.move(dir * bulletSpeed * deltaTime);
            }

            // Move Enemies
            for (auto& enemy : enemies) {
                sf::Vector2f dir = normalize(player.getPosition() - enemy.getPosition());
                enemy.move(dir * 150.f * deltaTime);
            }

            // Bullet-Enemy Collision
            for (int i = 0; i < bullets.size(); i++) {
                for (int j = 0; j < enemies.size(); j++) {
                    if (bullets[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
                        bullets.erase(bullets.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        score++;
                        break;
                    }
                }
            }

            // Enemy-Player Collision
            for (auto& enemy : enemies) {
                if (enemy.getGlobalBounds().intersects(player.getGlobalBounds())) {
                    gameOver = true;
                    gameOverText.setString("GAME OVER\nPress R to Restart");
                }
            }

            std::stringstream ss;
            ss << "Score: " << score;
            scoreText.setString(ss.str());
        }

        window.clear(sf::Color(30, 30, 30));

        window.draw(player);
        for (auto& bullet : bullets) window.draw(bullet);
        for (auto& enemy : enemies) window.draw(enemy);

        window.draw(scoreText);
        if (gameOver)
            window.draw(gameOverText);

        window.display();
    }

    return 0;
}
