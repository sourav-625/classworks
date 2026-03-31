#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Hello Window");
    while (window.isOpen()) {
        window.clear();

        // draw objects

        window.display();
    }
    return 0;
}