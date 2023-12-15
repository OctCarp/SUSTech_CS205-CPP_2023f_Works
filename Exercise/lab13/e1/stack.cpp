#include "stack.hpp"

Stack::Stack(int n) : size(n), top(0) {
    pitems = new Item[size];
}

Stack::Stack(const Stack &rhs) {
    size = rhs.size;
    top = rhs.top;
    pitems = new Item[size];
    for (int i = 0; i < top; ++i) {
        pitems[i] = rhs.pitems[i];
    }
}

Stack::~Stack() {
    delete[] pitems;
}

bool Stack::isempty() const {
    return top == 0;
}

bool Stack::isfull() const {
    return top == size;
}

bool Stack::push(const Item &item) {
    if (isfull()) {
        return false;
    } else {
        pitems[top++] = item;
        return true;
    }
}

bool Stack::pop(Item &item) {
    if (isempty()) {
        return false;
    } else {
        item = pitems[--top];
        return true;
    }
}

Stack &Stack::operator=(const Stack &rhs) {
    if (this != &rhs) {
        delete[] pitems;
        size = rhs.size;
        top = rhs.top;
        pitems = new Item[size];
        for (int i = 0; i < top; ++i) {
            pitems[i] = rhs.pitems[i];
        }
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Stack &stack) {
    os << "Capacity is: " << stack.size << " ";
    os << "Elements count is: " << stack.top << '\n';

    os << "Elements inside: ";
    for (int i = 0; i < stack.top; ++i) {
        os << stack.pitems[i] << " ";
    }
    os << std::endl;
    return os;
}