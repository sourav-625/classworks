#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    RenderWindow window(vm, "Hello");
    Vector2f size(300, 400);
    Vector2f pos(100, 100);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        RectangleShape rect;
        rect.setFillColor(Color::Red);
        rect.setOutlineColor(Color::Green);
        rect.setOutlineThickness(2);
        rect.setSize(size);
        rect.setPosition(pos);
        window.clear(Color::White);
        window.draw(rect);
        window.display();
    }
    return 0;
}