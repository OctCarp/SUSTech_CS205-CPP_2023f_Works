#include <iostream>
#include <cstring>

using namespace std;

template<typename T>
T maxn(T arr[], int sz) {
    T maxVal = arr[0];
    for (int i = 1; i < sz; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

template<>
const char *maxn<const char *>(const char *arr[], int sz) {
    const char *maxP = arr[0];
    int maxLen = strlen(arr[0]);
    for (int i = 1; i < sz; i++) {
        int len = strlen(arr[i]);
        if (len > maxLen) {
            maxP = arr[i];
            maxLen = len;
        }
    }
    return maxP;
}

int main() {
    int intArr[] = {1, 2, 3, 4, 5};
    double doubleArr[] = {1.1, 2.7, -3.5, -2};
    const char *stringArr[] = {"this", "no body", "morning", "birds", "sky"};

    cout << "Max int: " << maxn(intArr, 5) << endl;
    cout << "Max double: " << maxn(doubleArr, 5) << endl;
    cout << "Longest string: " << maxn(stringArr, 5) << endl;

    return 0;
}