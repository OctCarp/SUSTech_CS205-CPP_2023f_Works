#include <iostream>

using namespace std;

void Displaymenu() {
    cout << "================================================\n";
    cout << "                      MENU                      \n";
    cout << "================================================\n";
    cout << "         1.Add\n";
    cout << "         2.Substract\n";
    cout << "         3.Multiply\n";
    cout << "         4.Divide\n";
    cout << "         5.Modulus" << endl;
}

int Add(int a, int b) {
    return a + b;
}

int Substract(int a, int b) {
    return a - b;
}

int Multiply(int a, int b) {
    return a * b;
}

int Divide(int a, int b) {
    return a / b;
}

int Modulus(int a, int b) {
    return a % b;
}

int main() {
    Displaymenu();
    int yourChoice;
    int a, b;
    char confirm;
    
    do {
        cout << "Enter your choice(1~5): ";
        cin >> yourChoice;
        cout << "Enter your integer numbers: ";
        cin >> a >> b;
        cout << '\n';
        
        int res;
        switch (yourChoice) {
            case 1:
                res = Add(a, b);
                break;
            case 2:
                res = Substract(a, b);
                break;
            case 3:
                res = Multiply(a, b);
                break;
            case 4:
                res = Divide(a, b);
                break;
            case 5:
                res = Modulus(a, b);
                break;
            default:
                cout << "Wrong choice.";
                continue;
        }
        cout << "Result:" << res << '\n';
        
        cout << "Press y or Y to continue: ";
        cin >> confirm;
    } while (confirm == 'y' || confirm == 'Y');

    cout << "Done." << endl;
}