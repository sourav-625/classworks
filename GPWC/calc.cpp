#include <iostream>
using namesapce std;

int main() {
    int a, b;
    char op;
    cin >> a >> op >> b;
    switch (op) {
        case '+': cout << a + b;
        break;
        case '-': cout << a - b;
        break;
        case '*': cout << a * b;
        break;
        case '/':
        if (b == 0) {
            cout << "Division by zero!";
            return 1;
        } else {
            cout << a / b;
        }
        break;
        case '%':
        if (b == 0) {
            cout << "Second operand can not be zero!";
            return 1;
        } else {
            cout << a % b;
        }
        break;
        case default: cout << "Invalid Operator"
    }
    return 0;
}