#include "stack.hpp"

using namespace std;

int main() {
    Stack s1(3);
    Item popped;

    cout << boolalpha << s1.pop(popped) << endl;

    for (int i = 0; i < 3; ++i) {
        s1.push(i + 1);
    }
    cout << boolalpha << s1.push(4) << endl;
    cout << "s1: " << s1 << endl;


    s1.pop(popped);
    cout << "popped Item is:" << popped << endl;

    Stack s2(s1);
    cout << "s1: " << s1 << "s2: " << s2 << endl;

    s1.pop(popped);
    s2.push(3);
    Stack s3 = s1;
    s3.push(2);

    cout << "s1: " << s1 << "s2: " << s2 << "s3: " << s3 << endl;

    return 0;
}