#include <iostream>

using namespace std;

inline bool is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

inline string word_str(int cnt) {
    if (cnt < 2) {
        return to_string(cnt) + " word ";
    }
    return to_string(cnt) + " words ";
}

int main() {
    cout << "Enter words(q to quit):" << endl;
    string s;

    cin >> s;
    int cnt_v, cnt_c, cnt_o;
    cnt_v = cnt_c = cnt_o = 0;
    while (s != "q") {
        cin >> s;
        char ch = s[0];
        isalpha(ch) ? is_vowel(ch) ? ++cnt_v : ++cnt_c : ++cnt_o;
    }

    cout << word_str(cnt_v) << "begin with vowels." << endl;
    cout << word_str(cnt_c) << "begin with consonants." << endl;
    cout << cnt_o << " others." << endl;

    return 0;
}
