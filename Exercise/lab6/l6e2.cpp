#include <iostream>

using namespace std;

const int MAX_SIZE = 1024;

int fill_array(double arr[], int size) {
    int p = 0;
    while (size--) {
        cout << "Enter value #" << (p + 1) << ": ";
        if (cin >> arr[p]) {
            ++p;
        } else {
            break;
        }
    }

    return p;
}

void show_array(double *arr, int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void reverse_array(double *arr, int size) {
    if (size <= 1) {
        return;
    }
    swap(arr[0], arr[size - 1]);
    reverse_array(arr + 1, size - 2);
}


int main() {
    double *d1 = new double[MAX_SIZE];
    int in_sz;
    cout << "Enter the size of an array: ";
    cin >> in_sz;

    int sz = fill_array(d1, in_sz);

    cout << "The original array is: ";
    show_array(d1, sz);
    cout << "The reversed array is: ";
    reverse_array(d1, sz);
    show_array(d1, sz);

    delete[] d1;
    return 0;
}