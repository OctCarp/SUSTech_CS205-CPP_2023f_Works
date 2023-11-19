#include <iostream>
#include <cstring>

using namespace std;

struct stringy {
    char *str;
    int ct;
};

void set(stringy &stry, const char in[]) {
    stry.ct = strlen(in);
    char *p = new char[stry.ct];
    strcpy(p, in);
    stry.str = p;
}

void show(const char str[], int times = 1) {
    while (times--) {
        cout << str << endl;
    }
}

void show(const stringy &stry, int times = 1) {
    while (times--) {
        cout << stry.str << endl;
    }
}

int main() {
    stringy beany;
    char testing[] = "Reality isn't what it used to be.";

    set(beany, testing);

    show(beany);
    show(beany, 2);

    testing[0] = 'D';
    testing[1] = 'u';
    show(testing);
    show(testing, 3);
    show("Done!");

    return 0;
}