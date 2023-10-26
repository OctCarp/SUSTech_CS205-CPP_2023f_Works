#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string input;

    cout << "Please input a string: ";
    getline(cin, input);

    string temp1, temp2;
    for (char c: input) {
        if (isalpha(c) || c == ' ') {
            temp1 += c;
            temp2 += (char) toupper(c);
        }
    }

    ofstream file1("f1.txt");
    if (file1.is_open()) {
        file1 << temp1;
        file1.close();
    } else {
        cout << "Unable to open f1.txt" << endl;
        return 1;
    }

    ofstream file2("f2.txt");
    if (file2.is_open()) {
        file2 << temp2;
        file2.close();
    } else {
        cout << "Unable to open f2.txt" << endl;
        return 1;
    }

    cout << "The contents of f1.txt : " << temp1 << endl;
    cout << "The contents of f2.txt : " << temp2 << endl;

    return 0;
}
