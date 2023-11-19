#include <iostream>
#include <cstring>
#include "match.hpp"

using namespace std;

const int MAX_LEN = 1000;

int main() {
    char ch, str[MAX_LEN];
    cout<<"Please input a string:\n";
    cin>>str;
    cin.getline(str, MAX_LEN);
    cout<<"Please input a character:\n";
    cin>>ch;
    const char *res=match(str, ch);
    cout<< (res? res: "Not Found")<<endl;

    return 0;
}