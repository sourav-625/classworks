#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    RenderWindow window(vm, "Hello");
    Vector2f size(200, 100);
    Vector2f pos((VideoMode::getDesktopMode().width / 2.0f) - (size.x / 2.0f), (VideoMode::getDesktopMode().height / 2.0f) - (size.y / 2.0f));
    while (window.isOpen())
    {
        RectangleShape rect;
        rect.setFillColor(Color::Red);
        rect.setOutlineColor(Color::Green);
        rect.setOutlineThickness(2);
        rect.setSize(size);
        rect.setPosition(pos);
        //rect.setRotation(30);
        window.clear(Color::White);
        window.draw(rect);
        window.display();
    }
    return 0;
}