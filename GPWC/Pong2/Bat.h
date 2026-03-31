#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat {
    //declare Postion
    Vector2f m_Position;

    //declare Shape
    RectangleShape m_Shape;

    //declare Speed
    float m_Speed = 1000.f;

    //declare bool var for right and left movement
    bool m_movingRight = false;
    bool m_movingLeft = false;
    bool m_movingUp = false;
    bool m_movingDown = false;

    public:

    //declare constructor method
    Bat(float startX, float startY);

    //declare get_Position()
    FloatRect get_Position();

    //get_Shape()
    RectangleShape get_Shape();

    //moveRight()
    void moveRight();

    //moveLeft()
    void moveLeft();

    //stopRight()
    void stopRight();

    //stopLeft()
    void stopLeft();

    void moveUp();
    void moveDown();
    void stopUp();
    void stopDown();

    //update()
    void update(Time dt);
};