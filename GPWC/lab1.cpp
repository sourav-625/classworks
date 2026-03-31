#include <iostream>

using namespace std;

class A {
    int x, y;
    
    public:
    A(); //declaration of default constructor
    A(int x, int y) {
        A::x = x;
        A::y = y;
        cout << "Parametrized constructor is invoked" << endl;
    }
    A(A &obj) {
        A::x = obj.x;
        A::y = obj.y;
        cout << "Copy construtor is invoked" << endl;
    }
    void display() {
        cout << x << y << endl;
    }
};

A::A() {
    x = 0;
    y = 0;
    cout << "Default Constructor is invoked" << endl;
}

int main() {
    A obj1;
    A obj2(1, 2);
    A *obj3 = new A();
    A *obj4 = new A(1, 2);
    obj1.display();
    obj2.display();
    obj3->display();
    obj4->display();
    A obj5(obj2);
    obj5.display();
    return 0;
}