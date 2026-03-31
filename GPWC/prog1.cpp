#include <iostream>
using namespace std;

int main() {
    int a, b, sum, diff, prod, quo, rem;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    sum = a + b;
    diff = a - b;
    prod = a * b;
    if (b == 0) {
        cout << "Division by zero not possible";
        return 1;
    }
    quo = a / b;
    rem = a % b;
    cout << "sum = " << sum << "\ndifference = " << diff << "\nproduct = " << prod << "\nQuotient = " << quo << "\nRemainder = " << rem << endl;
    return 0;
}