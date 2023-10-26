#include <iostream>

using namespace std;

int main() {
    cout << "Enter words(to stop, type the word done):" << endl;
    string s;

    cin >> s;
    int cnt = 0;
    while (s != "done") {
        ++cnt;
        cin >> s;
    }

    if (!cnt) {
        cout << "no word entered." << endl;
    } else {
        cout << "You entered " << cnt << (cnt < 2 ? " word." : " words.") << endl;
    }

    return 0;
}