#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding random

int main() {
    // Create a window of size 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Application");

    // Create a rectangle of size 100x50 and position it at (300,400)
    sf::RectangleShape rectangle(sf::Vector2f(100, 50));
    rectangle.setPosition(300.f, 400.f);

    // Set the origin of the rectangle at its center
    rectangle.setOrigin(rectangle.getSize().x / 2.f, rectangle.getSize().y / 2.f);

    // Create squares at the four corners of the window
    sf::RectangleShape square(sf::Vector2f(50, 50));
    square.setFillColor(sf::Color::Green);

    // Load bee sprite
    sf::Texture beeTexture;
    if (!beeTexture.loadFromFile("bee.png")) {
        return -1; // Exit if the image is not loaded
    }
    sf::Sprite bee(beeTexture);
    
    // Load cloud sprite
    sf::Texture cloudTexture;
    if (!cloudTexture.loadFromFile("cloud.png")) {
        return -1; // Exit if the image is not loaded
    }
    sf::Sprite cloud1(cloudTexture);
    sf::Sprite cloud2(cloudTexture);

    // Randomly place the bee and clouds
    srand(static_cast<unsigned>(time(0)));

    float beeSpeed = rand() % 300 + 200; // Random speed from 200 to 500
    float beeHeight = rand() % 100 + 350; // Random height from 350 to 450
    bee.setPosition(-100.f, beeHeight); // Start position of the bee (off-screen)

    // Set random positions for the clouds
    float cloudSpeed1 = rand() % 200 + 50;
    float cloudSpeed2 = rand() % 200 + 50;

    cloud1.setPosition(-cloud1.getGlobalBounds().width, rand() % 300 + 10);
    cloud2.setPosition(800.f, rand() % 300 + 10);

    // Main game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Rotate the rectangle (clockwise) with 120 degrees per frame
        rectangle.rotate(120.f / 360.f); // Rotate by 120 degrees per second

        // Update the bee position
        bee.move(beeSpeed * 0.01f, 0); // Move the bee from left to right
        if (bee.getPosition().x > 800) {
            bee.setPosition(-100.f, rand() % 100 + 350); // Reset the bee once it leaves the window
        }

        // Update the clouds' positions
        cloud1.move(cloudSpeed1 * 0.01f, 0);
        cloud2.move(-cloudSpeed2 * 0.01f, 0);

        // If cloud1 goes off-screen on the right, reset to the left
        if (cloud1.getPosition().x > 800.f) {
            cloud1.setPosition(-cloud1.getGlobalBounds().width, rand() % 300 + 10);
        }

        // If cloud2 goes off-screen on the left, reset to the right
        if (cloud2.getPosition().x < -cloud2.getGlobalBounds().width) {
            cloud2.setPosition(800.f, rand() % 300 + 10);
        }

        // Clear the window
        window.clear(sf::Color::Blue);

        // Draw the rectangle
        window.draw(rectangle);

        // Draw the four corner squares
        square.setPosition(0, 0);
        window.draw(square);
        square.setPosition(750.f, 0);
        window.draw(square);
        square.setPosition(0, 550.f);
        window.draw(square);
        square.setPosition(750.f, 550.f);
        window.draw(square);

        // Draw the bee and clouds
        window.draw(bee);
        window.draw(cloud1);
        window.draw(cloud2);

        // Display the window content
        window.display();
    }

    return 0;
}